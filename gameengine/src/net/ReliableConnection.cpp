/*
 * ReliableConnection.cpp
 *
 *  Created on: Mar 1, 2013
 *      Author: amarppatel
 */

#include "net/ReliableConnection.h"

namespace net {

ReliableConnection::ReliableConnection( unsigned int protocolId, float timeout, unsigned int max_sequence )
			: Connection( protocolId, timeout ), reliabilitySystem( max_sequence )
{
	ClearData();
	#ifdef NET_UNIT_TEST
	packet_loss_mask = 0;
	#endif
}


ReliableConnection::~ReliableConnection() {
	if ( IsRunning() )
	{
		Stop();
	}
}

bool ReliableConnection::SendPacket( const unsigned char data[], int size )
{
	#ifdef NET_UNIT_TEST
	if ( reliabilitySystem.GetLocalSequence() & packet_loss_mask )
	{
		reliabilitySystem.PacketSent( size );
		return true;
	}
	#endif
	const int header = 12;
	unsigned char packet[header+size];
	unsigned int seq = reliabilitySystem.GetLocalSequence();
	unsigned int ack = reliabilitySystem.GetRemoteSequence();
	unsigned int ack_bits = reliabilitySystem.GenerateAckBits();
	WriteHeader( packet, seq, ack, ack_bits );
	memcpy( packet + header, data, size );
		if ( !Connection::SendPacket( packet, size + header ) )
		return false;
	reliabilitySystem.PacketSent( size );
	return true;
}

int ReliableConnection::ReceivePacket( unsigned char data[], int size )
{
	const int header = 12;
	if ( size <= header )
		return false;
	unsigned char packet[header+size];
	int received_bytes = Connection::ReceivePacket( packet, size + header );
	if ( received_bytes == 0 )
		return false;
	if ( received_bytes <= header )
		return false;
	unsigned int packet_sequence = 0;
	unsigned int packet_ack = 0;
	unsigned int packet_ack_bits = 0;
	ReadHeader( packet, packet_sequence, packet_ack, packet_ack_bits );
	reliabilitySystem.PacketReceived( packet_sequence, received_bytes - header );
	reliabilitySystem.ProcessAck( packet_ack, packet_ack_bits );
	memcpy( data, packet + header, received_bytes - header );
	return received_bytes - header;
}

void ReliableConnection::Update( float deltaTime )
{
	Connection::Update( deltaTime );
	reliabilitySystem.Update( deltaTime );
}

int ReliableConnection::GetHeaderSize() const
{
	return Connection::GetHeaderSize() + reliabilitySystem.GetHeaderSize();
}

ReliabilitySystem & ReliableConnection::GetReliabilitySystem()
{
	return reliabilitySystem;
}

void ReliableConnection::WriteInteger( unsigned char * data, unsigned int value )
{
	data[0] = (unsigned char) ( value >> 24 );
	data[1] = (unsigned char) ( ( value >> 16 ) & 0xFF );
	data[2] = (unsigned char) ( ( value >> 8 ) & 0xFF );
	data[3] = (unsigned char) ( value & 0xFF );
}

void ReliableConnection::WriteHeader( unsigned char * header, unsigned int sequence, unsigned int ack, unsigned int ack_bits )
{
	WriteInteger( header, sequence );
	WriteInteger( header + 4, ack );
	WriteInteger( header + 8, ack_bits );
}

void ReliableConnection::ReadInteger( const unsigned char * data, unsigned int & value )
{
		value = ( ( (unsigned int)data[0] << 24 ) | ( (unsigned int)data[1] << 16 ) |
		      ( (unsigned int)data[2] << 8 )  | ( (unsigned int)data[3] ) );
}

void ReliableConnection::ReadHeader( const unsigned char * header, unsigned int & sequence, unsigned int & ack, unsigned int & ack_bits )
{
	ReadInteger( header, sequence );
	ReadInteger( header + 4, ack );
	ReadInteger( header + 8, ack_bits );
}

void ReliableConnection::OnStop()
{
	ClearData();
}

void ReliableConnection::OnDisconnect()
{
	ClearData();
}

void ReliableConnection::ClearData()
{
	reliabilitySystem.Reset();
}

} /* namespace net */
