/*
 * ServerConnection.h
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#ifndef SERVERCONNECTION_H_
#define SERVERCONNECTION_H_

#include "Connection.h"
#include "GameConnection.h"
#include "GamePacket.h"

namespace net
{
	class ServerConnection : public GameConnection {
	public:
		ServerConnection();
		ServerConnection(Connection connection);
		virtual ~ServerConnection();
		void Send(GamePacket data);
		GamePacket Receive();
		bool HasData();
	private:
		Connection connection;
	};
}
#endif /* SERVERCONNECTION_H_ */
