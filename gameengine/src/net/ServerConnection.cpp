/*
 * ServerConnection.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#include "net/ServerConnection.h"

namespace net
{
	ServerConnection::ServerConnection(Address* address) : GameConnection(address) {
		// Set the connection port and start the connection
		if ( !connection->Start( address->GetPort() ) )
		{
			printf( "could not start server connection on port %d\n", address->GetPort() );
			// Should throw exception if error occurs.
		}
		else
		{
			// Start listening
			connection->Listen();
		}
	}

	ServerConnection::~ServerConnection() {
		delete connection;
	}

	void ServerConnection::Send(GamePacket* data) {
		//connection->SendPacket(data->Encode(), data->GetByteSize());
		unsigned char packet[] = "server to client";
		connection->SendPacket( packet, sizeof( packet ) );
	}

	GamePacket* ServerConnection::Receive() {
		// Need to implement this method.
		unsigned char packet[256];
		int bytes_read = connection->ReceivePacket( packet, sizeof(packet) );

		if(bytes_read == 0)
		{
			return NULL;
		}
		else
		{
			GamePacket* gamePacket = new GamePacket(packet);
			return gamePacket;
		}
	}

	bool ServerConnection::HasData() const {
		return connection->HasData();
	}

	bool ServerConnection::IsConnected() const {
		return connection->IsConnected();
	}

	void ServerConnection::Update( float deltaTime )
	{
		connection->Update(deltaTime);
	}
}
