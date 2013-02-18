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

	void Visit(Game* game);
	void Visit(OuterSpace* outerSpace);
};

#endif /* BASEVISITOR_H_ */
