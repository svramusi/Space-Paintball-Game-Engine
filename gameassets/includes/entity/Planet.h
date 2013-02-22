/*
 * Planet.h
 *
 *  Created on: Feb 19, 2013
 *      Author: amarppatel
 */

#ifndef PLANET_H_
#define PLANET_H_

#include <string>

#include "Prop.h"
#include "GameVisitor.h"
#include "GameState.h"

using namespace std;

class Planet : public Prop {
public:
	Planet(string name);
	virtual ~Planet();

	void AcceptVisitor(GameVisitor* visitor);
	GameState* GetGameState();
};

#endif /* PLANET_H_ */
