/*
 * Character.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <string>

#include "entity/Entity.h"

using namespace std;

class Character : public Entity {
public:
	Character(string name);
	virtual ~Character();
};

#endif /* CHARACTER_H_ */
