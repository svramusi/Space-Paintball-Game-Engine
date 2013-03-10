/*
 * ServerSocket.h
 *
 *  Created on: Mar 8, 2013
 *      Author: amarppatel
 */

#ifndef SERVERSOCKET_H_
#define SERVERSOCKET_H_

#include "net/Socket.h"
#include "net/Address.h"

namespace net
{
	class ServerSocket : public Socket {
	public:
		ServerSocket();
		ServerSocket( int theSocket );
		virtual ~ServerSocket();

		Address& GetClientAddress();
		void SetClientAddress( Address& theClientAddress );

	private:
		Address clientAddress;
	};
}
#endif /* SERVERSOCKET_H_ */
