#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "SDL-1.2.15/include/SDL.h"

#include "net/Net.h"
#include "net/Connection.h"
#include "net/NetUtils.h"
#include "GameEngine.h"
#include "TestCollectGameState.h"

using namespace std;
using namespace net;

const int ServerPort = 30000;
const int ClientPort = 30001;
const int ProtocolId = 0x99887766;
const float DeltaTime = 0.25f;
const float SendRate = 0.25f;
const float TimeOut = 10.0f;
// One frame each 20 milliseconds (i.e. 50 frames per second)
const Uint32 RedrawingPeriod = 20;
const int MaxFrameSkip = 10;

int PollForOSMessages(bool* quit);
int ConnectToGameMasterServer();
int GetInput(bool* quit);
void SendInputToServer(int input);
int GetUpdateFromServer();
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
		}

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

		SendInputToServer(input);

		///////////////////////////////////////////////////////////
		//Update Game State Copy
		int inputFromServer = GetUpdateFromServer();
		// Update local game state (or game state copy).
		gameEngine.UpdateGameState(inputFromServer);
		///////////////////////////////////////////////////////////

		/*
		 * Get information from the game engine to update
		 * the player score, health, etc. (since typically
		 * the HUD is not rendered by the game engine, but
		 * separately).
		 */
		UpdateStatistics();

		if(TimeForRendering())
		{
			/*
			 * Redraw the game.
			 */
			gameEngine.Render();
		}

		FPSControl();

		/*
		 * Play nice with the OS, and give
		 * some CPU for another process.
		 */
		SDL_Delay(1);
	} // End Client Game Loop

	return 0;
}

int GetUpdateFromServer()
{
	// Get the update from server.
	// TODO: Fix this
	//int input = getUpdateFromServer();
	int input = 0;



	return input;
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

int ConnectToGameMasterServer()
{
	Connection connection( ProtocolId, TimeOut );

	if ( !connection.Start( ClientPort ) )
	{
		printf( "could not start connection on port %d\n", ClientPort );
		return 1;
	}

	connection.Connect( Address(127,0,0,1,ServerPort ) );

	bool connected = false;

	while ( true )
	{
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

		unsigned char packet[] = "client to server";
		connection.SendPacket( packet, sizeof( packet ) );

		while ( true )
		{
			unsigned char packet[256];
			int bytes_read = connection.ReceivePacket( packet, sizeof(packet) );
			if ( bytes_read == 0 )
				break;
			printf( "received packet from server\n" );
		}

		connection.Update( DeltaTime );
		NetUtils::wait( DeltaTime );
	}

	return 0;
}

void SendInputToServer(int input)
{
	//TODO: Send input to server
}

int GetInput(bool* quit)
{
	return 0;
}
