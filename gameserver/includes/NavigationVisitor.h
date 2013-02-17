/*
 * NavigationVisitor.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef NAVIGATIONVISITOR_H_
#define NAVIGATIONVISITOR_H_

#include "BaseVisitor.h"
#include "GameVisitor.h"

class NavigationVisitor : public BaseVisitor {
public:
	NavigationVisitor();
	virtual ~NavigationVisitor();

	//static <T : GameVisitor> T ExecVisitor(T visitor, Visitable visitable);
private:
	//GameVisitor gameVisitor;
};

#endif /* NAVIGATIONVISITOR_H_ */
