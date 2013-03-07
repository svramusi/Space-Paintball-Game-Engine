#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <errno.h>
#include <arpa/inet.h>

#include "SDL-1.2.15/include/SDL.h"

#include "net/Net.h"
#include "net/Constants.hpp"
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
void SendInputToServer(int input);
int GetUpdateFromServer();
bool TimeForRendering();
void UpdateStatistics();
void FPSControl();

int main( int argc, char * argv[] )
{
//	TestCollectGameState* test = new TestCollectGameState();
//	test->PrintGameState();
//	delete test;

	bool quit = false;
	GameEngine gameEngine;
	Uint32 time = SDL_GetTicks();
	bool needToRedraw = true;

	///////////////////////////////////////////////////////////////////
	// Client Socket Initialization
	///////////////////////////////////////////////////////////////////
	int host_port= 1101;
	char* host_name="127.0.0.1";

	struct sockaddr_in my_addr;

	char buffer[1024];
	int bytecount;
	int buffer_len=0;

	int hsock;
	int * p_int;
	int err;

	hsock = socket(AF_INET, SOCK_STREAM, 0);
	if(hsock == -1){
		printf("Error initializing socket %d\n",errno);
		goto FINISH;
	}

	p_int = (int*)malloc(sizeof(int));
	*p_int = 1;

	if( (setsockopt(hsock, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1 )||
		(setsockopt(hsock, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1 ) ){
		printf("Error setting options %d\n",errno);
		free(p_int);
		goto FINISH;
	}
	free(p_int);

	my_addr.sin_family = AF_INET ;
	my_addr.sin_port = htons(host_port);

	memset(&(my_addr.sin_zero), 0, 8);
	my_addr.sin_addr.s_addr = inet_addr(host_name);

	if( connect( hsock, (struct sockaddr*)&my_addr, sizeof(my_addr)) == -1 ){
		if((err = errno) != EINPROGRESS){
			fprintf(stderr, "Error connecting socket %d\n", errno);
			goto FINISH;
		}
	}
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

		///////////////////////////////////////////////////////////
		// Client socket work
		///////////////////////////////////////////////////////////
		buffer_len = 1024;

		memset(buffer, '\0', buffer_len);

		printf("Enter some text to send to the server (press enter)\n");
		fgets(buffer, 1024, stdin);
		buffer[strlen(buffer)-1]='\0';

		if( (bytecount=send(hsock, buffer, strlen(buffer),0))== -1){
			fprintf(stderr, "Error sending data %d\n", errno);
			goto FINISH;
		}
		printf("Sent bytes %d\n", bytecount);

		if((bytecount = recv(hsock, buffer, buffer_len, 0))== -1){
			fprintf(stderr, "Error receiving data %d\n", errno);
			goto FINISH;
		}
		printf("Recieved bytes %d\nReceived string \"%s\"\n", bytecount, buffer);

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

		NetUtils::wait( DeltaTime );
	} // End Client Game Loop

	close(hsock);
FINISH:
;
}

int GetUpdateFromServer()
{
	return 0;
}

void SendInputToServer(int input)
{

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
