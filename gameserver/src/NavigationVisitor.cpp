/*
 * NavigationVisitor.cpp
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#include "NavigationVisitor.h"

NavigationVisitor::NavigationVisitor(GameVisitor* gameVisitor) {
	this->gameVisitor = gameVisitor;
	itemQueue = new list<Visitable*>();
}

NavigationVisitor::~NavigationVisitor() {
	delete itemQueue;
}

//template <typename T>
//T* NavigationVisitor::ExecuteVisitor(T* visitor, Visitable& visitable) {
//	NavigationVisitor navigation = new NavigationVisitor(visitor);
//	visitable.AcceptVisitor(navigation);
//	return visitor;
//}

CollectGameState * NavigationVisitor::ExecuteVisitor(CollectGameState* visitor, Visitable* visitable) {
	NavigationVisitor * navigation = new NavigationVisitor(visitor);
	visitable->AcceptVisitor(navigation);
	return visitor;
}

void NavigationVisitor::VisitNext() {
	if(!itemQueue->empty()) {
		// Get the first element of the list.
		Visitable* first = itemQueue->front();
		// Remove the first element of the list.
		itemQueue->pop_front();
		first->AcceptVisitor(this);
	}
}

void NavigationVisitor::Visit(Game* game) {
	gameVisitor->Visit(game);

	vector<Place*>* places = game->GetPlaces();

	// Add all Places in Game to queue.
	for(int i = 0; i < places->size(); i++)
	{
		itemQueue->push_back((*places)[i]);
	}

	VisitNext();
}

void NavigationVisitor::Visit(OuterSpace* outerSpace) {
	gameVisitor->Visit(outerSpace);

	vector<Character*>* characters = outerSpace->GetCharacters();
	vector<Prop*>* props = outerSpace->GetProps();

	// Add all Characters in Place to queue.
	for(int i = 0; i < characters->size(); i++)
	{
		itemQueue->push_back((*characters)[i]);
	}

	// Add all Props in Place to queue.
	for(int i = 0; i < props->size(); i++)
	{
		itemQueue->push_back((*props)[i]);
	}

	VisitNext();
}

void NavigationVisitor::Visit(SuperHero* superHero) {
	gameVisitor->Visit(superHero);
	VisitNext();
}

void NavigationVisitor::Visit(Astronaut* astronaut) {
	gameVisitor->Visit(astronaut);
	VisitNext();
}

void NavigationVisitor::Visit(Planet* planet) {
	gameVisitor->Visit(planet);
	VisitNext();
}

void NavigationVisitor::Visit(SpaceShip* spaceShip) {
	gameVisitor->Visit(spaceShip);
	VisitNext();
}
