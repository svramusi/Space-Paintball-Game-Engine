/*
 * OuterSpace.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef OUTERSPACE_H_
#define OUTERSPACE_H_

#include <string>

#include "Place.h"
#include "GameVisitor.h"

using namespace std;

class OuterSpace : public Place {
public:
	OuterSpace(string name);
	virtual ~OuterSpace();

	void AcceptVisitor(GameVisitor* visitor);
	GameState* GetGameState();
};

#endif /* OUTERSPACE_H_ */
