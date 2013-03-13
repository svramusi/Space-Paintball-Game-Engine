/*
 * GameEngine.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: amarppatel
 */

#include "GameEngine.h"

#include "SDL.h"

#include <unistd.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char* WINDOW_TITLE = "SDL Start";

const int SDL_START_HEIGHT = 1000;

GameEngine::GameEngine() {
    printf("Game Engine Initialized\n");



    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);

    bool running = true;
    const int FPS = 30;
    Uint32 start;

    SDL_Rect leftWall;
    leftWall.x=10;
    leftWall.y=100;
    leftWall.w=20;
    leftWall.h=200;

    SDL_Rect rightWall;
    rightWall.x=300;
    rightWall.y=100;
    rightWall.w=20;
    rightWall.h=200;

    SDL_Rect bottom;
    bottom.x=75;
    bottom.y=250;
    bottom.w=200;
    bottom.h=20;

    SDL_Rect moving1;
    moving1.x=50;
    moving1.y=50;
    moving1.w=10;
    moving1.h=10;

    SDL_Rect moving2;
    moving2.x=150;
    moving2.y=75;
    moving2.w=10;
    moving2.h=10;

    SDL_Rect moving3;
    moving3.x=155;
    moving3.y=100;
    moving3.w=10;
    moving3.h=10;



    Uint32 color = SDL_MapRGB(screen->format,0xff,0xff,0xff);
    Uint32 color2 = SDL_MapRGB(screen->format,0xff,0x00,0xff);

/*
    while(running) {
        start = SDL_GetTicks();
        SDL_Event event;

        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }



        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );

        SDL_FillRect(screen,&leftWall,color);
        SDL_FillRect(screen,&rightWall,color);
        SDL_FillRect(screen,&bottom,color);

        SDL_FillRect(screen,&moving1,color2);
        SDL_FillRect(screen,&moving2,color2);

        SDL_Flip(screen);
        if(1000/FPS > SDL_GetTicks()-start)
            SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
    }
    SDL_Quit();
*/





    physics = new PhysicsEngine(-9.8f, 0.0f);

    CollidableObject *leftWallCO;
    CollidableObject *rightWallCO;
    CollidableObject *bottomCO;

    CollidableObject *moving1CO;
    CollidableObject *moving2CO;
    CollidableObject *moving3CO;


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

    moving2CO = new AABB(-1, movingCenter2, radii, true);

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


    physics->insertPhysicsObject(leftWallCO, 10, zeroVel, zeroForce, zeroVel, zeroForce, zeroPoint);
    physics->insertPhysicsObject(bottomCO, 10, zeroVel, zeroForce, zeroVel, zeroForce, zeroPoint);
    physics->insertPhysicsObject(rightWallCO, 10, zeroVel, zeroForce, zeroVel, zeroForce, zeroPoint);

//    physics->insertPhysicsObject(moving1CO, 10, ballVel, zeroForce, zeroVel, zeroForce, zeroPoint);
//    physics->insertPhysicsObject(moving2CO, 10, ballVel, zeroForce, zeroVel, zeroForce, zeroPoint);
    physics->insertPhysicsObject(moving2CO, 10, zeroVel, zeroForce, zeroVel, zeroForce, zeroPoint);
    physics->insertPhysicsObject(moving3CO, 10, ballVel, zeroForce, zeroVel, zeroForce, zeroPoint);

    for(float i=0.0f; i<10.0f; i=i+0.03f)
    //for(int i=0; i<200; i++)
    {
        physics->updateWorld(i);

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
        if(1000/FPS > SDL_GetTicks()-start)
            SDL_Delay(1000/FPS - (SDL_GetTicks() - start));

        usleep(50000);
    }


    SDL_Quit();


    delete leftWallCO;
    delete rightWallCO;
    delete bottomCO;
    delete moving1CO;
    delete moving2CO;
}

GameEngine::~GameEngine() {
    if(physics)
        delete physics;
}

/*
 * Updating physics should be done as often as
 * possible.
 */
bool GameEngine::TimeForUpdatingPhysics()
{
    return true;
}

/*
 * Updating AI should be done once or twice per second.
 */
bool GameEngine::TimeForUpdatingAI()
{
    return true;
}

void GameEngine::UpdateAI(int input) {
    printf("Game Engine AI Updated\n");
}

void GameEngine::UpdatePhysics(int input) {
    printf("Game Engine Physics Updated\n");
    //Physics need to be class variable ?
    //physics.updateWorld( timeStep)
}

void GameEngine::UpdateGameState(int input) {
    if(TimeForUpdatingAI())
    {
        /*
         * AI will be implemented using an Open Source library.
         * Update the AI of any NPC in the game.
         */
        UpdateAI(input);
    }

    if(TimeForUpdatingPhysics())
    {
        /*
         * With the given player inputs, run one
         * frame of the physics simulation to move
         * the characters and objects in the game.
         */
        UpdatePhysics(input);
    }

    printf("Game State Updated\n");
}

void GameEngine::Render() {
    printf("Game Rendered\n");
}
