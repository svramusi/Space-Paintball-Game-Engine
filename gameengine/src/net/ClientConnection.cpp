/*
 * ClientConnection.cpp
 *
 *  Created on: Feb 10, 2013
 *      Author: amarppatel
 */

#include "net/ClientConnection.h"

namespace net
{
	ClientConnection::ClientConnection(Address& clientAddress) : GameConnection(clientAddress) {

	}

	ClientConnection::~ClientConnection() {
	}

	bool ClientConnection::Init() {
		return connection.Start(address.GetPort());
	}

	void ClientConnection::Connect(Address& serverMasterAddress) {
		connection.Connect(serverMasterAddress);
	}

	bool ClientConnection::SendPacket( const unsigned char data[], int size ) {
		connection.SendPacket(data, size);
	}

	int ClientConnection::ReceivePacket( unsigned char data[], int size ) {
		connection.ReceivePacket( data, size );
	}

	bool ClientConnection::HasData() const {
		return connection.HasData();
	}

	bool ClientConnection::ConnectFailed() const {
		return connection.ConnectFailed();
	}

	void ClientConnection::Update( float deltaTime ) {
		connection.Update(deltaTime);
	}

	bool ClientConnection::IsConnected() const
	{
		return connection.IsConnected();
	}
}
