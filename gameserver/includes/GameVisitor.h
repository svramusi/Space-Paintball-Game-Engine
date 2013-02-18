/*
 * GameVisitor.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef GAMEVISITOR_H_
#define GAMEVISITOR_H_

class Game;
class OuterSpace;

class GameVisitor {
public:
	GameVisitor();
	virtual ~GameVisitor();

	virtual void Visit(Game* game) = 0;
	virtual void Visit(OuterSpace* outerSpace) = 0;
};

#endif /* GAMEVISITOR_H_ */
