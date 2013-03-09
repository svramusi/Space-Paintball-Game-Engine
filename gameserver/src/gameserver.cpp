#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <map>
#include <errno.h>
#include <arpa/inet.h>

#include "SDL-1.2.15/include/SDL.h"

#include "net/Net.h"
#include "net/Constants.hpp"
#include "net/NetUtils.h"
#include "net/Address.h"
#include "net/ServerMasterSocket.h"
#include "net/ServerSocket.h"
#include "net/GameEngine.pb.h"
#include "net/GameEngine.pb.cc"

#include "utils/gun_utils.h"
#include "physicsengine.h"
#include "GameEngine.h"
#include "TestCollectGameState.h"

#include <iostream>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

using namespace google::protobuf::io;

using namespace std;
using namespace net;

int PollForOSMessages(bool* quit);
int GetInputFromClient(bool* quit);
void SendUpdateToClient();
bool TimeForRendering();
void UpdateStatistics();
void FPSControl();
bool ClientHasAlreadyConnected( Address& clientAddress );
void* SocketHandler( void* );
google::protobuf::uint32 ReadHeader( char *buf );
void ReadBody( ServerSocket* serverSocket, google::protobuf::uint32 size );
void FreeServerConnections();

map<Address, ServerSocket*> serverConnections;

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

	/////////////////////////////////////////////////////////////////
	// Setup and listen to server socket
	/////////////////////////////////////////////////////////////////
	ServerMasterSocket serverMasterSocket;

	serverMasterSocket.Open( MASTER_SOCKET_PORT );
	/////////////////////////////////////////////////////////////////

	pthread_t thread_id = 0;

 	// Server Game Loop
	while(!quit)
	{
		if( serverMasterSocket.HasData() )
		{
			Address clientAddress;
			ServerSocket* serverSocket = serverMasterSocket.Accept( clientAddress );

			if( !ClientHasAlreadyConnected( clientAddress ) )
			{
				serverConnections.insert( make_pair( clientAddress, serverSocket ) );

				printf( "---------------------\nReceived connection from %s\n", clientAddress.ToString().c_str() );
				pthread_create( &thread_id, 0, &SocketHandler, (void*)serverSocket );
				pthread_detach(thread_id);
			}
		}
	} // End Server Game Loop

	// Reclaim memory.
	FreeServerConnections();
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
int GetInputFromClient(bool* quit)
{
	int input = 0;

	return input;
}

void SendUpdateToClient()
{
}

google::protobuf::uint32 ReadHeader( char *buf )
{
  google::protobuf::uint32 size;
  google::protobuf::io::ArrayInputStream ais( buf,4 );
  CodedInputStream coded_input( &ais );
  coded_input.ReadVarint32( &size );//Decode the HDR and get the size
  printf( "Size of payload is %d\n", size );

  return size;
}

void ReadBody( ServerSocket* serverSocket, google::protobuf::uint32 size )
{
  int bytecount;
  net::Point payload;
  char buffer [ size + 4 ];//size of the payload and hdr
  //Read the entire buffer including the hdr
  bytecount = serverSocket->ReceiveWaitAll( (void *)buffer, 4 + size );

  printf( "Second read byte count is %d\n", bytecount );

  //Assign ArrayInputStream with enough memory
  google::protobuf::io::ArrayInputStream ais( buffer, size + 4 );
  CodedInputStream coded_input( &ais );
  //Read an unsigned integer with Varint encoding, truncating to 32 bits.
  coded_input.ReadVarint32( &size );
  //After the message's length is read, PushLimit() is used to prevent the CodedInputStream
  //from reading beyond that length.Limits are used when parsing length-delimited
  //embedded messages
  google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit( size );
  //De-Serialize
  payload.ParseFromCodedStream( &coded_input );
  //Once the embedded message has been parsed, PopLimit() is called to undo the limit
  coded_input.PopLimit( msgLimit );
  //Print the message
  printf( "Message is %s\n", payload.DebugString().c_str() );
}


bool ClientHasAlreadyConnected( Address & clientAddress )
{
	bool clientHasAlreadyConnected = false;

	map<Address, ServerSocket*>::iterator itr = serverConnections.find( clientAddress );

	if( itr != serverConnections.end() )
	{
		clientHasAlreadyConnected = true;
		printf( "The client %s has already connected\n", clientAddress.ToString().c_str() );
	}

	return clientHasAlreadyConnected;
}

void FreeServerConnections()
{
	for(map<Address, ServerSocket*>::iterator ii = serverConnections.begin(); ii != serverConnections.end(); ++ii)
	{
		ServerSocket * serverSocket = ii->second;

		delete serverSocket;
	}
}

void* SocketHandler(void* lp)
{
	ServerSocket* serverSocket = (ServerSocket*) lp;

	char buffer[ 4 ];
	int bytecount = 0;

	memset(buffer, '\0', 4);

	bool quit = false;

	// Game loop for each client connection.
	while (!quit)
	{
		/*
		 * Poll for OS Events/Messages; this is
		 * the event pump.
		 */
		PollForOSMessages(&quit);

		// send and receive packets

		///////////////////////////////////////////////////////////
		// Get data
		///////////////////////////////////////////////////////////
		char buffer[ 4 ];
		int bytecount = 0;

		memset( buffer, '\0', 4 );

		while ( true )
		{
			bytecount = serverSocket->Peek( buffer, 4 );

			if( bytecount == 0 )
			{
				// Quit reading data from the socket, if there is nothing to read.
				break;
			}

			ReadBody( serverSocket, ReadHeader( buffer ) );
		}
		///////////////////////////////////////////////////////////

		SendUpdateToClient();

		int input = GetInputFromClient(&quit);

		///////////////////////////////////////////////////////////
		// Update Game State
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

		NetUtils::wait( DELTA_TIME );
	} // End game loop

	serverSocket->Close();
	delete serverSocket;

	return 0;
}
