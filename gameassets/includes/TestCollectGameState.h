/*
 * TestCollectGameState.h
 *
 *  Created on: Feb 18, 2013
 *      Author: amarppatel
 */

#ifndef TESTCOLLECTGAMESTATE_H_
#define TESTCOLLECTGAMESTATE_H_

#include <map>
#include <stdio.h>

#include "Game.h"
#include "CollectGameState.h"
#include "NavigationVisitor.h"
#include "GameState.h"
#include "entity/Entity.h"

using namespace std;

class TestCollectGameState {
public:
	TestCollectGameState();
	virtual ~TestCollectGameState();

	void PrintGameState();
private:
	Game * game;
};

#endif /* TESTCOLLECTGAMESTATE_H_ */
