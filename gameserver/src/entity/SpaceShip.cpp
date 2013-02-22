/*
 * SpaceShip.cpp
 *
 *  Created on: Feb 19, 2013
 *      Author: amarppatel
 */

#include "entity/SpaceShip.h"

SpaceShip::SpaceShip(string name) : Prop(name) {
	this->gameState = new GameState(name);
}

SpaceShip::~SpaceShip() {
	delete gameState;
}

GameState* SpaceShip::GetGameState() {
	return gameState;
}

void SpaceShip::AcceptVisitor(GameVisitor* visitor) {
	visitor->Visit(this);
}
