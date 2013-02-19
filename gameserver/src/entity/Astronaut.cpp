/*
 * Astronaut.cpp
 *
 *  Created on: Feb 19, 2013
 *      Author: amarppatel
 */

#include "entity/Astronaut.h"

Astronaut::Astronaut(string name) {
	this->name = name;
	this->gameState = new GameState(name);
}

Astronaut::~Astronaut() {
	// TODO Auto-generated destructor stub
}

GameState* Astronaut::GetGameState() {
	return gameState;
}

void Astronaut::AcceptVisitor(GameVisitor* visitor) {
	visitor->Visit(this);
}
