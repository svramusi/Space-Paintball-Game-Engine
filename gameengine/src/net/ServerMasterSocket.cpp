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

	ServerSocket& ServerMasterSocket::Accept( Address& sender )
	{
		int sock;
		sockaddr_in sadr;
		socklen_t addr_size = 0;
		pthread_t thread_id = 0;
		ServerSocket serverSocket;

		addr_size = sizeof(sockaddr_in);

		if( ( sock = accept( socket, (sockaddr*) &sadr, &addr_size ) ) != -1 )
		{
			//printf("---------------------\nReceived connection from %s\n", inet_ntoa( sadr.sin_addr ) );
			//pthread_create( &thread_id, 0, &ServerMasterSocket::SocketHandler, (void*)sock );
			//pthread_detach( thread_id );

			unsigned int address = ntohl( sadr.sin_addr.s_addr );
			unsigned short port = ntohs( sadr.sin_port );

			sender = Address( address, port );
			serverSocket = ServerSocket( sock );
		}
		else
		{
			fprintf( stderr, "Error accepting %d\n", errno );
		}

		return serverSocket;
	}

	/*
	void* ServerMasterSocket::SocketHandler( void* lp )
	{
	    int *csock = (int*)lp;

		char buffer[ 4 ];
		int bytecount = 0;
		string output, pl;

		memset( buffer, '\0', 4 );

		while ( 1 ) {
			if( HasData() )
			{
				Read();
			}

			usleep(1);
		}

		FINISH:
	        free(csock);
	    return 0;
	}
	*/
}
