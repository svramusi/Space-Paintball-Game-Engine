/*
 * Entity.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include "Visitable.h"
#include "GameState.h"

using namespace std;

class Entity : public Visitable {
public:
	Entity(string name);
	virtual ~Entity();

	string ToString();
	string GetName();
	virtual void AcceptVisitor(GameVisitor* visitor) = 0;
	virtual GameState* GetGameState() = 0;

protected:
	string name;
	GameState* gameState;
};

#endif /* ENTITY_H_ */
