/*
 * Entity.cpp
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#include "entity/Entity.h"

Entity::Entity(string name) {
	this->name = name;
}

Entity::~Entity() {
	// TODO Auto-generated destructor stub
}

string Entity::ToString() {
	return "Entity";
}

string Entity::GetName() const {
	return name;
}
