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
		/*
		connection->Connect( Address(127,0,0,1, SERVER_PORT ));

		bool connected = false;

			while ( true )
			{
				if ( !connected && connection->IsConnected() )
				{
					printf( "client connected to server\n" );
					connected = true;
				}

				if ( !connected && connection->ConnectFailed() )
				{
					printf( "connection failed\n" );
					break;
				}

				unsigned char packet[] = "client to server";
				connection->SendPacket( packet, sizeof( packet ) );

				while ( true )
				{
					unsigned char packet[256];
					int bytes_read = connection->ReceivePacket( packet, sizeof(packet) );
					if ( bytes_read == 0 )
						break;
					printf( "received packet from server\n" );
				}

				connection->Update( DELTA_TIME );
				NetUtils::wait( DELTA_TIME );
			}
			*/
	}

	void ClientConnection::Send(GamePacket* data) {
		connection->SendPacket(data->GetDataPtr(), data->GetByteSize());
	}

	GamePacket* ClientConnection::Receive() {
		unsigned char packet[256];
		int bytes_read = connection->ReceivePacket( packet, sizeof(packet) );

		if(bytes_read == 0)
		{
			return NULL;
		}
		else
		{
			GamePacket* gamePacket = new GamePacket(packet, bytes_read);
			return gamePacket;
		}
	}

	bool ClientConnection::HasData() const {
		return connection->HasData();
	}

	bool ClientConnection::ConnectFailed() const {
		return connection->ConnectFailed();
	}

	void ClientConnection::Update( float deltaTime ) {
		connection->Update(deltaTime);
	}

	bool ClientConnection::IsConnected() const
	{
		return connection->IsConnected();
	}
}
