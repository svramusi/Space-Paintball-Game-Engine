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
#include "GameConnection.h"
#include "Connection.h"
#include "NetUtils.h"

namespace net
{
	class ClientConnection : GameConnection {
	public:
		ClientConnection(int clientPort);
		virtual ~ClientConnection();
		void connect(int IP, int port);
		void Send(GamePacket data);
		GamePacket Receive();
		bool HasData();
	private:
		int clientPort;
		Connection connection;
	};
}
#endif /* CLIENTCONNECTION_H_ */
