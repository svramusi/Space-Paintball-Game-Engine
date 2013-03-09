/*
 * GameEngine.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: amarppatel
 */

#include "GameEngine.h"

GameEngine::GameEngine() {
    printf("Game Engine Initialized\n");

    physics = new PhysicsEngine(-9.8f, 0.0f);

    CollidableObject *stationary_sphere;
    CollidableObject *bouncing_sphere;

    float radii[3];

    Point stationary_center;
    stationary_center.x = 4.0f;
    stationary_center.y = 3.0f;
    stationary_center.z = 0.0f;

    radii[0] = 1;
    radii[1] = 1;
    radii[2] = 1;

    stationary_sphere = new Sphere(-1, stationary_center, 1.0f, false);


    Point bouncing_center;
    bouncing_center.x = 4.0f;
    bouncing_center.y = 8.0f;
    bouncing_center.z = 0.0f;

    radii[0] = 2;
    radii[1] = 1;
    radii[2] = 0;

    bouncing_sphere = new AABB(-1, bouncing_center, radii, true);


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

    physics->insertPhysicsObject(stationary_sphere, 10, zeroVel, zeroForce, zeroVel, zeroForce, zeroPoint);
    physics->insertPhysicsObject(bouncing_sphere, 10, ballVel, zeroForce, zeroVel, zeroForce, zeroPoint);

    //for(float i=0.0f; i<10.0f; i=i+0.1f)
    for(int i=0; i<200; i++)
        physics->updateWorld(i);
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
