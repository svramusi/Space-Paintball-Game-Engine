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
#include "Address.h"

namespace net
{
	class ServerConnection : public GameConnection {
	public:
		ServerConnection(Address* address);
		virtual ~ServerConnection();
		void Send(GamePacket* data);
		GamePacket* Receive();
		bool HasData() const;
		bool IsConnected() const;
		void Update( float deltaTime );
	};
}
#endif /* SERVERCONNECTION_H_ */
