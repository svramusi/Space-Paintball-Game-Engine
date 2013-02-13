/*
 * NetUtils.cpp
 *
 *  Created on: Feb 10, 2013
 *      Author: amarppatel
 */

#include "NetUtils.h"

namespace net
{
	NetUtils::NetUtils() {
		// TODO Auto-generated constructor stub
	}

	NetUtils::~NetUtils() {
		// TODO Auto-generated destructor stub
	}

	void NetUtils::wait( float seconds ) { usleep( (int) ( seconds * 1000000.0f ) ); }
}
