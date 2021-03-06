/*
 * CollectGameState.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef COLLECTGAMESTATE_H_
#define COLLECTGAMESTATE_H_

#include <map>
#include <stdio.h>

#include "BaseVisitor.h"
#include "GameState.h"
#include "Game.h"
#include "entity/Entity.h"
#include "entity/Character.h"
#include "entity/Prop.h"
#include "entity/Place.h"
#include "entity/OuterSpace.h"
#include "entity/Planet.h"
#include "entity/SpaceShip.h"
#include "entity/SuperHero.h"
#include "entity/Astronaut.h"

#include "NavigationVisitor.h"

using namespace std;

class CollectGameState : public BaseVisitor {
public:
	CollectGameState();
	virtual ~CollectGameState();

	map<Entity*, GameState*, EntityComparer>* GetGameState();
	//TODO: Probably should return copy of data not actual reference.
	map<Character*, GameState*, EntityComparer>* GetCharactersGameState();
	//TODO: Probably should return copy of data not actual reference.
	map<Prop*, GameState*, EntityComparer>* GetPropsGameState();
	//TODO: Probably should return copy of data not actual reference.
	map<Place*, GameState*, EntityComparer>* GetPlacesGameState();

	// Places
	void Visit(OuterSpace* outerSpace);

	// Characters
	void Visit(SuperHero* superHero);
	void Visit(Astronaut* astronaut);

	// Props
	void Visit(Planet* planet);
	void Visit(SpaceShip* spaceShip);

	static map<Entity*, GameState*, EntityComparer>* Collect(Game* game);
private:
	map<Character*, GameState*, EntityComparer>* charactersGameStateMap;
	map<Prop*, GameState*, EntityComparer>* propsGameStateMap;
	map<Place*, GameState*, EntityComparer>* placesGameStateMap;
};

#endif /* COLLECTGAMESTATE_H_ */
