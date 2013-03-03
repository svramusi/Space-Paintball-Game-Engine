/*
 * Connection.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#include "net/Connection.h"

namespace net
{
	Connection::Connection() {

	}

	Connection::Connection( unsigned int protocolId, float timeout ) {
		this->protocolId = protocolId;
		this->timeout = timeout;
		mode = None;
		running = false;
		ClearData();
	}

	Connection::~Connection() {
		if ( running )
			Stop();
	}

	bool Connection::Start( int port )
	{
		assert( !running );
		printf( "start connection on port %d\n", port );
		if ( !socket.Open( port ) )
			return false;
		running = true;
		OnStart();
		return true;
	}

	void Connection::Stop()
	{
		assert( running );
		printf( "stop connection\n" );
		bool connected = IsConnected();
		ClearData();
		socket.Close();
		running = false;
		if( connected )
		{
			OnDisconnect();
		}
		OnStop();
	}

	bool Connection::IsRunning() const
	{
		return running;
	}

	void Connection::Listen()
	{
		printf( "server listening for connection\n" );
		bool connected = IsConnected();
		ClearData();
		// Commenting out since listen only works for TCP connection -- socket.Listen();
		if( connected )
		{
			OnDisconnect();
		}
		mode = Server;
		state = Listening;
	}

	/*
	 * Client Method
	 */
	void Connection::Connect( const Address & address )
	{
		printf( "client connecting to %d.%d.%d.%d:%d\n",
			address.GetA(), address.GetB(), address.GetC(), address.GetD(), address.GetPort() );
		bool connected = IsConnected();
		ClearData();
		if( connected )
		{
			OnDisconnect();
		}
		mode = Client;
		state = Connecting;
		this->address = address;
	}

	bool Connection::IsConnecting() const
	{
		return state == Connecting;
	}

	bool Connection::HasData() const
	{
		return socket.HasData();
	}

	bool Connection::ConnectFailed() const
	{
		return state == ConnectFail;
	}

	bool Connection::IsConnected() const
	{
		return state == Connected;
	}

	bool Connection::IsListening() const
	{
		return state == Listening;
	}

	Connection::Mode Connection::GetMode() const
	{
		return mode;
	}

	void Connection::Update( float deltaTime )
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
				OnDisconnect();
			}
			else if ( state == Connected )
			{
				printf( "connection timed out\n" );
				ClearData();
				if ( state == Connecting )
				{
					state = ConnectFail;
				}
				OnDisconnect();
			}
		}
	}

	bool Connection::SendPacket( const unsigned char data[], int size )
	{
		assert( running );
		if ( address.GetAddress() == 0 )
			return false;
		unsigned char packet[size+4];
		packet[0] = (unsigned char) ( protocolId >> 24 );
		packet[1] = (unsigned char) ( ( protocolId >> 16 ) & 0xFF );
		packet[2] = (unsigned char) ( ( protocolId >> 8 ) & 0xFF );
		packet[3] = (unsigned char) ( ( protocolId ) & 0xFF );
		memcpy( &packet[4], data, size );
		return socket.Send( address, packet, size + 4 );
	}

	int Connection::ReceivePacket( unsigned char data[], int size )
	{
		assert( running );
		unsigned char packet[size+4];
		Address sender;
		int bytes_read = socket.Receive( sender, packet, size + 4 );
		if ( bytes_read == 0 )
			return 0;
		if ( bytes_read <= 4 )
			return 0;
		if ( packet[0] != (unsigned char) ( protocolId >> 24 ) ||
			 packet[1] != (unsigned char) ( ( protocolId >> 16 ) & 0xFF ) ||
			 packet[2] != (unsigned char) ( ( protocolId >> 8 ) & 0xFF ) ||
			 packet[3] != (unsigned char) ( protocolId & 0xFF ) )
			return 0;
		if ( mode == Server && !IsConnected() )
		{
			printf( "server accepts connection from client %d.%d.%d.%d:%d\n",
				sender.GetA(), sender.GetB(), sender.GetC(), sender.GetD(), sender.GetPort() );
			state = Connected;
			address = sender;
			OnConnect();
		}
		if ( sender == address )
		{
			if ( mode == Client && state == Connecting )
			{
				printf( "client completes connection with server\n" );
				state = Connected;
				OnConnect();
			}
			timeoutAccumulator = 0.0f;
			memcpy( data, &packet[4], bytes_read - 4 );
			return bytes_read - 4;
		}
		return 0;
	}

	int Connection::GetAddress( Address & sender, unsigned char data[], int size )
	{
		assert( running );
		unsigned char packet[size+4];

		int bytes_read = socket.Receive( sender, packet, size + 4 );
		if ( bytes_read == 0 )
			return 0;
		if ( bytes_read <= 4 )
			return 0;
		if ( packet[0] != (unsigned char) ( protocolId >> 24 ) ||
			 packet[1] != (unsigned char) ( ( protocolId >> 16 ) & 0xFF ) ||
			 packet[2] != (unsigned char) ( ( protocolId >> 8 ) & 0xFF ) ||
			 packet[3] != (unsigned char) ( protocolId & 0xFF ) )
			return 0;
		if ( mode == Server && !IsConnected() )
		{
			printf( "server accepts connection from client %d.%d.%d.%d:%d\n",
				sender.GetA(), sender.GetB(), sender.GetC(), sender.GetD(), sender.GetPort() );
			state = Connected;
			address = sender;
			OnConnect();
		}
		if ( sender == address )
		{
			if ( mode == Client && state == Connecting )
			{
				printf( "client completes connection with server\n" );
				state = Connected;
				OnConnect();
			}
			timeoutAccumulator = 0.0f;
			memcpy( data, &packet[4], bytes_read - 4 );
			return bytes_read - 4;
		}
		return 0;
	}

	int Connection::GetHeaderSize() const
	{
		return 4;
	}

	void Connection::ClearData()
	{
		state = Disconnected;
		timeoutAccumulator = 0.0f;
		address = Address();
	}
}
