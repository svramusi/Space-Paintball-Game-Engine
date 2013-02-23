/*
 * ClientConnection.cpp
 *
 *  Created on: Feb 10, 2013
 *      Author: amarppatel
 */

#include "net/ClientConnection.h"

namespace net
{
	ClientConnection::ClientConnection(Address* clientAddress) {
		this->clientAddress = clientAddress;
	}

	ClientConnection::~ClientConnection() {
		delete serverConnection;
		delete clientAddress;
	}

	void ClientConnection::connect(Address* serverMasterAddress) {
		ServerMasterConnection * serverMasterConnection = new ServerMasterConnection(serverMasterAddress);

		if ( !serverMasterConnection->Init() )
		{
			printf( "could not start connection to server master on port %d\n", serverMasterAddress->GetPort() );
			// Throw exception.
		}

		this->serverConnection = serverMasterConnection->AcceptConection(clientAddress);
	}

	void ClientConnection::Send(GamePacket* data) {
		// Need to implement this method.
	}

	GamePacket* ClientConnection::Receive() {
		// Need to implement this method.
		unsigned char packet[] = "client to server";
		GamePacket* gamePacket = new GamePacket(packet);
		return gamePacket;
	}

	bool ClientConnection::HasData() const {
		return serverConnection->HasData();
	}
}
