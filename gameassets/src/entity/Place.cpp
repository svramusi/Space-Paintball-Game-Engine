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
	for(std::vector<Character*>::iterator it = characters->begin(); it != characters->end(); ++it)
		delete *it;

	delete characters;

	for(std::vector<Prop*>::iterator it = props->begin(); it != props->end(); ++it)
		delete *it;

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
