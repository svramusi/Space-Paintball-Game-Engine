/*
 * GameEngine.h
 *
 *  Created on: Feb 13, 2013
 *      Author: amarppatel
 */

#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <stdio.h>

using namespace std;

class GameEngine {
public:
	GameEngine();
	virtual ~GameEngine();

	void UpdateAI();
	void UpdatePhysics();
	void Render();
};

#endif /* GAMEENGINE_H_ */
