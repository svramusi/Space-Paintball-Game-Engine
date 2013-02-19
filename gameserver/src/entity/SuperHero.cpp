/*
 * SuperHero.cpp
 *
 *  Created on: Feb 19, 2013
 *      Author: amarppatel
 */

#include "entity/SuperHero.h"

SuperHero::SuperHero(string name) {
	this->name = name;
	this->gameState = new GameState(name);
}

SuperHero::~SuperHero() {
	// TODO Auto-generated destructor stub
}


GameState* SuperHero::GetGameState() {
	return gameState;
}

void SuperHero::AcceptVisitor(GameVisitor* visitor) {
	visitor->Visit(this);
}
