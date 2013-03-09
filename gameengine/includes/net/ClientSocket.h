/*
 * ClientSocket.h
 *
 *  Created on: Mar 8, 2013
 *      Author: amarppatel
 */

#ifndef CLIENTSOCKET_H_
#define CLIENTSOCKET_H_

#include "net/Socket.h"

namespace net
{
	class ClientSocket : public Socket {
	public:
		ClientSocket();
		virtual ~ClientSocket();

		bool Connect( const char* host_name, unsigned short port );
	};
}
#endif /* CLIENTSOCKET_H_ */
