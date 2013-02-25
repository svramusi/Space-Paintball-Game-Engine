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

ServerMasterConnection* serverMasterConnection;

int StartGameMasterServer();
int PollForOSMessages(bool* quit);
int GetInputFromClient(bool* quit);
int GetInputFromOneClient();
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

	// Initialize the server master connection
	Address* serverMasterAddress = new Address(127,0,0,1, ServerMasterPort);
	serverMasterConnection = new ServerMasterConnection(serverMasterAddress);
	if ( !serverMasterConnection->Init() )
	{
		printf( "could not start connection to server master on port %d\n", serverMasterAddress->GetPort() );
		return 1;
	}

	//StartGameMasterServer();
	// Server Game Loop
	while(!quit)
	{
		/*
		 * Poll for OS Events/Messages; this is
		 * the event pump.
		 */
		PollForOSMessages(&quit);

		//int input = GetInputFromClient(&quit);
		GetInputFromOneClient();

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
		SDL_Delay(1);
	} // End Server Game Loop

	//delete serverMasterAddress;
	//delete serverMasterConnection;

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

int GetInputFromOneClient()
{
	unsigned char packet[] = "server to client: player1 pressed up arrow";
	GamePacket* gamePacket = new GamePacket(packet, sizeof( packet ));
	serverMasterConnection->Send( gamePacket );
	delete gamePacket;

	while ( true )
	{
		unsigned char packet[256];
		GamePacket* gamePacket = serverMasterConnection->Receive();
		if ( gamePacket == NULL )
		{
			break;
		}
		printf( "received packet from sclient\n" );
	}

	serverMasterConnection->Update( DeltaTime );
	NetUtils::wait( DeltaTime );
}

/*
 * Check the keyboard/mouse state and identify any user
 * input. Also, if there are players over the network,
 * get their inputs.
 */
int GetInputFromClient(bool* quit)
{
	if(!quit)
	{
		map<Address*, ServerConnection*>* connections = serverMasterConnection->GetConnections();

		map<Address*, ServerConnection*>::iterator iter;

        for (iter = connections->begin(); iter != connections->end(); iter++) {
        	Address* address = iter->first;
        	ServerConnection* serverConnection = iter->second;

        	if ( serverConnection->IsConnected() )
			{
        		unsigned char packet[] = "server to client";
        		serverConnection->Send(new GamePacket(packet, sizeof(packet)));
			}
        	if( serverConnection->HasData() )
        	{
				while ( true )
				{
					GamePacket* gamePacket = serverConnection->Receive();
					if ( gamePacket == NULL )
					{
						break;
					}
					printf( "received packet from client\n" );
				}
        	}

            serverConnection->Update( DeltaTime );
     		NetUtils::wait( DeltaTime );
        }
	}

	return 0;
}

int StartGameMasterServer()
{
	Connection connection( ProtocolId, TimeOut );

	if ( !connection.Start( ServerMasterPort ) )
	{
		printf( "could not start connection on port %d\n", ServerMasterPort );
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
