/*
 * GameConnection.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#include "net/GameConnection.h"

namespace net
{
	GameConnection::GameConnection(Address* address) {
		this->connection = new Connection( PROTOCOL_ID, TIME_OUT );
		this->address = address;
	}

	GameConnection::~GameConnection() {
		connection->Stop();
		delete connection;
		delete address;
	}

}
