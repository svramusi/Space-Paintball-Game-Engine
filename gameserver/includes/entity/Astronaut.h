/*
 * Astronaut.h
 *
 *  Created on: Feb 19, 2013
 *      Author: amarppatel
 */

#ifndef ASTRONAUT_H_
#define ASTRONAUT_H_

#include <string>

#include "Character.h"
#include "GameState.h"
#include "GameVisitor.h"

using namespace std;

class Astronaut : public Character {
public:
	Astronaut(string name);
	virtual ~Astronaut();

	void AcceptVisitor(GameVisitor* visitor);
	GameState* GetGameState();
private:
	string name;
	GameState* gameState;
};

#endif /* ASTRONAUT_H_ */
