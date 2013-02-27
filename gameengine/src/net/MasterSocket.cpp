/*
 * MasterSocket.cpp
 *
 *  Created on: Feb 27, 2013
 *      Author: amarppatel
 */

#include "net/MasterSocket.h"

namespace net {

MasterSocket::MasterSocket() {
	socket = 0;
}

MasterSocket::~MasterSocket() {
	Close();
}

bool MasterSocket::Open( unsigned short port ) {
	assert( !IsOpen() );

	// create socket
	socket = ::socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

	if ( socket <= 0 )
	{
		printf( "failed to create socket\n" );
		socket = 0;
		return false;
	}

	int opt = TRUE;
	/*
	 *  set master socket to allow multiple connections (this is just a good habit) it will
	 *  work without this
	 */
	if(setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0)
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
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

	// try to specify a maximum of 3 pending connections for the mater socket
	if( listen(socket, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
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

Socket MasterSocket::Accept(const Address & source) {
	int new_socket;
	int addrlen;
	fd_set readfds;

	assert( source.GetAddress() != 0 );
	assert( source.GetPort() != 0 );

	// clear the socket set
	FD_ZERO(&readfds);

	// add master socket to the set
	FD_SET(socket, &readfds);

	// add child sockets to set
	for( int i = 0; i < max_clients; i++ )
	{
		int s = client_socket[i];
		if(s > 0)
		{
			FD_SET( s, &readfds );
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	// Check if socket has data
	////////////////////////////////////////////////////////////////////////////////
	// Determine if the socket has data.
    bool            result;
    struct timeval  nowait;

    //bzero((char *)&nowait,sizeof(nowait));
    memset((char *)&nowait,0,sizeof(nowait));

    // See if there is a result/activity on one of the sockets.
    int activity = select(max_clients + 3, &readfds, NULL, NULL, &nowait);

    if((activity < 0) && (errno != EINTR))
    {
    	printf("select error");
    }

    // if something happened on the master socket, then its an incoming connection.
    if( FD_ISSET(socket, &readfds) )
    {
    	result = true;
    }
    else
    {
        result = false;
    }
    ////////////////////////////////////////////////////////////////////////////////

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl( source.GetAddress() );
	address.sin_port = htons( (unsigned short) source.GetPort() );

	addrlen = sizeof(address);

	if((new_socket = accept(socket, (sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

    printf("New connection, socket fd: %d, IP: %s, port: %d \n", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

	return Socket(new_socket);
}

bool MasterSocket::HasData() const
{
	return true;
}

void MasterSocket::Close()
{
	if ( socket != 0 )
	{
		close( socket );
		socket = 0;
	}
}

bool MasterSocket::IsOpen() const
{
	return socket != 0;
}

bool MasterSocket::Send( const Address & destination, const void * data, int size )
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

int MasterSocket::Receive( Address & sender, void * data, int size )
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

	sender = Address( address, port );

	return received_bytes;
}

} /* namespace net */
