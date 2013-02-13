/*
 * GameConnection.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#include "GameConnection.h"

namespace net
{
	GameConnection::GameConnection() {

	}

	GameConnection::GameConnection(Connection connection, int localIp) {
		this->connection = connection;
		this->localIp = localIp;
	}

	GameConnection::~GameConnection() {
		connection.Stop();
	}

}
