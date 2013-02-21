/*
 * CollectGameState.cpp
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#include "CollectGameState.h"

CollectGameState::CollectGameState() {
	// TODO Auto-generated constructor stub

}

CollectGameState::~CollectGameState() {
	// TODO Auto-generated destructor stub
}

void CollectGameState::Visit(OuterSpace* outerSpace) {
	placesGameStateMap.insert(make_pair(outerSpace, outerSpace->GetGameState()));
}

void CollectGameState::Visit(SuperHero* superHero) {
	charactersGameStateMap.insert(make_pair(superHero, superHero->GetGameState()));
}

void CollectGameState::Visit(Astronaut* astronaut) {
	charactersGameStateMap.insert(make_pair(astronaut, astronaut->GetGameState()));
}

void CollectGameState::Visit(Planet* planet) {
	propsGameStateMap.insert(make_pair(planet, planet->GetGameState()));
}

void CollectGameState::Visit(SpaceShip* spaceShip) {
	propsGameStateMap.insert(make_pair(spaceShip, spaceShip->GetGameState()));
}

map<Entity*, GameState*, EntityComparer>* CollectGameState::GetGameState() {
	map<Entity*, GameState*, EntityComparer> gameStateMap;

	printf(">>>>!!!\n");
	printf(">>>>>>>>>>%d\n", placesGameStateMap.size());

	gameStateMap.insert(placesGameStateMap.begin(), placesGameStateMap.end());

	printf("111111\n");
	gameStateMap.insert(charactersGameStateMap.begin(), charactersGameStateMap.end());

	gameStateMap.insert(propsGameStateMap.begin(), propsGameStateMap.end());

	return &gameStateMap;
}

map<Character*, GameState*, EntityComparer>* CollectGameState::GetCharactersGameState() {
	return &charactersGameStateMap;
}

map<Prop*, GameState*, EntityComparer>* CollectGameState::GetPropsGameState() {
	return &propsGameStateMap;
}

map<Place*, GameState*, EntityComparer>* CollectGameState::GetPlacesGameState() {
	return &placesGameStateMap;
}

map<Entity*, GameState*, EntityComparer>* CollectGameState::Collect(Game& game) {
	//CollectGameState* collectGameState = NavigationVisitor::ExecuteVisitor<CollectGameState>(new CollectGameState(), game);
	CollectGameState* collectGameState = NavigationVisitor::ExecuteVisitor(new CollectGameState(), &game);
	return collectGameState->GetGameState();


	//map<Entity*, GameState*> gameStateMap;
	//return gameStateMap;
}
