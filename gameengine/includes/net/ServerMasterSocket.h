/*
 * ServerMasterSocket.h
 *
 *  Created on: Mar 8, 2013
 *      Author: amarppatel
 */

#ifndef SERVERMASTERSOCKET_H_
#define SERVERMASTERSOCKET_H_

#include <string>
#include "net/Address.h"
#include "net/Socket.h"
#include "net/ServerSocket.h"

using namespace std;

namespace net
{
	class ServerMasterSocket : public Socket {
	public:
		ServerMasterSocket();
		virtual ~ServerMasterSocket();

		bool Open( unsigned short port );
		ServerSocket* Accept( Address& sender );
		//static void* SocketHandler( void* lp );
	};
}
#endif /* SERVERMASTERSOCKET_H_ */
