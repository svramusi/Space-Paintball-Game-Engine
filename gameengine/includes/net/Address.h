/*
 * Address.h
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

namespace net
{
	// Internet address class
	class Address {
	public:
		Address();
		Address( unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port );
		Address( unsigned int address, unsigned short port );
		virtual ~Address();

		unsigned int GetAddress() const;
		unsigned char GetA() const;
		unsigned char GetB() const;
		unsigned char GetC() const;
		unsigned char GetD() const;
		unsigned short GetPort() const;
		bool operator == ( const Address & other ) const;
		bool operator != ( const Address & other ) const;
		bool operator < ( const Address & other ) const;
		string ToString();

	private:
		unsigned int address;
		unsigned short port;
	};
}
#endif /* ADDRESS_H_ */
