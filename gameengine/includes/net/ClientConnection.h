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
#include "GameConnection.h"

namespace net
{
	class ClientConnection : public GameConnection {
	public:
		ClientConnection(Address& clientAddress);
		virtual ~ClientConnection();
		bool Init();
		void Connect(Address& serverMasterAddress);
		bool SendPacket( const unsigned char data[], int size );
		int ReceivePacket( unsigned char data[], int size );
		bool HasData() const;
		bool ConnectFailed() const;
		void Update( float deltaTime );
		bool IsConnected() const;
	};
}
#endif /* CLIENTCONNECTION_H_ */
