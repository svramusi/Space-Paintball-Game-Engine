/*
 * GamePacket.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#include "net/GamePacket.h"

namespace net
{
	GamePacket::GamePacket() {
		// TODO Auto-generated constructor stub

	}

	GamePacket::~GamePacket() {
		// TODO Auto-generated destructor stub
	}

	int GamePacket::GetByteSize() {
		// Needs to be implemented.
		return 0;
	}

	char * GamePacket::GetDataPtr() {
		// Needs to be implemented.
		char * result;
		return result;
	}

	char * GamePacket::Encode() {
		// Needs to be implemented.
		char * result;
		return result;
	}

	void Decode(char *data, int size) {
		// Needs to be implemented.
	}
}
