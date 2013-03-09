/*
 * ServerSocket.h
 *
 *  Created on: Mar 8, 2013
 *      Author: amarppatel
 */

#ifndef SERVERSOCKET_H_
#define SERVERSOCKET_H_

#include "net/Socket.h"

namespace net
{
	class ServerSocket : public Socket {
	public:
		ServerSocket();
		ServerSocket( int theSocket );
		virtual ~ServerSocket();
	};
}
#endif /* SERVERSOCKET_H_ */
