/*
 * NavigationVisitor.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef NAVIGATIONVISITOR_H_
#define NAVIGATIONVISITOR_H_

#include <list>

#include "BaseVisitor.h"
#include "GameVisitor.h"
#include "Visitable.h"
#include "GameVisitor.h"
#include "CollectGameState.h"

using namespace std;

class CollectGameState;

class NavigationVisitor : public BaseVisitor {
public:
	NavigationVisitor(GameVisitor* gameVisitor);
	virtual ~NavigationVisitor();

	//template <typename T>
	//static T* ExecuteVisitor(T* visitor, Visitable& visitable);
	static CollectGameState* ExecuteVisitor(CollectGameState* visitor, Visitable* visitable);
private:
	GameVisitor* gameVisitor;
	list<Visitable*> itemQueue;

	void VisitNext();
};

#endif /* NAVIGATIONVISITOR_H_ */
