/*
 * Socket.h
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "GameEngine.pb.h"
#include "GameEngine.pb.cc"
#include "Net.h"
//#include "Point.h"

using namespace google::protobuf::io;

namespace net
{
	class Socket {
	public:
		Socket();
		virtual ~Socket();

		bool Setup();
		void Close();
		bool IsOpen() const;
		bool HasData() const;
		bool Send( const void * data, int size );
		int Receive( void * data, int size );
		int Read();
		google::protobuf::uint32 ReadHeader( char *buf );
		void ReadBody( google::protobuf::uint32 siz );

	protected:
		int socket;
		int err;
	};
}
#endif /* SOCKET_H_ */
