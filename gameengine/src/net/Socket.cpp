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

	Socket::Socket(int& theSocket) {
		socket = theSocket;
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

		if ( bind( socket, (const sockaddr*) &address, sizeof(address) ) < 0 )
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

	/*
	 * Listen will only work for TCP connections.
	 */
	bool Socket::Listen()
	{
		if(listen(socket,5) < 0)
		{
			printf("failed to listen\n");
			Close();
			return false;
		}

		return true;
	}

	Socket Socket::AcceptConnection()
	{
		struct sockaddr_in cli_addr;
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>1\n");
		socklen_t clilen = sizeof(sockaddr_in);
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>2\n");
		int newSocket = accept(socket,
				 (struct sockaddr *) &cli_addr,
				 &clilen);
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>3\n");
		if (newSocket < 0)
		{
		   printf("ERROR on accept");
		   Close();
		   return Socket();
		}

		return Socket(newSocket);
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
		/*
		// Determine if the socket has data.
	    bool            result = false;
	    fd_set          sready;
	    struct timeval  nowait;

	    FD_ZERO(&sready);
	    FD_SET((unsigned int)this->socket,&sready);
	    //bzero((char *)&nowait,sizeof(nowait));
	    memset((char *)&nowait,0,sizeof(nowait));

	    int returnValue = select(this->socket+1,&sready,NULL,NULL,&nowait);

	    if(returnValue == -1)
	    {
	    	perror("select()");
	    }
	    else
	    {
	    	printf("Data is available for reading now.\n");
	    }

	    if( FD_ISSET(this->socket,&sready) )
	    {
	    	result = true;
	    }
	    else
	    {
	        result = false;
	    }

	    return result;
	    */
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

		//printf("res>>>>>>>>>>>>>>>>>>>>>%d\n", res);

		return res != 0;
	}
}
