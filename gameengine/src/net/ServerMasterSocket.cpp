/*
 * ServerMasterSocket.cpp
 *
 *  Created on: Mar 8, 2013
 *      Author: amarppatel
 */

#include "net/ServerMasterSocket.h"

namespace net
{
	ServerMasterSocket::ServerMasterSocket()
	{
	}

	ServerMasterSocket::~ServerMasterSocket()
	{
		Close();
	}

	bool ServerMasterSocket::Open( unsigned short port )
	{
		Setup();
		sockaddr_in address;
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons( port );

		if ( bind( socket, (const sockaddr*) &address, sizeof(sockaddr_in) ) < 0 )
		{
			fprintf(stderr, "Error binding to socket, make sure nothing else is listening on this port %d\n", errno);
			Close();
			return false;
		}

		if( listen( socket, 10 ) == -1 )
		{
			fprintf( stderr, "Error listening %d\n", errno );
			Close();
			return false;
		}

		return true;
	}

	ServerSocket* ServerMasterSocket::Accept( Address& sender )
	{
		int sock;
		sockaddr_in sadr;
		socklen_t addr_size = 0;
		ServerSocket* serverSocket = NULL;

		addr_size = sizeof(sockaddr_in);

		if( ( sock = accept( socket, (sockaddr*) &sadr, &addr_size ) ) != -1 )
		{
			unsigned int address = ntohl( sadr.sin_addr.s_addr );
			unsigned short port = ntohs( sadr.sin_port );

			sender = Address( address, port );
			serverSocket = new ServerSocket( sock );
			serverSocket->SetClientAddress( sender );
		}
		else
		{
			fprintf( stderr, "Error accepting %d\n", errno );
		}

		printf( "New server socket: %s\n", sender.ToString().c_str() );
		return serverSocket;
	}
}
