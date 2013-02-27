/*
 * Socket.h
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/select.h>
#include <unistd.h>
#include "Net.h"
#include "Address.h"

namespace net
{
	class Socket {
	public:
		Socket();
		Socket(int & theSocket);
		virtual ~Socket();

		bool Open( unsigned short port );
		void Close();
		bool IsOpen() const;
		bool HasData() const;
		bool Send( const Address & destination, const void * data, int size );
		int Receive( Address & sender, void * data, int size );

	private:
		int socket;
	};
}
#endif /* SOCKET_H_ */
