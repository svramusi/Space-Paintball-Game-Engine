/*
 * Entity.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include "Visitable.h"

using namespace std;

class Entity : public Visitable {
public:
	Entity();
	virtual ~Entity();

	string ToString();
	virtual void AcceptVisitor(GameVisitor& visitor) = 0;
};

#endif /* ENTITY_H_ */
