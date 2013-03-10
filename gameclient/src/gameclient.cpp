#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <errno.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <iostream>

#include "SDL-1.2.15/include/SDL.h"

#include "net/Net.h"
#include "net/Constants.hpp"
#include "net/NetUtils.h"
#include "net/ClientSocket.h"
#include "net/GameEngine.pb.h"

#include "GameEngine.h"
#include "TestCollectGameState.h"

using namespace std;

// One frame each 20 milliseconds (i.e. 50 frames per second)
const Uint32 RedrawingPeriod = 20;
const int MaxFrameSkip = 10;

int PollForOSMessages(bool* quit);
int GetInput(bool* quit);
void SendInputToServer(int input);
int GetUpdateFromServer();
bool TimeForRendering();
void UpdateStatistics();
void FPSControl();

net::ClientSocket clientSocket;

int main( int argc, char * argv[] )
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	GameEngine *ge = new GameEngine();
    delete ge;
    //return 0;

	TestCollectGameState* test = new TestCollectGameState();
	test->PrintGameState();
	delete test;

	bool quit = false;
	GameEngine gameEngine;
	Uint32 time = SDL_GetTicks();
	bool needToRedraw = true;

	///////////////////////////////////////////////////////////////////
	// Initialize socket and connect with server.
	///////////////////////////////////////////////////////////////////
	clientSocket.Connect( net::HOST_NAME, net::MASTER_SOCKET_PORT );
	///////////////////////////////////////////////////////////////////

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

		// now you can write buf.data() to the socket
		///////////////////////////////////////////////////////////

		SendInputToServer(input);

		///////////////////////////////////////////////////////////
		//Update Game State Copy
		int inputFromServer = GetUpdateFromServer();
		// Update local game state (or game state copy).
		//gameEngine.UpdateGameState(inputFromServer);
		///////////////////////////////////////////////////////////

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

		net::NetUtils::Wait( net::DELTA_TIME );
	} // End Client Game Loop

	clientSocket.Close();
	// Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();
}

int GetUpdateFromServer()
{
	return 0;
}

void SendInputToServer( int input )
{
	///////////////////////////////////////////////////////////////////
	// Initialize payload
	///////////////////////////////////////////////////////////////////
	net::GameEngine* payload = net::NetUtils::GetGameEnginePayload();
	///////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////
	// Client socket work - send payload to server
	///////////////////////////////////////////////////////////////////
	net::NetUtils::Send( payload, &clientSocket );
	///////////////////////////////////////////////////////////////////
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
