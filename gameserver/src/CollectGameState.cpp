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

map<Entity*, GameState*>& CollectGameState::GetGameState() {
	map<Entity*, GameState*> gameStateMap;

	gameStateMap.insert(charactersGameStateMap.begin(), charactersGameStateMap.end());
	gameStateMap.insert(propsGameStateMap.begin(), propsGameStateMap.end());
	gameStateMap.insert(placesGameStateMap.begin(), placesGameStateMap.end());

	return gameStateMap;
}

map<Character*, GameState*>& CollectGameState::GetCharactersGameState() {
	return charactersGameStateMap;
}

map<Prop*, GameState*>& CollectGameState::GetPropsGameState() {
	return propsGameStateMap;
}

map<Place*, GameState*>& CollectGameState::GetPlacesGameState() {
	return placesGameStateMap;
}

map<Entity*, GameState*>& CollectGameState::Collect(Game& game) {
	//CollectGameState* collectGameState = NavigationVisitor::ExecuteVisitor<CollectGameState>(new CollectGameState(), game);
	CollectGameState* collectGameState = NavigationVisitor::ExecuteVisitor(new CollectGameState(), &game);
	return collectGameState->GetGameState();


	//map<Entity*, GameState*> gameStateMap;
	//return gameStateMap;
}
