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

    Point rect_center;
    rect_center.x = 4;
    rect_center.y = 3;
    rect_center.z = 0;

    aabb_t rect;
    rect.center = rect_center;
    rect.radii[0] = 2;
    rect.radii[1] = 1;
    rect.radii[2] = 0;


    Point block_center;
    block_center.x = 4;
    block_center.y = 8;
    block_center.z = 0;

    aabb_t block;
    block.center = block_center;
    block.radii[0] = 1;
    block.radii[1] = 1;
    block.radii[2] = 1;


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

    physics->insertPhysicsObject(rect, 10, zeroVel, zeroForce, zeroVel, zeroForce, zeroPoint);
    physics->insertPhysicsObject(block, 10, ballVel, zeroForce, zeroVel, zeroForce, zeroPoint);
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
