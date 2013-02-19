/*
 * Visitable.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef VISITABLE_H_
#define VISITABLE_H_

#include "GameVisitor.h"

class Visitable {
public:
	Visitable();
	virtual ~Visitable();

	virtual void AcceptVisitor(GameVisitor *visitor) = 0;
};

#endif /* VISITABLE_H_ */
