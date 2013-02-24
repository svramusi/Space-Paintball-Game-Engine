/*
 * ClientConnection.cpp
 *
 *  Created on: Feb 10, 2013
 *      Author: amarppatel
 */

#include "net/ClientConnection.h"

namespace net
{
	ClientConnection::ClientConnection(Address* clientAddress) : GameConnection(clientAddress) {

	}

	ClientConnection::~ClientConnection() {
		delete serverConnection;
	}

	void ClientConnection::Connect(Address* serverMasterAddress) {
		//ServerMasterConnection * serverMasterConnection = new ServerMasterConnection(serverMasterAddress);

		//if ( !serverMasterConnection->Init() )
		//{
		//	printf( "could not start connection to server master on port %d\n", serverMasterAddress->GetPort() );
			// Throw exception.
		//}

		//serverConnection = serverMasterConnection->AcceptConection(address);

		if ( !connection->Start( address->GetPort() ) )
		{
			printf( "could not start client connection on port %d\n", address->GetPort() );
			return;
		}

		connection->Connect( *serverMasterAddress );
	}

	void ClientConnection::Send(GamePacket* data) {
		// Need to implement this method.
		//unsigned char packet[] = "client to server";
		serverConnection->Send(data);
	}

	GamePacket* ClientConnection::Receive() {
		// Need to implement this method.
//		unsigned char packet[] = "client to server";
		GamePacket* gamePacket = serverConnection->Receive();
		return gamePacket;
	}

	bool ClientConnection::HasData() const {
		return serverConnection->HasData();
	}
}
