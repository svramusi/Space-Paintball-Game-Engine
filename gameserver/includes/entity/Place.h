/*
 * Place.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef PLACE_H_
#define PLACE_H_

#include <vector>

#include "Character.h"
#include "Prop.h"
#include "entity/Entity.h"

using namespace std;

class Place : public Entity {
public:
	Place();
	virtual ~Place();

	void AddCharacter(Character& character);
	//void AddProp(Prop& prop);
	//vector<Character>& GetCharacters();
	//vector<Prop>& GetProps();
private:
	vector<Character> characters;
	vector<Prop> props;
};

#endif /* PLACE_H_ */
