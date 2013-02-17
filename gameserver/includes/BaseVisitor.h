/*
 * BaseVisitor.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef BASEVISITOR_H_
#define BASEVISITOR_H_

#include "GameVisitor.h"

class BaseVisitor : public GameVisitor {
public:
	BaseVisitor();
	virtual ~BaseVisitor();

	virtual void Visit(Game& game);
	virtual void Visit(OuterSpace& outerSpace);
};

#endif /* BASEVISITOR_H_ */
