/*
 * GameEngine.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: amarppatel
 */

#include "GameEngine.h"

GameEngine::GameEngine() {
	printf("Game Engine Initialized\n");
}

GameEngine::~GameEngine() {
	// TODO Auto-generated destructor stub
}

void GameEngine::UpdateAI() {
	printf("Game Engine AI Updated\n");
}

void GameEngine::UpdatePhysics() {
	printf("Game Engine Physics Updated\n");
}

void GameEngine::Render() {
	printf("Game Rendered\n");
}
