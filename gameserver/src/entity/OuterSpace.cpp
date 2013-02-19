/*
 * OuterSpace.cpp
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#include "entity/OuterSpace.h"
#include "GameState.h"

OuterSpace::OuterSpace(string name) {
	this->name = name;
	this->gameState = new GameState(name);
}

OuterSpace::~OuterSpace() {
	// TODO Auto-generated destructor stub
}

GameState* OuterSpace::GetGameState() {
	return gameState;
}

void OuterSpace::AcceptVisitor(GameVisitor* visitor) {
	visitor->Visit(this);
}
