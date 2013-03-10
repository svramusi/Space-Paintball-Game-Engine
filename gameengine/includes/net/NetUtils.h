/*
 * NetUtils.h
 *
 *  Created on: Feb 10, 2013
 *      Author: amarppatel
 */

#ifndef NETUTILS_H_
#define NETUTILS_H_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <errno.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "net/GameEngine.pb.h"
#include "net/Socket.h"

using namespace google::protobuf::io;
using namespace std;

namespace net
{
	class NetUtils {
	public:
		NetUtils();
		virtual ~NetUtils();
		static void Wait( float seconds );
		void Send( net::GameEngine& input, net::Socket& socket );
		static google::protobuf::uint32 ReadHeader( char *buf );
		static net::GameEngine* ReadBody( net::Socket* serverSocket, google::protobuf::uint32 size );
		static net::GameEngine* GetGameEnginePayload();
		static void SetPhysicsInfo( net::PhysicsInfo* physicsInfo, float value );
	};
}
#endif /* NETUTILS_H_ */
