/*
 * CollectGameState.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef COLLECTGAMESTATE_H_
#define COLLECTGAMESTATE_H_

#include "BaseVisitor.h"

class CollectGameState : public BaseVisitor {
public:
	CollectGameState();
	virtual ~CollectGameState();
};

#endif /* COLLECTGAMESTATE_H_ */
