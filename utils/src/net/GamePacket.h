/*
 * GamePacket.h
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#ifndef GAMEPACKET_H_
#define GAMEPACKET_H_

namespace net
{
	/*
	 * This class stores a message the game will send.
	 */
	class GamePacket {
	public:
		GamePacket();
		virtual ~GamePacket();
		int GetByteSize();
		char *GetDataPtr();
		/*
		 * This method encodes the packet into an array of bytes.
		 */
		char *Encode();
		/*
		 * This method decodes the packet from an array of bytes.
		 */
		void Decode( char *data, int size );
	};
}

#endif /* GAMEPACKET_H_ */
