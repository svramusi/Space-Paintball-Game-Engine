/*
 * Prop.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef PROP_H_
#define PROP_H_

#include <string>

#include "entity/Entity.h"

using namespace std;

class Prop : public Entity {
public:
	Prop(string name);
	virtual ~Prop();
};

#endif /* PROP_H_ */
