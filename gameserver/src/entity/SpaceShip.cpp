/*
 * SpaceShip.cpp
 *
 *  Created on: Feb 19, 2013
 *      Author: amarppatel
 */

#include "entity/SpaceShip.h"

SpaceShip::SpaceShip(string name) {
	this->name = name;
	this->gameState = new GameState(name);
}

SpaceShip::~SpaceShip() {
	// TODO Auto-generated destructor stub
}

GameState* SpaceShip::GetGameState() {
	return gameState;
}

void SpaceShip::AcceptVisitor(GameVisitor* visitor) {
	visitor->Visit(this);
}
