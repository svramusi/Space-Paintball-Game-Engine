/*
 * ClientConnection.h
 *
 *  Created on: Feb 10, 2013
 *      Author: amarppatel
 */

#ifndef CLIENTCONNECTION_H_
#define CLIENTCONNECTION_H_

#include "Constants.hpp"
#include "GamePacket.h"
#include "Connection.h"
#include "NetUtils.h"
#include "Address.h"
#include "ServerConnection.h"
#include "ServerMasterConnection.h"

namespace net
{
	class ClientConnection {
	public:
		ClientConnection(Address* clientAddress);
		virtual ~ClientConnection();
		void connect(Address* serverMasterAddress);
		void Send(GamePacket* data);
		GamePacket* Receive();
		bool HasData() const;
	private:
		Address* clientAddress;
		ServerConnection* serverConnection;
	};
}
#endif /* CLIENTCONNECTION_H_ */
