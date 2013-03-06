/*
 * Connection.h
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "Net.h"
#include "Socket.h"

namespace net
{
	class Connection {
	public:
		enum Mode
		{
			None,
			Client,
			Server
		};

		Connection();
		Connection(unsigned int protocolId, float timeout);
		virtual ~Connection();

		bool Start( int port );
		void Stop();
		bool IsRunning() const;
		void Listen();
		void Connect( const Address & address );
		bool IsConnecting() const;
		bool HasData() const;
		bool ConnectFailed() const;
		bool IsConnected() const;
		bool IsListening() const;
		Mode GetMode() const;
		virtual void Update( float deltaTime );
		bool SendPacket( Address & theAddress, const unsigned char data[], int size );
		virtual bool SendPacket( const unsigned char data[], int size );
		virtual int ReceivePacket( unsigned char data[], int size );
		int GetHeaderSize() const;
		int GetAddress( Address & sender, unsigned char data[], int size );

	protected:
		virtual void OnStart()		{}
		virtual void OnStop()		{}
		virtual void OnConnect()    {}
		virtual void OnDisconnect() {}

	private:
		void ClearData();

		enum State
		{
			Disconnected,
			Listening,
			Connecting,
			ConnectFail,
			Connected
		};

		unsigned int protocolId;
		float timeout;

		bool running;
		Mode mode;
		State state;
		Socket socket;
		float timeoutAccumulator;
		Address address;
	};
}

#endif /* CONNECTION_H_ */
