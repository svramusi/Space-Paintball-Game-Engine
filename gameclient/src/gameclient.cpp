#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "SDL-1.2.15/include/SDL.h"

#include "net/Net.h"
#include "net/Constants.hpp"
#include "net/ReliableConnection.h"
#include "net/PacketQueue.h"
#include "net/FlowControl.h"
#include "net/NetUtils.h"
#include "GameEngine.h"
#include "TestCollectGameState.h"

//#define SHOW_ACKS

using namespace std;
using namespace net;

// One frame each 20 milliseconds (i.e. 50 frames per second)
const Uint32 RedrawingPeriod = 20;
const int MaxFrameSkip = 10;

int PollForOSMessages(bool* quit);
int GetInput(bool* quit);
void SendInputToServer(int input, const float & sendRate, float & sendAccumulator, ReliableConnection& connection);
int GetUpdateFromServer(ReliableConnection& connection);
bool TimeForRendering();
void UpdateStatistics();
void FPSControl();

int main( int argc, char * argv[] )
{
	TestCollectGameState* test = new TestCollectGameState();
	test->PrintGameState();
	delete test;

	bool quit = false;
	GameEngine gameEngine;
	Uint32 time = SDL_GetTicks();
	bool needToRedraw = true;

	enum Mode
	{
		Client
	};

	Mode mode = Client;
	Address address;

	if ( argc >= 2 )
	{
		int a,b,c,d;
		if ( sscanf( argv[1], "%d.%d.%d.%d", &a, &b, &c, &d ) )
		{
			address = Address(a,b,c,d,ServerPort);
		}
	}

	// Initialize the client connection
	ReliableConnection connection( ProtocolId, TimeOut );

	if ( !connection.Start( ClientPort ) )
	{
		printf( "could not start connection on port %d\n", ClientPort );
		return 1;
	}

	connection.Connect( address );

	bool connected = false;
	float sendAccumulator = 0.0f;
	float statsAccumulator = 0.0f;

	FlowControl flowControl;

	// Client Game Loop
	while(!quit)
	{
		/*
		 * Poll for OS Events/Messages; this is
		 * the event pump.
		 */
		PollForOSMessages(&quit);

		Uint32 actualTime = SDL_GetTicks();
		int frames = 0;

		while(actualTime >= RedrawingPeriod && frames < MaxFrameSkip)
		{
			/*
			 * If the computer is too slow to run at
			 * the desired FPS, try to execute more than
			 * one update per redrawing frame (i.e.,
			 * skip frames).
			 */

			/*
			 * If 20 ms have passed since the last time
			 * we ran a game cycle, then run another
			 * cycle.
			 */
			time += RedrawingPeriod;

			//TODO: fix this
			//keyboard->cycle();
			//if(!gameEngine->cycle(k))
			//{
			//	quit = true;
			//}

			actualTime = SDL_GetTicks();
			needToRedraw = true;
			frames++;
		} // End inner while loop.

		if(time < actualTime)
		{
			/*
			 * If after skipping the maximum number
			 * of frames, we have not yet caught up,
			 * it may be game lost focus or something;
			 * so, don't try to catch up.
			 */
			time = actualTime;
		}

		if(needToRedraw)
		{
			//TODO: fix this
			//game->draw();
			needToRedraw = false;
		}

		int input = GetInput(&quit);

		// update flow control
		if ( connection.IsConnected() )
		{
			flowControl.Update( DeltaTime, connection.GetReliabilitySystem().GetRoundTripTime() * 1000.0f );
		}

		const float sendRate = flowControl.GetSendRate();

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

		SendInputToServer(input, sendRate, sendAccumulator, connection);

		///////////////////////////////////////////////////////////
		//Update Game State Copy
		int inputFromServer = GetUpdateFromServer( connection );
		// Update local game state (or game state copy).
		//gameEngine.UpdateGameState(inputFromServer);
		///////////////////////////////////////////////////////////

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


		/*
		 * Get information from the game engine to update
		 * the player score, health, etc. (since typically
		 * the HUD is not rendered by the game engine, but
		 * separately).
		 */
		//UpdateStatistics();

		if(TimeForRendering())
		{
			/*
			 * Redraw the game.
			 */
			//gameEngine.Render();
		}

		FPSControl();

		/*
		 * Play nice with the OS, and give
		 * some CPU for another process.
		 */
		//SDL_Delay(1);

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
	} // End Client Game Loop

	return 0;
}

int GetUpdateFromServer(ReliableConnection& connection)
{
	while ( true )
	{
		unsigned char packet[256];
		int bytes_read = connection.ReceivePacket( packet, sizeof(packet) );
		if ( bytes_read == 0 )
			break;

		printf( "received packet from server\n" );
	}
}

void SendInputToServer(int input, const float & sendRate, float & sendAccumulator, ReliableConnection& connection)
{
	while ( sendAccumulator > 1.0f / sendRate )
	{
		unsigned char packet[PacketSize];
		memset( packet, 0, sizeof( packet ) );
		connection.SendPacket( packet, sizeof( packet ) );
		sendAccumulator -= 1.0f / sendRate;
	}
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

int GetInput(bool* quit)
{
	return 0;
}
