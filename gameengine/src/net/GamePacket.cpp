/*
 * GamePacket.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#include "net/GamePacket.h"

namespace net
{
	GamePacket::GamePacket(unsigned char* packet) {
		this->packet = packet;
	}

	GamePacket::~GamePacket() {
		delete packet;
	}

	int GamePacket::GetByteSize() {
		return sizeof(packet);
	}

	unsigned char * GamePacket::GetDataPtr() {
		return packet;
	}

	unsigned char * GamePacket::Encode() {
		// Needs to be implemented.
		return packet;
	}

	GamePacket* GamePacket::Decode(unsigned char *data, int size) {
		// Needs to be implemented.
		GamePacket* gamePacket = new GamePacket(data);

		return gamePacket;
	}
}
