/*
 * Planet.cpp
 *
 *  Created on: Feb 19, 2013
 *      Author: amarppatel
 */

#include "entity/Planet.h"

Planet::Planet(string name) : Prop(name) {
	this->gameState = new GameState(name);
}

Planet::~Planet() {
	delete gameState;
}

GameState* Planet::GetGameState() {
	return gameState;
}

void Planet::AcceptVisitor(GameVisitor* visitor) {
	visitor->Visit(this);
}
