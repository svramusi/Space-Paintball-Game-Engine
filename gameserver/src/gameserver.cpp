#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
int GetInputFromClient(bool* quit, ReliableConnection& connection);
void SendUpdateToClient(const float & sendRate, float& sendAccumulator, ReliableConnection& connection);
bool TimeForRendering();
void UpdateStatistics();
void FPSControl();

int main( int argc, char * argv[] )
{
	TestCollectGameState* test = new TestCollectGameState();
	test->PrintGameState();
	delete test;

	GunUtils *guns = new GunUtils("example.xml");
	guns->print_guns();
	delete guns;

//	PhysicsEngine *physics_engine = new PhysicsEngine();
//	physics_engine->updateWorld();
//	delete physics_engine;

	//startGameMasterServer();

	GameEngine gameEngine;
	bool quit = false;
	Uint32 time = SDL_GetTicks();
	bool needToRedraw = true;

	enum Mode
	{
		Server
	};

	Mode mode = Server;
	Address address;

	// Initialize the client connection
	ReliableConnection connection( ProtocolId, TimeOut );

	if ( !connection.Start( ServerPort ) )
	{
		printf( "could not start connection on port %d\n", ServerPort );
		return 1;
	}

	connection.Listen();

	bool connected = false;
	float sendAccumulator = 0.0f;
	float statsAccumulator = 0.0f;

	FlowControl flowControl;

	// Server Game Loop
	while(!quit)
	{
		/*
		 * Poll for OS Events/Messages; this is
		 * the event pump.
		 */
		PollForOSMessages(&quit);

		// update flow control

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

		// send and receive packets

		sendAccumulator += DeltaTime;

		SendUpdateToClient(sendRate, sendAccumulator, connection);

		int input = GetInputFromClient(&quit, connection);

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

		// update connection
		connection.Update( DeltaTime );

		// show packets that were acked this frame

		#ifdef SHOW_ACKS
		unsigned int * acks = NULL;
		int ack_count = 0;
		connection.GetReliabilitySystem().GetAcks( &acks, ack_count );
		if ( ack_count > 0 )
		{
			printf( "acks: %d", acks[0] );
			for ( int i = 1; i < ack_count; ++i )
				printf( ",%d", acks[i] );
			printf( "\n" );
		}
		#endif

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
int GetInputFromClient(bool* quit, ReliableConnection& connection)
{
	int input = 0;
	while ( true )
	{
		unsigned char packet[256];
		int bytes_read = connection.ReceivePacket( packet, sizeof(packet) );
		if ( bytes_read == 0 )
		{
			break;
		}
	}

	return input;
}

void SendUpdateToClient(const float & sendRate, float& sendAccumulator, ReliableConnection& connection) {
	while ( sendAccumulator > 1.0f / sendRate )
	{
		unsigned char packet[PacketSize];
		memset( packet, 0, sizeof( packet ) );
		connection.SendPacket( packet, sizeof( packet ) );
		sendAccumulator -= 1.0f / sendRate;
	}
}
