/*
 * ClientSocket.cpp
 *
 *  Created on: Mar 8, 2013
 *      Author: amarppatel
 */

#include "net/ClientSocket.h"

namespace net
{
	ClientSocket::ClientSocket()
	{
	}

	ClientSocket::~ClientSocket()
	{
		Close();
	}

	bool ClientSocket::Connect( char* host_name, unsigned short port )
	{
		Setup();

		sockaddr_in address;
		address.sin_family = AF_INET;
		address.sin_port = htons( port );
		address.sin_addr.s_addr = inet_addr( host_name );

		if( connect( socket, (const sockaddr*) &address, sizeof(sockaddr_in) ) == -1 )
		{
			if( ( err = errno ) != EINPROGRESS )
			{
				fprintf(stderr, "Error connecting socket %d\n", errno);
				Close();
				return false;
			}
		}

		return true;
	}

}
