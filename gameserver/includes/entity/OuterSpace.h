/*
 * OuterSpace.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef OUTERSPACE_H_
#define OUTERSPACE_H_

#include "Place.h"
#include "GameVisitor.h"

class OuterSpace : public Place {
public:
	OuterSpace();
	virtual ~OuterSpace();

	void AcceptVisitor(GameVisitor& visitor);
	GameState* GetGameState();
};

#endif /* OUTERSPACE_H_ */
