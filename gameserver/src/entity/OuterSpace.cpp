/*
 * OuterSpace.cpp
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#include "entity/OuterSpace.h"

OuterSpace::OuterSpace() {
	// TODO Auto-generated constructor stub

}

OuterSpace::~OuterSpace() {
	// TODO Auto-generated destructor stub
}

void OuterSpace::AcceptVisitor(GameVisitor& visitor) {
	visitor.Visit(this);
}
