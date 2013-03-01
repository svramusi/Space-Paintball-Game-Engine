/*
 * PacketQueue.h
 *
 *  Created on: Mar 1, 2013
 *      Author: amarppatel
 */

#ifndef PACKETQUEUE_H_
#define PACKETQUEUE_H_

#include <list>

using namespace std;

namespace net {

	/*
	 * packet queue to store information about sent and received packets sorted in sequence order
	 * + we define ordering using the "sequence_more_recent" function, this works provided there is a large gap when sequence wrap occurs
	 */

	struct PacketData
	{
		unsigned int sequence;			// packet sequence number
		float time;					    // time offset since packet was sent or received (depending on context)
		int size;						// packet size in bytes
	};

	inline bool sequence_more_recent( unsigned int s1, unsigned int s2, unsigned int max_sequence )
	{
		return ( s1 > s2 ) && ( s1 - s2 <= max_sequence/2 ) || ( s2 > s1 ) && ( s2 - s1 > max_sequence/2 );
	}

class PacketQueue : public list<PacketData> {
public:
	PacketQueue();
	virtual ~PacketQueue();
	bool exists( unsigned int sequence );
	void insert_sorted( const PacketData & p, unsigned int max_sequence );
	void verify_sorted( unsigned int max_sequence );
};

} /* namespace net */
#endif /* PACKETQUEUE_H_ */
