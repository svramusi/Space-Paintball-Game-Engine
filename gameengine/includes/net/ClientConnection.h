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
#include "GameConnection.h"

namespace net
{
	class ClientConnection : public GameConnection {
	public:
		ClientConnection(Address* clientAddress);
		virtual ~ClientConnection();
		void Connect(Address* serverMasterAddress);
		void Send(GamePacket* data);
		GamePacket* Receive();
		bool HasData() const;
	private:
		ServerConnection* serverConnection;
	};
}
#endif /* CLIENTCONNECTION_H_ */
