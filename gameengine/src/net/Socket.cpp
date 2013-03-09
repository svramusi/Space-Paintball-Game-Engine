/*
 * Socket.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#include "net/Socket.h"

namespace net
{
	Socket::Socket()
	{
		socket = 0;
	}

	Socket::~Socket()
	{
		Close();
	}

	bool Socket::Setup()
	{
		assert( !IsOpen() );

		// create socket

		socket = ::socket( AF_INET, SOCK_STREAM, 0 );

		if ( socket <= 0 )
		{
			printf("Error initializing socket %d\n", errno);
			socket = 0;
			return false;
		}

		// set socket options.
		int on = 1;
		if( (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int)) == -1 ) ||
			(setsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, &on, sizeof(int)) == -1 ) )
		{
			printf("Error setting options %d\n", errno);
			socket = 0;
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

	bool Socket::Send( const void * data, int size )
	{
		assert( data );
		assert( size > 0 );

		if ( socket == 0 )
			return false;

		int send_bytes = 0;

		if( (send_bytes = send( socket, (const char*)data, size, 0 ) ) == -1)
		{
			fprintf( stderr, "Error sending data %d\n", errno );
			return false;
		}

		printf( "Sent bytes %d\n", send_bytes );

		return send_bytes == size;
	}

	int Socket::Receive( void * data, int size )
	{
		assert( data );
		assert( size > 0 );

		if ( socket == 0 )
			return false;

		sockaddr_in from;
		socklen_t fromLength = sizeof( from );

		int received_bytes;

		if( ( received_bytes = recv( socket, (char*)data, size, 0 ) ) == -1 )
		{
			fprintf( stderr, "Error receiving data %d\n", errno );
		}

		if ( received_bytes <= 0 )
			return 0;

		return received_bytes;
	}

	int Socket::ReceiveWaitAll( void * data, int size )
	{
		assert( data );
		assert( size > 0 );

		if ( socket == 0 )
			return false;

		sockaddr_in from;
		socklen_t fromLength = sizeof( from );

		int received_bytes;

		if( ( received_bytes = recv( socket, (char*)data, size, MSG_WAITALL ) ) == -1 )
		{
			fprintf( stderr, "Error receiving data %d\n", errno );
		}

		if ( received_bytes <= 0 )
			return 0;

		return received_bytes;
	}

	bool Socket::HasData() const
	{
		int timeOut = 100; //ms
		fd_set socketReadSet;
		FD_ZERO(&socketReadSet);
		FD_SET(socket,&socketReadSet);
		struct timeval tv;
		if (timeOut) {
			tv.tv_sec  = timeOut / 1000;
			tv.tv_usec = (timeOut % 1000) * 1000;
		} else {
			tv.tv_sec  = 0;
			tv.tv_usec = 0;
		} // if

		if (select(socket+1,&socketReadSet,0,0,&tv) == -1) {
			perror("select()\n");
			return false;
		} // if
		int res = FD_ISSET(socket,&socketReadSet);

		return res != 0;
	}

	int Socket::Peek( void * buffer, int size )
	{
		int bytecount = 0;

		// Peek into the socket and get the packet size.
		if( ( bytecount = recv( socket, (char *) buffer, size, MSG_PEEK ) ) == -1 )
		{
			fprintf( stderr, "Error peeking at received data %d\n", errno );
		}

		printf( "Peek(): First read byte count is %d\n", bytecount );

		return bytecount;
	}
}
