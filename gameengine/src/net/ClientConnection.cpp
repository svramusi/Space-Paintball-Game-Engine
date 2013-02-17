/*
 * ClientConnection.cpp
 *
 *  Created on: Feb 10, 2013
 *      Author: amarppatel
 */

#include "net/ClientConnection.h"

namespace net
{
	ClientConnection::ClientConnection(int clientPort ) {
		this-> clientPort = clientPort;

	}

	ClientConnection::~ClientConnection() {
		// TODO Auto-generated destructor stub
	}

	void ClientConnection::connect(int IP, int port) {
		Connection connection( PROTOCOL_ID, TIME_OUT );

		if ( !connection.Start( clientPort ) )
		{
			printf( "could not start connection on port %d\n", clientPort );
			// Throw exception.
		}

		connection.Connect( Address(127,0,0,1,SERVER_PORT ) );

		bool connected = false;

		while ( true )
		{
			if ( !connected && connection.IsConnected() )
			{
				printf( "client connected to server\n" );
				connected = true;
			}

			if ( !connected && connection.ConnectFailed() )
			{
				printf( "connection failed\n" );
				break;
			}

			unsigned char packet[] = "client to server";
			connection.SendPacket( packet, sizeof( packet ) );

			while ( true )
			{
				unsigned char packet[256];
				int bytes_read = connection.ReceivePacket( packet, sizeof(packet) );
				if ( bytes_read == 0 )
					break;
				printf( "received packet from server\n" );
			}

			connection.Update( DELTA_TIME );
			NetUtils::wait( DELTA_TIME );
		}
	}

	void ClientConnection::Send(GamePacket data) {
		// Need to implement this method.
	}

	GamePacket ClientConnection::Receive() {
		// Need to implement this method.
		GamePacket gamePacket;
		return gamePacket;
	}

	bool ClientConnection::HasData() {
		// Need to implement this method.
		return true;
	}
}
