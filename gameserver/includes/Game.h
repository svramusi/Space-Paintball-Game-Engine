/*
 * Game.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef GAME_H_
#define GAME_H_

#include "Visitable.h"
#include "GameVisitor.h"

class Game : public Visitable {
public:
	Game();
	virtual ~Game();

	void AcceptVisitor(GameVisitor& visitor);
};

#endif /* GAME_H_ */
