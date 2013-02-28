/*
 * MasterConnection.cpp
 *
 *  Created on: Feb 27, 2013
 *      Author: amarppatel
 */

#include "net/MasterConnection.h"

namespace net {

MasterConnection::MasterConnection( unsigned int protocolId, float timeout ) {
	this->protocolId = protocolId;
	this->timeout = timeout;
	mode = None;
	running = false;
	ClearData();
}

MasterConnection::~MasterConnection() {
	if ( running )
		Stop();
}

bool MasterConnection::Start( int port )
{
	assert( !running );
	printf( "start connection on port %d\n", port );
	if ( !socket.Open( port ) )
		return false;
	running = true;
	return true;
}

void MasterConnection::Stop()
{
	assert( running );
	printf( "stop connection\n" );
	ClearData();
	socket.Close();
	running = false;
}

void MasterConnection::Listen()
{
	printf( "master server listening for connection\n" );
	ClearData();
	mode = Server;
	state = Listening;
}

void MasterConnection::Connect( const Address & address )
{
	printf( "client connecting to %d.%d.%d.%d:%d\n",
		address.GetA(), address.GetB(), address.GetC(), address.GetD(), address.GetPort() );
	ClearData();
	mode = Client;
	state = Connecting;
	this->address = address;
}

bool MasterConnection::HasData() const
{
	return socket.HasData();
}

bool MasterConnection::IsConnecting() const
{
	return state == Connecting;
}

bool MasterConnection::ConnectFailed() const
{
	return state == ConnectFail;
}

bool MasterConnection::IsConnected() const
{
	return state == Connected;
}

bool MasterConnection::IsListening() const
{
	return state == Listening;
}

MasterConnection::Mode MasterConnection::GetMode() const
{
	return mode;
}

void MasterConnection::Update( float deltaTime )
{
	assert( running );
	timeoutAccumulator += deltaTime;
	if ( timeoutAccumulator > timeout )
	{
		if ( state == Connecting )
		{
			printf( "connect timed out\n" );
			ClearData();
			state = ConnectFail;
		}
		else if ( state == Connected )
		{
			printf( "connection timed out\n" );
			ClearData();
			if ( state == Connecting )
				state = ConnectFail;
		}
	}
}

bool MasterConnection::SendPacket( const unsigned char data[], int size )
{
	assert( running );
	if ( address.GetAddress() == 0 )
		return false;
	unsigned char* packet = new unsigned char[size+4];
	packet[0] = (unsigned char) ( protocolId >> 24 );
	packet[1] = (unsigned char) ( ( protocolId >> 16 ) & 0xFF );
	packet[2] = (unsigned char) ( ( protocolId >> 8 ) & 0xFF );
	packet[3] = (unsigned char) ( ( protocolId ) & 0xFF );
	memcpy( &packet[4], data, size );
	bool res = socket.Send( address, packet, size + 4 );
	delete [] packet;
	return res;
}

int MasterConnection::ReceivePacket( unsigned char data[], int size )
{
	assert( running );
	unsigned char* packet = new unsigned char[size+4];
	Address sender;
	int bytes_read = socket.Receive( sender, packet, size + 4 );
	if ( bytes_read == 0 )
	{
		delete [] packet;
		return 0;
	}
	if ( bytes_read <= 4 )
	{
		delete [] packet;
		return 0;
	}
	if ( packet[0] != (unsigned char) ( protocolId >> 24 ) ||
		 packet[1] != (unsigned char) ( ( protocolId >> 16 ) & 0xFF ) ||
		 packet[2] != (unsigned char) ( ( protocolId >> 8 ) & 0xFF ) ||
		 packet[3] != (unsigned char) ( protocolId & 0xFF ) )
	{
		delete [] packet;
		return 0;
	}
	if ( mode == Server && !IsConnected() )
	{
		printf( "server accepts connection from client %d.%d.%d.%d:%d\n",
			sender.GetA(), sender.GetB(), sender.GetC(), sender.GetD(), sender.GetPort() );
		state = Connected;
		address = sender;
	}
	if ( sender == address )
	{
		if ( mode == Client && state == Connecting )
		{
			printf( "client completes connection with server\n" );
			state = Connected;
		}
		timeoutAccumulator = 0.0f;
		memcpy( data, &packet[4], size - 4 );
		delete [] packet;
		return size - 4;
	}
	delete [] packet;
	return 0;
}

void MasterConnection::ClearData()
{
	state = Disconnected;
	timeoutAccumulator = 0.0f;
	address = Address();
}

} /* namespace net */
