/*
 * SpaceShip.h
 *
 *  Created on: Feb 19, 2013
 *      Author: amarppatel
 */

#ifndef SPACESHIP_H_
#define SPACESHIP_H_

#include <string>

#include "Prop.h"
#include "GameState.h"
#include "GameVisitor.h"

using namespace std;

class SpaceShip : public Prop {
public:
	SpaceShip(string name);
	virtual ~SpaceShip();

	void AcceptVisitor(GameVisitor* visitor);
	GameState* GetGameState();
private:
	string name;
	GameState* gameState;

};

#endif /* SPACESHIP_H_ */
