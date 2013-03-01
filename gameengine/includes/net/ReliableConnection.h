/*
 * ReliableConnection.h
 *
 *  Created on: Mar 1, 2013
 *      Author: amarppatel
 */

#ifndef RELIABLECONNECTION_H_
#define RELIABLECONNECTION_H_

#include "Connection.h"
#include "ReliabilitySystem.h"

namespace net {

/*
 *connection with reliability (seq/ack)
 */
class ReliableConnection : public Connection {
public:
	ReliableConnection( unsigned int protocolId, float timeout, unsigned int max_sequence = 0xFFFFFFFF );
	virtual ~ReliableConnection();

	// overriden functions from "Connection"
	bool SendPacket( const unsigned char data[], int size );
	int ReceivePacket( unsigned char data[], int size );
	void Update( float deltaTime );
	int GetHeaderSize() const;
	ReliabilitySystem & GetReliabilitySystem();

	// unit test controls
	#ifdef NET_UNIT_TEST
	void SetPacketLossMask( unsigned int mask )
	{
		packet_loss_mask = mask;
	}
	#endif

protected:
		void WriteInteger( unsigned char * data, unsigned int value );
		void WriteHeader( unsigned char * header, unsigned int sequence, unsigned int ack, unsigned int ack_bits );
		void ReadInteger( const unsigned char * data, unsigned int & value );
		void ReadHeader( const unsigned char * header, unsigned int & sequence, unsigned int & ack, unsigned int & ack_bits );
		virtual void OnStop();
		virtual void OnDisconnect()

private:
	void ClearData();

	#ifdef NET_UNIT_TEST
	unsigned int packet_loss_mask;			// mask sequence number, if non-zero, drop packet - for unit test only
	#endif

	ReliabilitySystem reliabilitySystem;	// reliability system: manages sequence numbers and acks, tracks network stats etc.
};

} /* namespace net */
#endif /* RELIABLECONNECTION_H_ */
