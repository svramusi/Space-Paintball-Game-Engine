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
class SuperHero;
class Astronaut;
class Planet;
class SpaceShip;

class GameVisitor {
public:
	GameVisitor();
	virtual ~GameVisitor();

	// Game
	virtual void Visit(Game* game) = 0;

	// Places
	virtual void Visit(OuterSpace* outerSpace) = 0;

	// Characters
	virtual void Visit(SuperHero* superHero) = 0;
	virtual void Visit(Astronaut* astronaut) = 0;

	// Props
	virtual void Visit(Planet* planet) = 0;
	virtual void Visit(SpaceShip* spaceShip) = 0;
};

#endif /* GAMEVISITOR_H_ */
