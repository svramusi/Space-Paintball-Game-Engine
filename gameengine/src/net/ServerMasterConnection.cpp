/*
 * ServerMasterConnection.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#include "net/ServerMasterConnection.h"

namespace net
{
	ServerMasterConnection::ServerMasterConnection(Address& address) : GameConnection(address) {
	}

	ServerMasterConnection::~ServerMasterConnection() {
	}

	bool ServerMasterConnection::Init() {
		return connection.Start(address.GetPort());
	}

	void ServerMasterConnection::Listen() {
		connection.Listen();
	}

	ServerConnection ServerMasterConnection::AcceptConection(Address& source) {
		ServerConnection serverConnection(source);

	    return serverConnection;
	}

	bool ServerMasterConnection::IsConnected() const {
		return connection.IsConnected();
	}

	bool ServerMasterConnection::SendPacket( const unsigned char data[], int size ) {
		connection.SendPacket(data, size);
	}

	int ServerMasterConnection::ReceivePacket( unsigned char data[], int size ) {
		connection.ReceivePacket( data, size );
	}

	bool ServerMasterConnection::HasData() const {
		return connection.HasData();
	}

	void ServerMasterConnection::Update( float deltaTime )
	{
		connection.Update(deltaTime);
	}
}
