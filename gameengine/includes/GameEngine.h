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

	bool TimeForUpdatingAI();
	bool TimeForUpdatingPhysics();
	void UpdateAI(int imput);
	void UpdatePhysics(int input);
	void UpdateGameState(int input);
	void Render();
};

#endif /* GAMEENGINE_H_ */
