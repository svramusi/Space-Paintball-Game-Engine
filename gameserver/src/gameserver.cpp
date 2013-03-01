#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "SDL-1.2.15/include/SDL.h"

#include "net/Net.h"
#include "net/Connection.h"
#include "net/NetUtils.h"
#include "net/ServerMasterConnection.h"
#include "utils/gun_utils.h"
#include "physicsengine.h"
#include "GameEngine.h"
#include "TestCollectGameState.h"

using namespace std;
using namespace net;

const int ServerMasterPort = 30000;
const int ClientPort = 30001;
const int ProtocolId = 0x99887766;
const float DeltaTime = 0.25f;
const float SendRate = 0.25f;
const float TimeOut = 10.0f;

int PollForOSMessages(bool* quit);
int GetInputFromClient(bool* quit, ServerMasterConnection& connection);
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

	// Initialize the client connection
	Address serverMasterAddress(127,0,0,1, ServerMasterPort);
	ServerMasterConnection serverMasterConnection(serverMasterAddress);

	bool serverMasterInitialized = serverMasterConnection.Init();

	if(!serverMasterInitialized)
	{
		perror("Problem initializing server master.");
		return 1;
	}

	serverMasterConnection.Listen();

	// Server Game Loop
	while(!quit)
	{
		/*
		 * Poll for OS Events/Messages; this is
		 * the event pump.
		 */
		PollForOSMessages(&quit);

		int input = GetInputFromClient(&quit, serverMasterConnection);

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

		serverMasterConnection.Update( DeltaTime );
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
int GetInputFromClient(bool* quit, ServerMasterConnection& connection)
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
		// If input from all clients is to shutdown game server, set quit
		//else if() {quit = true;}
		else
		{
			// TODO: Determine the input based on message from client.
			input = 1;
		}

		printf( "received packet from client\n" );
	}

	return input;
}
