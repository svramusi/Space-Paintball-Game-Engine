/*
 * Game.cpp
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#include "Game.h"

Game::Game() {
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::AcceptVisitor(GameVisitor *visitor) {
	visitor->Visit(this);
}

void Game::AddPlace(Place* place) {
	places.push_back(place);
}

vector<Place *>& Game::GetPlaces() {
	return places;
}
