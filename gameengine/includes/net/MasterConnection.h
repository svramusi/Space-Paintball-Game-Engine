/*
 * MasterConnection.h
 *
 *  Created on: Feb 27, 2013
 *      Author: amarppatel
 */

#ifndef MASTERCONNECTION_H_
#define MASTERCONNECTION_H_

#include "Connection.h"
#include "Socket.h"
#include "MasterSocket.h"

namespace net {

class MasterConnection {
public:
	enum Mode
	{
		None,
		Client,
		Server
	};

	MasterConnection();
	MasterConnection(unsigned int protocolId, float timeout);
	virtual ~MasterConnection();
	bool Start( int port );
	void Stop();
	void Listen();
	void Connect( const Address & address );
	bool IsConnecting() const;
	bool ConnectFailed() const;
	bool IsConnected() const;
	bool IsListening() const;
	Mode GetMode() const;
	void Update( float deltaTime );
	bool SendPacket( const unsigned char data[], int size );
	int ReceivePacket( unsigned char data[], int size );

protected:
	void ClearData();

private:
	enum State
	{
		Disconnected,
		Listening,
		Connecting,
		ConnectFail,
		Connected
	};

	unsigned int protocolId;
	float timeout;

	bool running;
	Mode mode;
	State state;
	MasterSocket socket;
	float timeoutAccumulator;
	Address address;
};

} /* namespace net */
#endif /* MASTERCONNECTION_H_ */
