/*
 * Game.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef GAME_H_
#define GAME_H_

#include <vector>

#include "Visitable.h"
#include "GameVisitor.h"
#include "entity/Place.h"

using namespace std;

class Game : public Visitable {
public:
	Game();
	virtual ~Game();

	void AcceptVisitor(GameVisitor &visitor);
	void AddPlace(Place& place);
	vector<Place *>& GetPlaces();
private:
	// Game has a few places.
	//ArrayList<Place> places;
	vector<Place *> places;
};

#endif /* GAME_H_ */
