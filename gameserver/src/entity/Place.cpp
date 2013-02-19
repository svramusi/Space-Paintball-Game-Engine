/*
 * Place.cpp
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#include "entity/Place.h"

Place::Place() {
	// TODO Auto-generated constructor stub

}

Place::~Place() {
	// TODO Auto-generated destructor stub
}

void Place::AddCharacter(Character* character) {
	characters.push_back(character);
}

void Place::AddProp(Prop* prop) {
	props.push_back(prop);
}

vector<Character*>& Place::GetCharacters() {
	return characters;
}

vector<Prop*>& Place::GetProps() {
	return props;
}
