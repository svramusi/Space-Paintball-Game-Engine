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

	int Socket::Read()
	{
		int bytecount = 0;
		char buffer[ 4 ];

		memset( buffer, '\0', 4 );

		// Peek into the socket and get the packet size.
		if( ( bytecount = recv( socket, buffer, 4, MSG_PEEK ) ) == -1)
		{
			fprintf( stderr, "Error receiving data %d\n", errno );
		}

		printf( "First read byte count is %d\n", bytecount );

		ReadBody( ReadHeader( buffer ) );

		return bytecount;
	}

	google::protobuf::uint32 Socket::ReadHeader( char *buf )
	{
	  google::protobuf::uint32 size;
	  google::protobuf::io::ArrayInputStream ais( buf,4 );
	  CodedInputStream coded_input( &ais );
	  coded_input.ReadVarint32( &size );//Decode the HDR and get the size
	  printf( "Size of payload is %d\n", size );

	  return size;
	}

	void Socket::ReadBody( google::protobuf::uint32 size )
	{
	  int bytecount;
	  net::Point payload;
	  char buffer [ size + 4 ];//size of the payload and hdr
	  //Read the entire buffer including the hdr
	  if( ( bytecount = recv(socket, (void *)buffer, 4 + size, MSG_WAITALL ) ) == -1 )
	  {
		  fprintf( stderr, "Error receiving data %d\n", errno );
	  }

	  printf( "Second read byte count is %d\n", bytecount );

	  //Assign ArrayInputStream with enough memory
	  google::protobuf::io::ArrayInputStream ais( buffer, size + 4 );
	  CodedInputStream coded_input( &ais );
	  //Read an unsigned integer with Varint encoding, truncating to 32 bits.
	  coded_input.ReadVarint32( &size );
	  //After the message's length is read, PushLimit() is used to prevent the CodedInputStream
	  //from reading beyond that length.Limits are used when parsing length-delimited
	  //embedded messages
	  google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit( size );
	  //De-Serialize
	  payload.ParseFromCodedStream( &coded_input );
	  //Once the embedded message has been parsed, PopLimit() is called to undo the limit
	  coded_input.PopLimit( msgLimit );
	  //Print the message
	  printf( "Message is %s\n", payload.DebugString().c_str() );
	}
}
