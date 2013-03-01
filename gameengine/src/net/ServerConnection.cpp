/*
 * ServerConnection.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#include "net/ServerConnection.h"

namespace net
{
	ServerConnection::ServerConnection(Address& address) : GameConnection(address) {
	}

	ServerConnection::~ServerConnection() {
	}

	bool ServerConnection::SendPacket( const unsigned char data[], int size ) {
		connection.SendPacket(data, size);
	}

	int ServerConnection::ReceivePacket( unsigned char data[], int size ) {
		connection.ReceivePacket( data, size );
	}

	bool ServerConnection::HasData() const {
		return connection.HasData();
	}

	bool ServerConnection::IsConnected() const {
		return connection.IsConnected();
	}

	void ServerConnection::Update( float deltaTime )
	{
		connection.Update(deltaTime);
	}
}
