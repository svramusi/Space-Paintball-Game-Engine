#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <map>

#include "SDL-1.2.15/include/SDL.h"

#include "net/Net.h"
#include "net/Constants.hpp"
#include "net/ReliableConnection.h"
#include "net/FlowControl.h"
#include "net/NetUtils.h"
#include "utils/gun_utils.h"
#include "physicsengine.h"
#include "GameEngine.h"
#include "TestCollectGameState.h"

//#define SHOW_ACKS

using namespace std;
using namespace net;

int PollForOSMessages(bool* quit);
int GetInputFromClient(bool* quit, ReliableConnection* connection);
void SendUpdateToClient(const float & sendRate, float& sendAccumulator, ReliableConnection* connection);
bool TimeForRendering();
void UpdateStatistics();
void FPSControl();

int main( int argc, char * argv[] )
{
	//TestCollectGameState* test = new TestCollectGameState();
	//test->PrintGameState();
	//delete test;

	//GunUtils *guns = new GunUtils("example.xml");
	//guns->print_guns();
	//delete guns;

//	PhysicsEngine *physics_engine = new PhysicsEngine();
//	physics_engine->updateWorld();
//	delete physics_engine;

	//startGameMasterServer();

	GameEngine gameEngine;
	bool quit = false;
	Uint32 time = SDL_GetTicks();
	bool needToRedraw = true;
	map<Address, ReliableConnection*> serverConnections;

	enum Mode
	{
		Server
	};

	Mode mode = Server;
	Address address;

	// Initialize the client connection
	ReliableConnection connection( ProtocolId, TimeOut );

	if ( !connection.Start( MasterServerPort ) )
	{
		printf( "could not start connection on port %d\n", MasterServerPort );
		return 1;
	}

	connection.Listen();

	bool connected = false;
	float sendAccumulator = 0.0f;
	float statsAccumulator = 0.0f;
	int theCurrentServerPort = MasterServerPort;

	FlowControl flowControl;

	// Server Game Loop
	while(!quit)
	{
		if ( connection.IsConnected() )
		{
			flowControl.Update( DeltaTime, connection.GetReliabilitySystem().GetRoundTripTime() * 1000.0f );
		}

		const float sendRate = flowControl.GetSendRate();

		// detect changes in connection state

		if ( mode == Server && connected && !connection.IsConnected() )
		{
			flowControl.Reset();
			printf( "reset flow control\n" );
			connected = false;
		}

		if ( !connected && connection.IsConnected() )
		{
			printf( "client connected to server\n" );
			connected = true;
		}

		if ( !connected && connection.ConnectFailed() )
		{
			printf( "connection failed\n" );
			break;
		}

		sendAccumulator += DeltaTime;

		// Check if someone is trying to connect to the master server.
		if(connection.HasData())
		{
			// Someone is trying to connect so get that client's address.
			unsigned char packet[256];
			Address clientAddress;
			connection.GetAddress(clientAddress, packet, sizeof(packet));

			bool clientAddressAlreadyProcessed = false;

			map<Address, ReliableConnection *>::iterator itr = serverConnections.find(clientAddress);

			if(itr != serverConnections.end())
			{
				clientAddressAlreadyProcessed = true;
			}

			if(!clientAddressAlreadyProcessed)
			{
				printf( "client %d.%d.%d.%d:%d is trying to connect\n",
						clientAddress.GetA(), clientAddress.GetB(), clientAddress.GetC(), clientAddress.GetD(), clientAddress.GetPort() );

				// Initialize the regular server connection for the client to reconnect to.
				ReliableConnection *serverConnection = new ReliableConnection( ProtocolId, TimeOut );


				theCurrentServerPort += 1;
				if ( !serverConnection->Start( theCurrentServerPort ) )
				{
					printf( "could not start connection on port %d\n", theCurrentServerPort );
					//return 1;
				}

				// Start listening for the client.
				//serverConnection->Listen();
				serverConnection->Connect(clientAddress);

				serverConnections.insert(make_pair(clientAddress, serverConnection));

				const float sendRate = flowControl.GetSendRate();
				//printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>%f<<<<<<<<<<<<<<<<<<<<<<<<<<<<<", sendRate);

				SendUpdateToClient(sendRate, sendAccumulator, &connection);

				// Store the regular server address.
				//Address serverAddress(127, 0, 0, 1, theCurrentServerPort);
				// Send the client the regular server address to connect to.
				//SendAddressToClient(sendRate, sendAccumulator, connection, serverAddress);

				/*
				string result;
				ostringstream convert;
				convert << theCurrentServerPort;

				result = convert.str();

				while ( sendAccumulator > 1.0f / sendRate )
				{
					//char * clientAddr = clientAddress.ToString().c_str();
					unsigned char buff [6];
					for(int i = 0; i < result.length(); i++)
					{
						buff[i] = result.at(i);
					}

					// Add string terminator.
					buff[5] = '\0';

					connection.SendPacket( clientAddress, buff, sizeof( buff ) );
					printf("SENT %s\n", buff);
					sendAccumulator -= 1.0f / sendRate;
				}
				*/
			} // End if !map.containsKey(clientAddress)
		}

		for(map<Address, ReliableConnection*>::iterator ii = serverConnections.begin(); ii != serverConnections.end(); ++ii)
		{
			ReliableConnection * serverConnection = ii->second;

			if( serverConnection->HasData() )
			{
				/*
				 * Poll for OS Events/Messages; this is
				 * the event pump.
				 */
				PollForOSMessages(&quit);

				// update flow control

				if ( serverConnection->IsConnected() )
				{
					flowControl.Update( DeltaTime, serverConnection->GetReliabilitySystem().GetRoundTripTime() * 1000.0f );
				}

				const float sendRate = flowControl.GetSendRate();

				// detect changes in server connection state

				if ( mode == Server && connected && !serverConnection->IsConnected() )
				{
					flowControl.Reset();
					printf( "reset flow control\n" );
					connected = false;
				}

				if ( !connected && serverConnection->IsConnected() )
				{
					printf( "client connected to server\n" );
					connected = true;
				}

				if ( !connected && serverConnection->ConnectFailed() )
				{
					printf( "server connection failed\n" );
					break;
				}

				// send and receive packets

				SendUpdateToClient(sendRate, sendAccumulator, serverConnection);

				int input = GetInputFromClient(&quit, serverConnection);

				///////////////////////////////////////////////////////////
				//Update Game State
				//gameEngine.UpdateGameState(input);
				///////////////////////////////////////////////////////////

				/*
				 * Get information from the game engine to update
				 * the player score, health, etc. (since typically
				 * the HUD is not rendered by the game engine, but
				 * separately).
				 */
				//UpdateStatistics();

				FPSControl();

				/*
				 * Play nice with the OS, and give
				 * some CPU for another process.
				 */
				//SDL_Delay(1);

				// show packets that were acked this frame

				#ifdef SHOW_ACKS
				unsigned int * acks = NULL;
				int ack_count = 0;
				serverConnection->GetReliabilitySystem().GetAcks( &acks, ack_count );
				if ( ack_count > 0 )
				{
					printf( "acks: %d", acks[0] );
					for ( int i = 1; i < ack_count; ++i )
						printf( ",%d", acks[i] );
					printf( "\n" );
				}
				#endif

				// update server connection

				serverConnection->Update( DeltaTime );

				// show connection stats

				statsAccumulator += DeltaTime;

				while ( statsAccumulator >= 0.25f && serverConnection->IsConnected() )
				{
					float rtt = serverConnection->GetReliabilitySystem().GetRoundTripTime();

					unsigned int sent_packets = serverConnection->GetReliabilitySystem().GetSentPackets();
					unsigned int acked_packets = serverConnection->GetReliabilitySystem().GetAckedPackets();
					unsigned int lost_packets = serverConnection->GetReliabilitySystem().GetLostPackets();

					float sent_bandwidth = serverConnection->GetReliabilitySystem().GetSentBandwidth();
					float acked_bandwidth = serverConnection->GetReliabilitySystem().GetAckedBandwidth();

					printf( "rtt %.1fms, sent %d, acked %d, lost %d (%.1f%%), sent bandwidth = %.1fkbps, acked bandwidth = %.1fkbps\n",
						rtt * 1000.0f, sent_packets, acked_packets, lost_packets,
						sent_packets > 0.0f ? (float) lost_packets / (float) sent_packets * 100.0f : 0.0f,
						sent_bandwidth, acked_bandwidth );

					statsAccumulator -= 0.25f;
				}

				NetUtils::wait( DeltaTime );
			} // End if serverConnection.HasData().
		} // End for each serverConnection

		// update connection

		connection.Update( DeltaTime );

		// show connection stats

		statsAccumulator += DeltaTime;

		while ( statsAccumulator >= 0.25f && connection.IsConnected() )
		{
			float rtt = connection.GetReliabilitySystem().GetRoundTripTime();

			unsigned int sent_packets = connection.GetReliabilitySystem().GetSentPackets();
			unsigned int acked_packets = connection.GetReliabilitySystem().GetAckedPackets();
			unsigned int lost_packets = connection.GetReliabilitySystem().GetLostPackets();

			float sent_bandwidth = connection.GetReliabilitySystem().GetSentBandwidth();
			float acked_bandwidth = connection.GetReliabilitySystem().GetAckedBandwidth();

			printf( "rtt %.1fms, sent %d, acked %d, lost %d (%.1f%%), sent bandwidth = %.1fkbps, acked bandwidth = %.1fkbps\n",
				rtt * 1000.0f, sent_packets, acked_packets, lost_packets,
				sent_packets > 0.0f ? (float) lost_packets / (float) sent_packets * 100.0f : 0.0f,
				sent_bandwidth, acked_bandwidth );

			statsAccumulator -= 0.25f;
		}

		NetUtils::wait( DeltaTime );
	} // End Server Game Loop

	return 0;
}

