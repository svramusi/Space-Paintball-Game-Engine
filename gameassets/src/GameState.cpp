/*
 * GameState.cpp
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#include "GameState.h"

GameState::GameState(string gameState) {
	this->gameState = gameState + " Game State";
}

GameState::~GameState() {
	// TODO Auto-generated destructor stub
}

string GameState::GetState() {
	return this->gameState;
}

