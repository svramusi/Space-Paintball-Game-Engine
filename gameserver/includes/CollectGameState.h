/*
 * CollectGameState.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef COLLECTGAMESTATE_H_
#define COLLECTGAMESTATE_H_

#include <map>
#include "BaseVisitor.h"
#include "GameState.h"
#include "Game.h"
#include "entity/Entity.h"
#include "entity/Character.h"
#include "entity/Prop.h"
#include "entity/Place.h"

using namespace std;

class CollectGameState : public BaseVisitor {
public:
	CollectGameState();
	virtual ~CollectGameState();

	map<Entity*, GameState*>& GetGameState();
	//TODO: Probably should return copy of data not actual reference.
	map<Character*, GameState*>& GetCharactersGameState();
	//TODO: Probably should return copy of data not actual reference.
	map<Prop*, GameState*>& GetPropsGameState();
	//TODO: Probably should return copy of data not actual reference.
	map<Place*, GameState*>& GetPlacesGameState();

	void visit(OuterSpace& outerSpace);
	static map<Entity*, GameState*>& Collect(Game& game);
private:
	map<Character*, GameState*> charactersGameStateMap;
	map<Prop*, GameState*> propsGameStateMap;
	map<Place*, GameState*> placesGameStateMap;
};

#endif /* COLLECTGAMESTATE_H_ */
