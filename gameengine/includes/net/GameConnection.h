/*
 * GameSocket.h
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#ifndef GAMECONNECTION_H_
#define GAMECONNECTION_H_

#include "Connection.h"
#include "GamePacket.h"

namespace net
{
	class GameConnection {
	public:
		GameConnection();
		GameConnection(Connection connection, int localIp);
		virtual ~GameConnection();

		virtual void Send(GamePacket data) = 0;
		virtual GamePacket Receive() = 0;
		virtual bool HasData() = 0;

	private:
		Connection connection;
		int localIp;
	};
}
#endif /* GAMECONNECTION_H_ */
