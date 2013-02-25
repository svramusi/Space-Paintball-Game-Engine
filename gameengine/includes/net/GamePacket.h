/*
 * GamePacket.h
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#ifndef GAMEPACKET_H_
#define GAMEPACKET_H_

#include<string>

using namespace std;

namespace net
{
	/*
	 * This class stores a message the game will send.
	 */
	class GamePacket {
	public:
		GamePacket(unsigned char* packet, int size);
		virtual ~GamePacket();
		int GetByteSize();
		unsigned char* GetDataPtr();
		/*
		 * This method encodes the packet into an array of bytes.
		 */
		unsigned char* Encode();
		/*
		 * This method decodes the packet from an array of bytes.
		 */
		static GamePacket* Decode( unsigned char *data, int size );
		string ToString();
	private:
		unsigned char* packet;
		int size;
	};
}

#endif /* GAMEPACKET_H_ */
