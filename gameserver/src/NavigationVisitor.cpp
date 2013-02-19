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
		Visitable* first = itemQueue.front();
		first->AcceptVisitor(this);
	}
}
