/*
 * TestCollectGameState.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: amarppatel
 */

#include "TestCollectGameState.h"
#include "entity/Place.h"
#include "entity/OuterSpace.h"
#include "entity/Planet.h"
#include "entity/SuperHero.h"
#include "entity/SpaceShip.h"
#include "entity/Astronaut.h"

TestCollectGameState::TestCollectGameState() {
	game = new Game();

	Place* milkyWay = new OuterSpace("Milky Way");
	milkyWay->AddProp(new Planet("Earth"));
	milkyWay->AddProp(new Planet("Mars"));
	milkyWay->AddProp(new Planet("Venus"));
	milkyWay->AddProp(new Planet("Jupiter"));
	milkyWay->AddProp(new Planet("Mercury"));
	milkyWay->AddProp(new Planet("Saturn"));
	milkyWay->AddProp(new Planet("Uranus"));
	milkyWay->AddProp(new Planet("Neptune"));

	milkyWay->AddCharacter(new SuperHero("Superman"));
	milkyWay->AddCharacter(new SuperHero("Batman"));
	milkyWay->AddCharacter(new SuperHero("Iron Man"));
	milkyWay->AddCharacter(new SuperHero("Hulk"));

	game->AddPlace(milkyWay);

	Place* earthOrbit = new OuterSpace("Earth Orbit");

	earthOrbit->AddProp(new SpaceShip("Atlantis"));
	earthOrbit->AddProp(new SpaceShip("International Space Station"));
	earthOrbit->AddProp(new SpaceShip("Discovery"));
	earthOrbit->AddProp(new SpaceShip("Endeavour"));

	earthOrbit->AddCharacter(new Astronaut("Armstrong"));
	earthOrbit->AddCharacter(new Astronaut("Ride"));
	earthOrbit->AddCharacter(new Astronaut("White"));
	earthOrbit->AddCharacter(new Astronaut("Bluford"));

	game->AddPlace(earthOrbit);
}

TestCollectGameState::~TestCollectGameState() {
	// TODO Auto-generated destructor stub
}

