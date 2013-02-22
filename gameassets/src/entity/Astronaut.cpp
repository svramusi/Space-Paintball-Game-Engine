/*
 * Astronaut.cpp
 *
 *  Created on: Feb 19, 2013
 *      Author: amarppatel
 */

#include "entity/Astronaut.h"

Astronaut::Astronaut(string name) : Character(name) {
	this->gameState = new GameState(name);
}

Astronaut::~Astronaut() {
	delete gameState;
}

GameState* Astronaut::GetGameState() {
	return gameState;
}

void Astronaut::AcceptVisitor(GameVisitor* visitor) {
	visitor->Visit(this);
}
