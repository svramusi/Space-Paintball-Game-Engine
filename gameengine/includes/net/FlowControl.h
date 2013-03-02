/*
 * FlowControl.h
 *
 *  Created on: Mar 1, 2013
 *      Author: amarppatel
 */

#ifndef FLOWCONTROL_H_
#define FLOWCONTROL_H_

#include <iostream>
#include <fstream>

namespace net {

class FlowControl {
public:
	FlowControl();
	virtual ~FlowControl();
	void Reset();
	void Update( float deltaTime, float rtt );
	float GetSendRate();

private:
	enum Mode
	{
		Good,
		Bad
	};

	Mode mode;
	float penalty_time;
	float good_conditions_time;
	float penalty_reduction_accumulator;
};

} /* namespace net */
#endif /* FLOWCONTROL_H_ */
