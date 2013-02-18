/*
 * GameState.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <string>

using namespace std;

class GameState {
public:
	GameState(string gameState);
	virtual ~GameState();

private:
	string gameState;
};

#endif /* GAMESTATE_H_ */
