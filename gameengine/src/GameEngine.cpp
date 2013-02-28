/*
 * GameEngine.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: amarppatel
 */

#include "GameEngine.h"

GameEngine::GameEngine() {
    printf("Game Engine Initialized\n");

    physics = new PhysicsEngine();

    Point stationary_center;
    stationary_center.x = 4;
    stationary_center.y = 3;
    stationary_center.z = 0;

    sphere_t stationary_sphere;
    stationary_sphere.center = stationary_center;
    stationary_sphere.radius = 2;


    Point bouncing_center;
    bouncing_center.x = 4;
    bouncing_center.y = 8;
    bouncing_center.z = 0;

    sphere_t bouncing_sphere;
    bouncing_sphere.center = bouncing_center;
    bouncing_sphere.radius = 1;


    Velocity zeroVel;
    zeroVel.x = 0;
    zeroVel.y = 0;
    zeroVel.z = 0;

    Velocity ballVel;
    ballVel.x = 0;
    ballVel.y = -9.8;
    ballVel.z = 0;

    Force zeroForce;
    zeroForce.x = 0;
    zeroForce.y = 0;
    zeroForce.z = 0;

    Point zeroPoint;
    zeroPoint.x = 0;
    zeroPoint.y = 0;
    zeroPoint.z = 0;

    physics->insertPhysicsObject(stationary_sphere, 10, zeroVel, zeroForce, zeroVel, zeroForce, zeroPoint);
    physics->insertPhysicsObject(bouncing_sphere, 10, ballVel, zeroForce, zeroVel, zeroForce, zeroPoint);
}

GameEngine::~GameEngine() {
    // TODO Auto-generated destructor stub

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
