/*
 * ServerMasterConnection.h
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#ifndef SERVERMASTERCONNECTION_H_
#define SERVERMASTERCONNECTION_H_

#include "GameConnection.h"
#include "ServerConnection.h"
#include "Constants.hpp"

namespace net
{
	class ServerMasterConnection : public GameConnection {
	public:
		/*
		 * Just creates an instance, but does nothing else.
		 * We don't want to open the port right away after
		 * creating the socket, since we might just be setting
		 * up the data structures.
		 */
		ServerMasterConnection(int port);
		virtual ~ServerMasterConnection();
		/*
		 * This function does all the work of creating the socket:
		 * 1. Create the socket,
		 * 2. Set the options (protocol, etc.),
		 * 3. Set the port, and
		 * 4. Start listening
		 */
		void Init();
		/*
		 * When "hasData()" is true, the client is trying to connect.
		 * This function accepts the connection, and returns the
		 * ServerSocket that will be used for that connection.
		 */
		ServerConnection AcceptConection(int &IP);

		virtual void Send(GamePacket data);
		virtual GamePacket Receive();
		virtual bool HasData();

	private:
		int port;
		Connection connection;
	};
}
#endif /* SERVERMASTERCONNECTION_H_ */
