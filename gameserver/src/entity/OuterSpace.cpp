/*
 * OuterSpace.cpp
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#include "entity/OuterSpace.h"
#include "GameState.h"

OuterSpace::OuterSpace(string name) : Place(name) {
	this->gameState = new GameState(name);
}

OuterSpace::~OuterSpace() {
	delete gameState;
}

GameState* OuterSpace::GetGameState() {
	return gameState;
}

void OuterSpace::AcceptVisitor(GameVisitor* visitor) {
	visitor->Visit(this);
}
