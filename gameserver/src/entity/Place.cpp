/*
 * Place.cpp
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#include "entity/Place.h"

Place::Place(string name) : Entity(name) {
	characters = new vector<Character*>();
	props = new vector<Prop*>();
}

Place::~Place() {
	delete characters;
	delete props;
}

void Place::AddCharacter(Character* character) {
	characters->push_back(character);
}

void Place::AddProp(Prop* prop) {
	props->push_back(prop);
}

vector<Character*>* Place::GetCharacters() {
	return characters;
}

vector<Prop*>* Place::GetProps() {
	return props;
}
