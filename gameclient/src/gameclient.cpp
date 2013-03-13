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

int PollForOSMessages(bool& quit);
int GetInput(bool& quit);
void SendInputToServer(int input);
net::GameEngineMessage* GetUpdateFromServer();
bool TimeForRendering();
void UpdateStatistics();
void FPSControl();

void checkForUpdatesFromServer();
void redraw();

net::ClientSocket clientSocket;

SDL_Rect leftWall;
SDL_Rect rightWall;
SDL_Rect bottom;
SDL_Rect moving1;
SDL_Rect moving2;
SDL_Rect moving3;

CollidableObject *leftWallCO;
CollidableObject *rightWallCO;
CollidableObject *bottomCO;

CollidableObject *moving1CO;
CollidableObject *moving2CO;
CollidableObject *moving3CO;

SDL_Surface* screen;

const int FPS = 30;
const int SDL_START_HEIGHT = 1000;

Uint32 color;
Uint32 color2;

void
initGraphics()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);
    color = SDL_MapRGB(screen->format,0xff,0xff,0xff);
    color2 = SDL_MapRGB(screen->format,0xff,0x00,0xff);


    Uint32 start;

    leftWall.x=10;
    leftWall.y=100;
    leftWall.w=20;
    leftWall.h=200;

    rightWall.x=300;
    rightWall.y=100;
    rightWall.w=20;
    rightWall.h=200;

    bottom.x=75;
    bottom.y=250;
    bottom.w=200;
    bottom.h=20;

    moving1.x=50;
    moving1.y=50;
    moving1.w=10;
    moving1.h=10;

    moving2.x=150;
    moving2.y=75;
    moving2.w=10;
    moving2.h=10;

    moving3.x=155;
    moving3.y=100;
    moving3.w=10;
    moving3.h=10;
}

void
sendGraphicObjectsToServer()
{
    float radii[3];

    Point leftWallCenter;
    leftWallCenter.x = 20.0f;
    leftWallCenter.y = SDL_START_HEIGHT - 200.0f;
    leftWallCenter.z = 0.0f;

    radii[0] = 10;
    radii[1] = 100;
    radii[2] = 0;

    leftWallCO = new AABB(-1, leftWallCenter, radii, false);



    Point rightWallCenter;
    rightWallCenter.x = 310.0f;
    rightWallCenter.y = SDL_START_HEIGHT - 200.0f;
    rightWallCenter.z = 0.0f;

    radii[0] = 10;
    radii[1] = 100;
    radii[2] = 0;

    rightWallCO = new AABB(-1, rightWallCenter, radii, false);



    Point bottomCenter;
    bottomCenter.x = 175.0f;
    bottomCenter.y = SDL_START_HEIGHT - 260.0f;
    bottomCenter.z = 0.0f;

    radii[0] = 100;
    radii[1] = 10;
    radii[2] = 0;

    bottomCO = new AABB(-1, bottomCenter, radii, false);



    Point movingCenter1;
    movingCenter1.x = 55.0f;
    movingCenter1.y = SDL_START_HEIGHT - 55.0f;
    movingCenter1.z = 0.0f;

    radii[0] = 10;
    radii[1] = 10;
    radii[2] = 0;

    moving1CO = new AABB(-1, movingCenter1, radii, true);


    Point movingCenter2;
    movingCenter2.x = 155.0f;
    movingCenter2.y = SDL_START_HEIGHT - 80.0f;
    movingCenter2.z = 0.0f;

    radii[0] = 10;
    radii[1] = 10;
    radii[2] = 0;

#ifdef SWEPT_SHAPES_MODE
    moving2CO = new Sphere(-1, movingCenter2, 10.0f, true);
#else
    moving2CO = new AABB(-1, movingCenter2, radii, true);
#endif

    Point movingCenter3;
    movingCenter3.x = 160.0f;
    movingCenter3.y = SDL_START_HEIGHT - 55.0f;
    movingCenter3.z = 0.0f;

    radii[0] = 10;
    radii[1] = 10;
    radii[2] = 0;

    moving3CO = new AABB(-1, movingCenter3, radii, true);



    Velocity zeroVel;
    zeroVel.x = 0.0f;
    zeroVel.y = 0.0f;
    zeroVel.z = 0.0f;

    Velocity ballVel;
    ballVel.x = 0.0f;
    ballVel.y = -9.8f;
    ballVel.z = 0.0f;

    Force zeroForce;
    zeroForce.x = 0.0f;
    zeroForce.y = 0.0f;
    zeroForce.z = 0.0f;

    Point zeroPoint;
    zeroPoint.x = 0.0f;
    zeroPoint.y = 0.0f;
    zeroPoint.z = 0.0f;



    vector<physicsInfo> physicsInfos;

    physicsInfos.push_back(
        net::NetUtils::GetPhysicsInfo(leftWallCO, 10, zeroVel, zeroForce, zeroVel, zeroForce, zeroPoint)
    );

    physicsInfos.push_back(
        net::NetUtils::GetPhysicsInfo(bottomCO, 10, zeroVel, zeroForce, zeroVel, zeroForce, zeroPoint)
    );

    physicsInfos.push_back(
        net::NetUtils::GetPhysicsInfo(rightWallCO, 10, zeroVel, zeroForce, zeroVel, zeroForce, zeroPoint)
    );

    physicsInfos.push_back(
        net::NetUtils::GetPhysicsInfo(moving1CO, 10, ballVel, zeroForce, zeroVel, zeroForce, zeroPoint)
    );

    physicsInfos.push_back(
        net::NetUtils::GetPhysicsInfo(moving2CO, 10, ballVel, zeroForce, zeroVel, zeroForce, zeroPoint)
    );

#ifndef SWEPT_SHAPES_MODE
    physicsInfos.push_back(
        net::NetUtils::GetPhysicsInfo(moving3CO, 10, ballVel, zeroForce, zeroVel, zeroForce, zeroPoint)
    );
#endif


    net::GameEngineMessage* payload = net::NetUtils::GetGameEngineCreateMessage( physicsInfos );
    net::NetUtils::Send( payload, &clientSocket );
}

