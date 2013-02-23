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
#include "Address.h"
#include "Constants.hpp"

namespace net
{
	class GameConnection {
	public:
		GameConnection(Address* address);
		virtual ~GameConnection();

		virtual void Send(GamePacket* data) = 0;
		virtual GamePacket* Receive() = 0;
		virtual bool HasData() const = 0;

	protected:
		Connection* connection;
		Address* address;
	};
}
#endif /* GAMECONNECTION_H_ */
