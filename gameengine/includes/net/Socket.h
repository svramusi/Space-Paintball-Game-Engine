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

#include "Net.h"

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
		int Peek( void * buffer, int size );
		bool Send( const void * data, int size );
		int Receive( void * data, int size );
		int ReceiveWaitAll( void * data, int size );
		int Read();

	protected:
		int socket;
		int err;
	};
}
#endif /* SOCKET_H_ */
