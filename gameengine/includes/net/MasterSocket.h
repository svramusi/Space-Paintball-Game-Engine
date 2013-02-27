/*
 * MasterSocket.h
 *
 *  Created on: Feb 27, 2013
 *      Author: amarppatel
 */

#ifndef MASTERSOCKET_H_
#define MASTERSOCKET_H_

#include "Socket.h"
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <arpa/inet.h>

namespace net {

#define TRUE 1
#define FALSE 0

class MasterSocket {
public:
	MasterSocket();
	virtual ~MasterSocket();

	Socket Accept(const Address & source);
	bool Open( unsigned short port );
	void Close();
	bool IsOpen() const;
	bool HasData() const;
	bool Send( const Address & destination, const void * data, int size );
	int Receive( Address & sender, void * data, int size );

private:
	int socket;
	int client_socket[30];
	int max_clients = 30;
};

} /* namespace net */
#endif /* MASTERSOCKET_H_ */