int main( int argc, char * argv[] )
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    initGraphics();

    //GameEngine *ge = new GameEngine();
    //delete ge;
    //return 0;


/*
    TestCollectGameState* test = new TestCollectGameState();
    test->PrintGameState();
    delete test;
*/

    bool quit = false;
    Uint32 time = SDL_GetTicks();
    bool needToRedraw = true;

    ///////////////////////////////////////////////////////////////////
    // Initialize socket and connect with server.
    ///////////////////////////////////////////////////////////////////
    clientSocket.Connect( net::HOST_NAME, net::MASTER_SOCKET_PORT );
    ///////////////////////////////////////////////////////////////////

    sendGraphicObjectsToServer();

    // Client Game Loop
    while(!quit)
    {
        /*
         * Poll for OS Events/Messages; this is
         * the event pump.
         */
        PollForOSMessages( quit );

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
            //  quit = true;
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

        int input = GetInput( quit );

        // now you can write buf.data() to the socket
        ///////////////////////////////////////////////////////////

        //SendInputToServer(input);

        ///////////////////////////////////////////////////////////
        //Update Game State Copy
        checkForUpdatesFromServer();

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
        }

        redraw();

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

void
checkForUpdatesFromServer()
{
    net::GameEngineMessage* gameEngineUpdates = GetUpdateFromServer();
    if(gameEngineUpdates == NULL)
        return;

    vector<physicsInfo> updatedObjects = net::NetUtils::GetGameEngineRetrieveObj(gameEngineUpdates);

    if(updatedObjects.size() > 0) {
        for(int i=0; i < updatedObjects.size(); i++) {
            physicsInfo info = updatedObjects[i];

            if(info.collidableObject->getID() == 3)
                moving1CO = info.collidableObject;
            else if(info.collidableObject->getID() == 4)
                moving2CO = info.collidableObject;
            else if(info.collidableObject->getID() == 5)
                moving3CO = info.collidableObject;
        }
    }
}


void
redraw()
{
    //Clear the screen
    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

    moving1.x = moving1CO->getCenter().x;
    moving1.y = SDL_START_HEIGHT - moving1CO->getCenter().y;

    moving2.x = moving2CO->getCenter().x;
    moving2.y = SDL_START_HEIGHT - moving2CO->getCenter().y;

    moving3.x = moving3CO->getCenter().x;
    moving3.y = SDL_START_HEIGHT - moving3CO->getCenter().y;


    SDL_FillRect(screen,&leftWall,color);
    SDL_FillRect(screen,&rightWall,color);
    SDL_FillRect(screen,&bottom,color);

    SDL_FillRect(screen,&moving1,color2);
    SDL_FillRect(screen,&moving2,color2);
    SDL_FillRect(screen,&moving3,color2);

    SDL_Flip(screen);
    if(1000/FPS > SDL_GetTicks())
        SDL_Delay(1000/FPS - (SDL_GetTicks()));
}

net::GameEngineMessage* GetUpdateFromServer()
{
    net::GameEngineMessage* input = NULL;

    ///////////////////////////////////////////////////////////
    // Get data
    ///////////////////////////////////////////////////////////
    char buffer[ 4 ];
    int bytecount = 0;

    memset( buffer, '\0', 4 );

    while ( clientSocket.HasData() )
    {
        bytecount = clientSocket.Peek( buffer, 4 );

        if( bytecount == 0 )
        {
            // Quit reading data from the socket, if there is nothing to read.
            break;
        }

        input = net::NetUtils::ReadBody( &clientSocket, net::NetUtils::ReadHeader( buffer ) );
    }
    ///////////////////////////////////////////////////////////

    return input;
}

void SendInputToServer( int input )
{
/*
    ///////////////////////////////////////////////////////////////////
    // Initialize payload
    ///////////////////////////////////////////////////////////////////
    vector<physicsInfo> physicsInfos;
    physicsInfos.push_back( net::NetUtils::GetPhysicsInfo( 1.0f ) );
    physicsInfos.push_back( net::NetUtils::GetPhysicsInfo( 2.0f ) );
    net::GameEngineMessage* payload = net::NetUtils::GetGameEngineCreateMessage( physicsInfos );
    ///////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    // Client socket work - send payload to server
    ///////////////////////////////////////////////////////////////////
    net::NetUtils::Send( payload, &clientSocket );
    ///////////////////////////////////////////////////////////////////
*/
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
int PollForOSMessages(bool& quit)
{
	SDL_Event event;

    while( SDL_PollEvent( &event ) )
    {
        switch( event.type )
        {
/*
            case SDL_KEYDOWN:
            	if(event.key.keysym.sym == SDLK_F12)
                {
                    quit = true;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                gameEngine->MouseClick(event.button.x, event.button.y);
                break;
*/
            case SDL_QUIT:
                quit = true;
                break;
        } // End Switch
    }

    return 0;
}

int GetInput(bool& quit)
{
    return 0;
}
