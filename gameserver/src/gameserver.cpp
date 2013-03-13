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

#include "utils/gun_utils.h"
#include "physicsengine.h"
#include "GameEngine.h"
#include "TestCollectGameState.h"

using namespace std;

int PollForOSMessages( bool* quit );
net::GameEngineMessage* GetInputFromClient( bool* quit, net::ServerSocket* serverSocket );
void SendUpdateToClients( net::GameEngineMessage* input );
bool TimeForRendering();
void UpdateStatistics();
void FPSControl();
bool ClientHasAlreadyConnected( net::Address& clientAddress );
void* SocketHandler( void* );
void ShutdownGameServer();

map<net::Address, net::ServerSocket*> serverConnections;

GameEngine *gameEngine;

int main( int argc, char * argv[] )
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    Uint32 time = SDL_GetTicks();
    gameEngine = new GameEngine(time);

    bool quit = false;
    bool needToRedraw = true;

    /////////////////////////////////////////////////////////////////
    // Setup and listen to server socket
    /////////////////////////////////////////////////////////////////
    net::ServerMasterSocket serverMasterSocket;

    serverMasterSocket.Open( net::MASTER_SOCKET_PORT );
    /////////////////////////////////////////////////////////////////

    pthread_t thread_id = 0;

    // Server Game Loop
    while(!quit)
    {

usleep(500000);

        time = SDL_GetTicks();

        if( serverMasterSocket.HasData() )
        {
            net::Address clientAddress;
            net::ServerSocket* serverSocket = serverMasterSocket.Accept( clientAddress );

            if( !ClientHasAlreadyConnected( clientAddress ) )
            {
                serverConnections.insert( make_pair( clientAddress, serverSocket ) );

                serverSocket->SetSenderAddress( clientAddress );

                printf( "---------------------\nReceived connection from %s\n", clientAddress.ToString().c_str() );
                pthread_create( &thread_id, 0, &SocketHandler, (void*)serverSocket );
                pthread_detach(thread_id);
            }
        }


        gameEngine->UpdatePhysics(time);

        std::vector<physicsInfo> updatedObjects = gameEngine->getUpdatedObjects();
        if(updatedObjects.size() > 0)
        {
            net::GameEngineMessage* payload = net::NetUtils::GetGameEngineCreateMessage(updatedObjects);
            SendUpdateToClients(payload);
        }

    } // End Server Game Loop

    // Reclaim memory.
    ShutdownGameServer();

    if(gameEngine)
        delete gameEngine;
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
net::GameEngineMessage* GetInputFromClient( bool* quit, net::ServerSocket* serverSocket )
{
    net::GameEngineMessage* input;

    ///////////////////////////////////////////////////////////
    // Get data
    ///////////////////////////////////////////////////////////
    char buffer[ 4 ];
    int bytecount = 0;

    memset( buffer, '\0', 4 );

    while ( serverSocket->HasData() )
    {
        bytecount = serverSocket->Peek( buffer, 4 );

        if( bytecount == 0 )
        {
            // Quit reading data from the socket, if there is nothing to read.
            break;
        }

        input = net::NetUtils::ReadBody( serverSocket, net::NetUtils::ReadHeader( buffer ) );
    }
    ///////////////////////////////////////////////////////////

    return input;
}

void SendUpdateToClients( net::GameEngineMessage* input )
{
    for(map<net::Address, net::ServerSocket*>::iterator ii = serverConnections.begin(); ii != serverConnections.end(); ++ii)
    {
        net::ServerSocket* serverSocket = ii->second;

        net::NetUtils::Send( input, serverSocket );
    }
}

bool ClientHasAlreadyConnected( net::Address & clientAddress )
{
    bool clientHasAlreadyConnected = false;

    map<net::Address, net::ServerSocket*>::iterator itr = serverConnections.find( clientAddress );

    if( itr != serverConnections.end() )
    {
        clientHasAlreadyConnected = true;
        printf( "The client %s has already connected\n", clientAddress.ToString().c_str() );
    }

    return clientHasAlreadyConnected;
}

void ShutdownGameServer()
{
    for(map<net::Address, net::ServerSocket*>::iterator ii = serverConnections.begin(); ii != serverConnections.end(); ++ii)
    {
        net::ServerSocket * serverSocket = ii->second;

        delete serverSocket;
    }

    // Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();
}

void* SocketHandler(void* lp)
{
    net::ServerSocket* serverSocket = (net::ServerSocket*) lp;

    char buffer[ 4 ];

    memset(buffer, '\0', 4);

    bool quit = false;

    // Game loop for each client connection.
    while ( !quit )
    {
        /*
         * Poll for OS Events/Messages; this is
         * the event pump.
         */
        PollForOSMessages(&quit);

        // send and receive packets

        if( serverSocket->HasData() )
        {
            net::GameEngineMessage* input = GetInputFromClient( &quit, serverSocket );

            vector<physicsInfo> physicsInfoList = net::NetUtils::GetGameEngineRetrieveObj(input);

            for(int i=0; i < physicsInfoList.size(); i++ ) {
                physicsInfo info = physicsInfoList[i];

cout << endl << "in server and adding object: "
        << " x: " << info.collidableObject->getCenter().x
        << " y: " << info.collidableObject->getCenter().y
        << " z: " << info.collidableObject->getCenter().z << endl;

                gameEngine->insertPhysicsObject( info.collidableObject, info.mass, info.linearVelocity,
                    info.linearForce, info.angularVelocity, info.angularForce, info.angularPosition);
            }

            //SendUpdateToClients( input );
        }

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

        net::NetUtils::Wait( net::DELTA_TIME );
    } // End game loop

    serverSocket->Close();
    delete serverSocket;

    return 0;
}
