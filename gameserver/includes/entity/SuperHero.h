/*
 * SuperHero.h
 *
 *  Created on: Feb 19, 2013
 *      Author: amarppatel
 */

#ifndef SUPERHERO_H_
#define SUPERHERO_H_

#include <string>

#include "GameVisitor.h"
#include "GameState.h"
#include "Character.h"

using namespace std;

class SuperHero : public Character {
public:
	SuperHero(string name);
	virtual ~SuperHero();

	void AcceptVisitor(GameVisitor* visitor);
	GameState* GetGameState();
};

#endif /* SUPERHERO_H_ */
