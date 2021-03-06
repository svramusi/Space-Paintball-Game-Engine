/*
 * Address.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: amarppatel
 */

#include "net/Address.h"

namespace net
{
	Address::Address() {
		address = 0;
		port = 0;
	}

	Address::~Address() {
	}

	Address::Address( unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port )
	{
		this->address = ( a << 24 ) | ( b << 16 ) | ( c << 8 ) | d;
		this->port = port;
	}

	Address::Address( unsigned int address, unsigned short port )
	{
		this->address = address;
		this->port = port;
	}

	unsigned int Address::GetAddress() const
	{
		return address;
	}

	unsigned char Address::GetA() const
	{
		return ( unsigned char ) ( address >> 24 );
	}

	unsigned char Address::GetB() const
	{
		return ( unsigned char ) ( address >> 16 );
	}

	unsigned char Address::GetC() const
	{
		return ( unsigned char ) ( address >> 8 );
	}

	unsigned char Address::GetD() const
	{
		return ( unsigned char ) ( address );
	}

	unsigned short Address::GetPort() const
	{
		return port;
	}

	bool Address::operator == ( const Address & other ) const
	{
		return address == other.address && port == other.port;
	}

	bool Address::operator != ( const Address & other ) const
	{
		return ! ( *this == other );
	}

	bool Address::operator < ( const Address & other ) const
	{
		// note: this is so we can use address as a key in std::map
		if ( address < other.address )
			return true;
		if ( address > other.address )
			return false;
		else
			return port < other.port;
	}

	string Address::ToString()
	{
		string result;
		ostringstream convert;
		convert << (int)GetA() << "." << (int)GetB() << "." << (int)GetC() << "." << (int)GetD() << ":" << (int)GetPort();

		result = convert.str();

		return result;
	}
}
