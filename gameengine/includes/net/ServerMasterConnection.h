/*
 * ServerMasterConnection.h
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#ifndef SERVERMASTERCONNECTION_H_
#define SERVERMASTERCONNECTION_H_

#include <map>
#include <string>

#include "GameConnection.h"
#include "ServerConnection.h"
#include "Constants.hpp"
#include "Address.h"

using namespace std;

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
		ServerMasterConnection(Address& address);
		virtual ~ServerMasterConnection();
		/*
		 * This function does all the work of creating the socket:
		 * 1. Create the socket,
		 * 2. Set the options (protocol, etc.),
		 * 3. Set the port, and
		 * 4. Start listening
		 */
		bool Init();
		/*
		 * When "hasData()" is true, the client is trying to connect.
		 * This function accepts the connection, and returns the
		 * ServerSocket that will be used for that connection.
		 */
		ServerConnection AcceptConection(Address& address);

		void Listen();
		bool HasData() const;
		bool IsConnected() const;
		bool SendPacket( const unsigned char data[], int size );
		int ReceivePacket( unsigned char data[], int size );
		void Update( float deltaTime );

		map<Address, ServerConnection> GetConnections();

		//virtual void Send(GamePacket* data);
		//virtual GamePacket* Receive();

	private:
		map<Address, ServerConnection> addressToConnectionMap;
	};
}
#endif /* SERVERMASTERCONNECTION_H_ */
