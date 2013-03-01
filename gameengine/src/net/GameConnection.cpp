/*
 * GameConnection.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#include "net/GameConnection.h"

namespace net
{
	GameConnection::GameConnection(Address& theAddress) {
		connection = Connection( PROTOCOL_ID, TIME_OUT );
		address = theAddress;
	}

	GameConnection::~GameConnection() {
		connection.Stop();
	}

}
