#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "net/Net.h"
#include "net/Connection.h"
#include "net/NetUtils.h"

using namespace std;
using namespace net;

const int ServerPort = 30000;
const int ClientPort = 30001;
const int ProtocolId = 0x99887766;
const float DeltaTime = 0.25f;
const float SendRate = 0.25f;
const float TimeOut = 10.0f;

int main( int argc, char * argv[] )
{
	Connection connection( ProtocolId, TimeOut );

	if ( !connection.Start( ServerPort ) )
	{
		printf( "could not start connection on port %d\n", ServerPort );
		return 1;
	}

	connection.Listen();

	while ( true )
	{
		if ( connection.IsConnected() )
		{
			unsigned char packet[] = "server to client";
			connection.SendPacket( packet, sizeof( packet ) );
		}

		while ( true )
		{
			unsigned char packet[256];
			int bytes_read = connection.ReceivePacket( packet, sizeof(packet) );
			if ( bytes_read == 0 )
				break;
			printf( "received packet from client\n" );
		}

		connection.Update( DeltaTime );
		NetUtils::wait( DeltaTime );
	}

	return 0;
}
