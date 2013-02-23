/*
 * ServerMasterConnection.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#include "net/ServerMasterConnection.h"

namespace net
{
	ServerMasterConnection::ServerMasterConnection(Address* address) : GameConnection(address) {
		this-> addressToConnectionMap = new map<Address*, ServerConnection*>();
	}

	ServerMasterConnection::~ServerMasterConnection() {
		delete addressToConnectionMap;
	}

	bool ServerMasterConnection::Init() {
		// Set the connection port and start the connection
		if ( !connection->Start( address->GetPort() ) )
		{
			printf( "could not start master connection on port %d\n", address->GetPort() );
			// Should throw exception if error occurs.
			return false;
		}

		// Start listening
		connection->Listen();
		return true;
	}

	ServerConnection* ServerMasterConnection::AcceptConection(Address* address) {
		if(connection->HasData())
		{
			ServerConnection* serverConnection = new ServerConnection(address);

			// Put server connection into map
			addressToConnectionMap->insert(make_pair(address, serverConnection));

			return serverConnection;
		}

		return NULL;
	}

	bool ServerMasterConnection::IsConnected() const {
		return connection->IsConnected();
	}

	map<Address*, ServerConnection*>* ServerMasterConnection::GetConnections() {
		return this->addressToConnectionMap;
	}

	void ServerMasterConnection::Send(GamePacket* data) {
		//connection->SendPacket(data->Encode(), data->GetByteSize());
		unsigned char packet[] = "master server to client";
		connection->SendPacket( packet, sizeof( packet ) );
	}

	GamePacket* ServerMasterConnection::Receive() {
		// Need to implement this method.
		unsigned char packet[256];
		int bytes_read = connection->ReceivePacket( packet, sizeof(packet) );
		GamePacket* gamePacket = new GamePacket(packet);
		return gamePacket;
	}

	bool ServerMasterConnection::HasData() const {
		return connection->HasData();
	}

	void ServerMasterConnection::Update( float deltaTime )
	{
		connection->Update(deltaTime);
	}
}
