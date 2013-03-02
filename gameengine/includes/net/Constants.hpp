/*
 * Constants.hpp
 *
 *  Created on: Feb 10, 2013
 *      Author: amarppatel
 */

#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

namespace net {
	const int ServerPort = 30000;
	const int ClientPort = 30001;
	const int ProtocolId = 0x11223344;
	const float DeltaTime = 1.0f / 30.0f;
	const float SendRate = 1.0f / 30.0f;
	const float TimeOut = 10.0f;
	const int PacketSize = 256;
}

#endif /* CONSTANTS_HPP_ */
