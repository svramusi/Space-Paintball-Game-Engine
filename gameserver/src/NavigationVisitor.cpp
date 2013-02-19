/*
 * NavigationVisitor.cpp
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#include "NavigationVisitor.h"

NavigationVisitor::NavigationVisitor(GameVisitor* gameVisitor) {
	this->gameVisitor = gameVisitor;
}

NavigationVisitor::~NavigationVisitor() {
	// TODO Auto-generated destructor stub
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
	if(!itemQueue.empty()) {
		// Get the first element of the list.
		Visitable* first = itemQueue.front();
		// Remove the first element of the list.
		itemQueue.pop_front();
		first->AcceptVisitor(this);
	}
}

void NavigationVisitor::Visit(Game* game) {
		gameVisitor->Visit(game);

		vector<Place*> places = game->GetPlaces();

		for(int i = 0; i < places.size(); i++)
		{
			itemQueue.push_back(places[i]);
		}

		VisitNext();
	}
