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

    ////////////////////////////////////////////////////////////////////////////////
    // send new connection greeting message
    ////////////////////////////////////////////////////////////////////////////////

    //a message
    char *message = "ECHO Daemon\r\n";
    if( send(new_socket, message, strlen(message), 0) != strlen(message))
    {
    	perror("send");
    }

    puts("Welcome message sent successfully");

    // add new socket to array of sockets
    for(int i = 0; i < max_clients; i++)
    {
    	int s = client_socket[i];
    	if( s == 0 )
    	{
    		client_socket[i] = new_socket;
    		printf("Adding to list of sockets as %d\n", i);
    		i = max_clients;
    	}
    }
    ////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////
    // Else its some IO operation on some other socket
    ////////////////////////////////////////////////////////////////////////////////
    for(int i = 0; i < max_clients; i++)
    {
    	int s = client_socket[i];

    	if( FD_ISSET( s, &readfds ) )
    	{
    		// Check if it was for closing, and also read the incoming message.
    		int valread;
    		char buffer[1025];
    		if((valread = read( s, buffer, 1024 )) == 0)
    		{
    			// Somebody disconnected, get their details and print
    			getpeername(s, (sockaddr*)&address, (socklen_t*)&addrlen);
    			printf("Host disconnected, IP: %s, port: %d \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

    			//Close the socket and mark as 0 in list for reuse.
    			close(s);
    			client_socket[i] = 0;
    		}
    		else
    		{
    			// Echo back the message that came in.
    			// Set the terminating NULL byte on  the end of the data read
    			buffer[valread = '\0'];
    			send( s, buffer, strlen(buffer), 0);
    		}
    	}
    }
    ////////////////////////////////////////////////////////////////////////////////

	return Socket(new_socket);
}

bool MasterSocket::HasData() const
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
	{
		perror("recvfrom");
		return 0;
	}

	unsigned int address = ntohl( from.sin_addr.s_addr );
	unsigned short port = ntohs( from.sin_port );

	std::string message((char*)data, size);

	printf("Received packet from %s:%d\n Data: %s\n\n", inet_ntoa(from.sin_addr), port, message.c_str());

	sender = Address( address, port );

	return received_bytes;
}

} /* namespace net */
