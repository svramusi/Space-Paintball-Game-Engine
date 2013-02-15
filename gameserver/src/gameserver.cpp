#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SDL/SDL.h>

#include "net/Net.h"
#include "net/Connection.h"
#include "net/NetUtils.h"
#include "utils/gun_utils.h"
#include "physicsengine.h"
#include "GameEngine.h"

using namespace std;
using namespace net;

const int ServerPort = 30000;
const int ClientPort = 30001;
const int ProtocolId = 0x99887766;
const float DeltaTime = 0.25f;
const float SendRate = 0.25f;
const float TimeOut = 10.0f;

int StartGameMasterServer();
int PollForOSMessages();
int GetInput();
bool TimeForUpdatingAI();
bool TimeForUpdatingPhysics();
bool TimeForRendering();
void UpdateStatistics();
void FPSControl();

int main( int argc, char * argv[] )
{

	GunUtils *guns = new GunUtils("example.xml");
	guns->print_guns();
	delete guns;

//	PhysicsEngine *physics_engine = new PhysicsEngine();
//	physics_engine->updateWorld();
//	delete physics_engine;

	//startGameMasterServer();

	GameEngine gameEngine;
	bool quit = false;
	int time = SDL_GetTicks();

	// Game Loop
	while(!quit)
	{
		// Poll for OS Messages.
		PollForOSMessages();

		int i = GetInput();

		///////////////////////////////////////////////////////////
		//Update Game State
		if(TimeForUpdatingAI())
		{
			/*
			 * AI will be implemented using an Open Source library.
			 * Update the AI of any NPC in the game.
			 */
			gameEngine.UpdateAI();
		}

		if(TimeForUpdatingPhysics())
		{
			/*
			 * With the given player inputs, run one
			 * frame of the physics simulation to move
			 * the characters and objects in the game.
			 */
			gameEngine.UpdatePhysics();
		}

		/*
		 * Get information from the game engine to update
		 * the player score, health, etc. (since typically
		 * the HUD is not rendered by the game engine, but
		 * separately).
		 */
		UpdateStatistics();
		///////////////////////////////////////////////////////////

		if(TimeForRendering())
		{
			/*
			 * Redraw the game.
			 */
			gameEngine.Render();
		}

		FPSControl();
	} // End Game Loop

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
 * Updating physics should be done as often as
 * possible.
 */
bool TimeForUpdatingPhysics()
{
	return true;
}

/*
 * Updating AI should be done once or twice per second.
 */
bool TimeForUpdatingAI()
{
	return true;
}

int PollForOSMessages()
{
	return 0;
}

/*
 * Check the keyboard/mouse state and identify any user
 * input. Also, if there are players over the network,
 * get their inputs.
 */
int GetInput()
{
	return 0;
}

int StartGameMasterServer()
{
	Connection connection( ProtocolId, TimeOut );

		if ( !connection.Start( ServerPort ) )
		{
			printf( "could not start connection on port %d\n", ServerPort );
			//Throw exception.
			return 1;
		}

		connection.Listen();

		while ( true )
		{
			if ( connection.IsConnected() )
			{
				unsigned char packet[] = "server to client";
				connection.SendPacket( packet, sizeof( packet ) );
			}

			while ( true )
			{
				unsigned char packet[256];
				int bytes_read = connection.ReceivePacket( packet, sizeof(packet) );
				if ( bytes_read == 0 )
					break;
				printf( "received packet from client\n" );
			}

			connection.Update( DeltaTime );
			NetUtils::wait( DeltaTime );
		}

		return 0;
}
