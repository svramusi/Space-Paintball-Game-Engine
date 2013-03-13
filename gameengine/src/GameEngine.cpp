/*
 * GameEngine.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: amarppatel
 */

#include "GameEngine.h"

GameEngine::GameEngine(unsigned int startTime) {
    physics = new PhysicsEngine(-9.8f, 0.0f, startTime);
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

void
GameEngine::insertPhysicsObject(
    CollidableObject *obj, float mass, Velocity linVel, Force linForce,
    Velocity angVel, Force angForce, Point angPos
) {
    physics->insertPhysicsObject(obj, mass, linVel, linForce, angVel, 
        angForce, angPos);
}

void GameEngine::UpdatePhysics(unsigned int timeStep) {
    physics->updateWorld(timeStep);
}

std::vector<physicsInfo>
GameEngine::getUpdatedObjects() {
    return physics->getUpdatedObjects();
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
