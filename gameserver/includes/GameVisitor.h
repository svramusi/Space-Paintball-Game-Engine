/*
 * GameVisitor.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef GAMEVISITOR_H_
#define GAMEVISITOR_H_

#include "Game.h"

class GameVisitor {
public:
	GameVisitor();
	virtual ~GameVisitor();

	virtual void Visit(Game& game) = 0;
};

#endif /* GAMEVISITOR_H_ */