void FPSControl()
{

}

void UpdateStatistics()
{

}

/*
 * Keep rendering time at 30 or 50 fps.
 */
bool TimeForRendering()
{
	return true;
}

/*
 * Event pump method; polling method for
 * OS messages.
 */
int PollForOSMessages(bool* quit)
{
/*
	while(SDL_PollEvent(&event))
	{
		switch(eventType)
		{
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_F12)
				{
					quit = true;
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				gameEngine->MouseClick(event.button.x, event.button.y);
				break;

			case SDL_QUIT:
				quit = true;
				break;
		} // End Switch
	}
	*/

	return 0;
}

/*
 * Check the keyboard/mouse state and identify any user
 * input. Also, if there are players over the network,
 * get their inputs.
 */
int GetInputFromClient(bool* quit, ReliableConnection* connection)
{
	int input = 0;
	while ( true )
	{
		unsigned char packet[256];
		int bytes_read = connection->ReceivePacket( packet, sizeof(packet) );
		if ( bytes_read == 0 )
		{
			break;
		}
	}

	return input;
}

void SendUpdateToClient(const float & sendRate, float& sendAccumulator, ReliableConnection* connection) {
	printf("Send rate: %f | Send accumulator: %f\n", sendRate, sendAccumulator);
	while ( sendAccumulator > 1.0f / sendRate )
	{
		unsigned char packet[PacketSize];
		memset( packet, 0, sizeof( packet ) );
		connection->SendPacket( packet, sizeof( packet ) );
		sendAccumulator -= 1.0f / sendRate;
		//unsigned char buff [] = "Hello World!";
		//connection.SendPacket( buff, sizeof( buff ) );
		//sendAccumulator -= 1.0f / sendRate;
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>PACKET SENT<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	}
}
