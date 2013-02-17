/*
 * Game.cpp
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#include "Game.h"

Game::Game() {
	// TODO Auto-generated constructor stub

}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::AcceptVisitor(GameVisitor &visitor) {
	visitor.Visit(this);
}
