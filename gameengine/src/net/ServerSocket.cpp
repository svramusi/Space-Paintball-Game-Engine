/*
 * ServerSocket.cpp
 *
 *  Created on: Mar 8, 2013
 *      Author: amarppatel
 */

#include "net/ServerSocket.h"

namespace net
{
	ServerSocket::ServerSocket()
	{
	}

	ServerSocket::ServerSocket( int theSocket )
	{
		socket = theSocket;
	}

	ServerSocket::~ServerSocket()
	{
		Close();
	}

	Address& ServerSocket::GetClientAddress()
	{
		return clientAddress;
	}

	void ServerSocket::SetClientAddress( Address& theClientAddress )
	{
		clientAddress = theClientAddress;
	}
}
