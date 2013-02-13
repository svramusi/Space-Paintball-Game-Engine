/*
 * ServerMasterConnection.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#include "ServerMasterConnection.h"

namespace net
{
	ServerMasterConnection::ServerMasterConnection(int port) {
		this->port = port;
		// Create the connection instance.
		Connection connection( PROTOCOL_ID, TIME_OUT );
	}

	ServerMasterConnection::~ServerMasterConnection() {
		// TODO Auto-generated destructor stub
	}

	void ServerMasterConnection::Init() {
		// Need to implement this function.
		// Set the connection port and start the connection
		if ( !connection.Start( SERVER_PORT ) )
		{
			printf( "could not start connection on port %d\n", SERVER_PORT );
			// Should throw exception if error occurs.
			return;
		}

		// Start listening
		connection.Listen();
	}

	ServerConnection ServerMasterConnection::AcceptConection(int &IP) {
		// Need to implement this function.
		if(HasData())
		{
			Connection connection( PROTOCOL_ID, TIME_OUT );

			// Set the connection port and start the connection
			if ( !connection.Start( CLIENT_PORT ) )
			{
				printf( "could not start connection on port %d\n", CLIENT_PORT );
				// Should throw exception if error occurs.
			}
			else
			{
				// Start listening
				connection.Listen();

				ServerConnection serverConnection( connection );

				return serverConnection;
			}
		}
	}

	void ServerMasterConnection::Send(GamePacket data) {
		// Need to implement this method.
	}

	GamePacket ServerMasterConnection::Receive() {
		// Need to implement this method.
		GamePacket gamePacket;
		return gamePacket;
	}

	bool ServerMasterConnection::HasData() {
		// Need to implement this method.
		return true;
	}
}
