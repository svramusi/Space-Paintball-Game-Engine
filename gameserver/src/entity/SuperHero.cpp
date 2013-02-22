/*
 * SuperHero.cpp
 *
 *  Created on: Feb 19, 2013
 *      Author: amarppatel
 */

#include "entity/SuperHero.h"

SuperHero::SuperHero(string name) : Character(name) {
	this->gameState = new GameState(name);
}

SuperHero::~SuperHero() {
	delete gameState;
}


GameState* SuperHero::GetGameState() {
	return gameState;
}

void SuperHero::AcceptVisitor(GameVisitor* visitor) {
	visitor->Visit(this);
}
