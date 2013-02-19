/*
 * OuterSpace.cpp
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#include "entity/OuterSpace.h"
#include "GameState.h"

OuterSpace::OuterSpace() {
	// TODO Auto-generated constructor stub

}

OuterSpace::~OuterSpace() {
	// TODO Auto-generated destructor stub
}

GameState* OuterSpace::GetGameState() {
	return new GameState("OuterSpace!");
}

void OuterSpace::AcceptVisitor(GameVisitor* visitor) {
	visitor->Visit(this);
}
