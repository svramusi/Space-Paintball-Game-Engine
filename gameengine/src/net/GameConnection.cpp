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
		connection = Connection( ProtocolId, TimeOut );
		address = theAddress;
	}

	GameConnection::~GameConnection() {
		connection.Stop();
	}

}
