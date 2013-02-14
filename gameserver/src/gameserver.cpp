#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
/*
	GunUtils *guns = new GunUtils("example.xml");
	guns->print_guns();
	delete guns;
*/
//	PhysicsEngine *physics_engine = new PhysicsEngine();
//	physics_engine->updateWorld();
//	delete physics_engine;

	//startGameMasterServer();

	GameEngine gameEngine;
	bool quit = false;

	// Game Loop
	while(!quit)
	{
		// Poll for OS Messages.
		PollForOSMessages();

		int i = GetInput();

		if(TimeForUpdatingAI())
		{
			// AI will be implemented using an Open Source library.
			gameEngine.UpdateAI();
		}

		if(TimeForUpdatingPhysics())
		{
			gameEngine.UpdatePhysics();
		}

		UpdateStatistics();

		if(TimeForRendering())
		{
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

bool TimeForRendering()
{
	return true;
}

bool TimeForUpdatingPhysics()
{
	return true;
}


bool TimeForUpdatingAI()
{
	return true;
}

int PollForOSMessages()
{
	return 0;
}

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
