/*
 * Socket.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#include "net/Socket.h"

namespace net
{
	Socket::Socket() {
		socket = 0;

	}

	Socket::~Socket() {
		Close();
	}

	bool Socket::Open( unsigned short port )
	{
		assert( !IsOpen() );

		// create socket

		socket = ::socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

		if ( socket <= 0 )
		{
			printf( "failed to create socket\n" );
			socket = 0;
			return false;
		}

		// bind to port

		sockaddr_in address;
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons( (unsigned short) port );

		if ( bind( socket, (const sockaddr*) &address, sizeof(sockaddr_in) ) < 0 )
		{
			printf( "failed to bind socket\n" );
			Close();
			return false;
		}

		// set non-blocking io

		int nonBlocking = 1;
		if ( fcntl( socket, F_SETFL, O_NONBLOCK, nonBlocking ) == -1 )
		{
			printf( "failed to set non-blocking socket\n" );
			Close();
			return false;
		}

		return true;
	}

	void Socket::Close()
	{
		if ( socket != 0 )
		{
			close( socket );
			socket = 0;
		}
	}

	bool Socket::IsOpen() const
	{
		return socket != 0;
	}

	bool Socket::Send( const Address & destination, const void * data, int size )
	{
		assert( data );
		assert( size > 0 );

		if ( socket == 0 )
			return false;

		assert( destination.GetAddress() != 0 );
		assert( destination.GetPort() != 0 );

		sockaddr_in address;
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = htonl( destination.GetAddress() );
		address.sin_port = htons( (unsigned short) destination.GetPort() );

		int sent_bytes = sendto( socket, (const char*)data, size, 0, (sockaddr*)&address, sizeof(sockaddr_in) );

		return sent_bytes == size;
	}

	int Socket::Receive( Address & sender, void * data, int size )
	{
		assert( data );
		assert( size > 0 );

		if ( socket == 0 )
			return false;

		sockaddr_in from;
		socklen_t fromLength = sizeof( from );

		int received_bytes = recvfrom( socket, (char*)data, size, 0, (sockaddr*)&from, &fromLength );

		if ( received_bytes <= 0 )
			return 0;

		unsigned int address = ntohl( from.sin_addr.s_addr );
		unsigned short port = ntohs( from.sin_port );

		printf("Received packet from %s:%d\n Data: %s\n\n", inet_ntoa(from.sin_addr), port, data);

		sender = Address( address, port );

		return received_bytes;
	}

	bool Socket::HasData() const
	{
		// Determine if the socket has data.
	    bool            result;
	    fd_set          sready;
	    struct timeval  nowait;

	    FD_ZERO(&sready);
	    FD_SET((unsigned int)this->socket,&sready);
	    //bzero((char *)&nowait,sizeof(nowait));
	    memset((char *)&nowait,0,sizeof(nowait));

	    result = select(this->socket+1,&sready,NULL,NULL,&nowait);
	    if( FD_ISSET(this->socket,&sready) )
	    {
	    	result = true;
	    }
	    else
	    {
	        result = false;
	    }

	    return result;
	}
}
