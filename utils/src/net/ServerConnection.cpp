/*
 * ServerConnection.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#include "ServerConnection.h"

namespace net
{
	ServerConnection::ServerConnection() {

	}

	ServerConnection::ServerConnection(Connection connection) {
		this->connection = connection;
	}

	ServerConnection::~ServerConnection() {
		// TODO Auto-generated destructor stub
	}

	void ServerConnection::Send(GamePacket data) {
		// Need to implement this method.
	}

	GamePacket ServerConnection::Receive() {
		// Need to implement this method.
		GamePacket gamePacket;
		return gamePacket;
	}

	bool ServerConnection::HasData() {
		// Need to implement this method.
		return true;
	}
}
