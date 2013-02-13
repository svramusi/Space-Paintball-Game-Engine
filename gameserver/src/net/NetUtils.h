/*
 * NetUtils.h
 *
 *  Created on: Feb 10, 2013
 *      Author: amarppatel
 */

#ifndef NETUTILS_H_
#define NETUTILS_H_

#include <unistd.h>

namespace net
{
	class NetUtils {
	public:
		NetUtils();
		virtual ~NetUtils();
		static void wait( float seconds );
	};
}
#endif /* NETUTILS_H_ */
