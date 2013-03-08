#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <map>
#include <errno.h>
#include <arpa/inet.h>

#include "SDL-1.2.15/include/SDL.h"

#include "net/Net.h"
#include "net/Constants.hpp"
#include "net/NetUtils.h"
#include "utils/gun_utils.h"
#include "physicsengine.h"
#include "GameEngine.h"
#include "TestCollectGameState.h"
#include "net/GameEngine.pb.h"
#include "net/GameEngine.pb.cc"

#include <iostream>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

using namespace google::protobuf::io;

using namespace std;
using namespace net;

int PollForOSMessages(bool* quit);
int GetInputFromClient(bool* quit);
void SendUpdateToClient();
bool TimeForRendering();
void UpdateStatistics();
void FPSControl();
void* SocketHandler(void*);
bool HasData(int & csock);

int main( int argc, char * argv[] )
{
	//TestCollectGameState* test = new TestCollectGameState();
	//test->PrintGameState();
	//delete test;

	//GunUtils *guns = new GunUtils("example.xml");
	//guns->print_guns();
	//delete guns;

//	PhysicsEngine *physics_engine = new PhysicsEngine();
//	physics_engine->updateWorld();
//	delete physics_engine;

	//startGameMasterServer();

	GameEngine gameEngine;
	bool quit = false;
	Uint32 time = SDL_GetTicks();
	bool needToRedraw = true;

	/////////////////////////////////////////////////////////////////
	// Setup up server socket
	/////////////////////////////////////////////////////////////////
    int host_port= 1101;

    struct sockaddr_in my_addr;

    int hsock;
    int * p_int ;
    int err;

    socklen_t addr_size = 0;
    int* csock;
    sockaddr_in sadr;
    pthread_t thread_id=0;

    hsock = socket(AF_INET, SOCK_STREAM, 0);
    if(hsock == -1){
            printf("Error initializing socket %d\n", errno);
            goto FINISH;
    }

    p_int = (int*)malloc(sizeof(int));
    *p_int = 1;

    if( (setsockopt(hsock, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1 )||
            (setsockopt(hsock, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1 ) ){
            printf("Error setting options %d\n", errno);
            free(p_int);
            goto FINISH;
    }
    free(p_int);

    my_addr.sin_family = AF_INET ;
    my_addr.sin_port = htons(host_port);

    memset(&(my_addr.sin_zero), 0, 8);
    my_addr.sin_addr.s_addr = INADDR_ANY ;

    if( bind( hsock, (sockaddr*)&my_addr, sizeof(my_addr)) == -1 ){
            fprintf(stderr,"Error binding to socket, make sure nothing else is listening on this port %d\n",errno);
            goto FINISH;
    }
    if(listen( hsock, 10) == -1 ){
            fprintf(stderr, "Error listening %d\n",errno);
            goto FINISH;
    }
	/////////////////////////////////////////////////////////////////

    addr_size = sizeof(sockaddr_in);

	// Server Game Loop
	while(!quit)
	{
		/*
		 * Poll for OS Events/Messages; this is
		 * the event pump.
		 */
		PollForOSMessages(&quit);

		///////////////////////////////////////////////////////////
		// Socket logic
		///////////////////////////////////////////////////////////
		printf("waiting for a connection\n");
		csock = (int*)malloc(sizeof(int));
		if((*csock = accept( hsock, (sockaddr*)&sadr, &addr_size))!= -1){
				printf("---------------------\nReceived connection from %s\n",inet_ntoa(sadr.sin_addr));
				pthread_create(&thread_id,0,&SocketHandler, (void*)csock );
				pthread_detach(thread_id);
		}
		else{
				fprintf(stderr, "Error accepting %d\n", errno);
		}
		///////////////////////////////////////////////////////////

		// send and receive packets

		SendUpdateToClient();

		int input = GetInputFromClient(&quit);

		///////////////////////////////////////////////////////////
		//Update Game State
		//gameEngine.UpdateGameState(input);
		///////////////////////////////////////////////////////////

		/*
		 * Get information from the game engine to update
		 * the player score, health, etc. (since typically
		 * the HUD is not rendered by the game engine, but
		 * separately).
		 */
		//UpdateStatistics();

		FPSControl();

		/*
		 * Play nice with the OS, and give
		 * some CPU for another process.
		 */
		//SDL_Delay(1);
		NetUtils::wait( DeltaTime );
	} // End Server Game Loop

FINISH:
;
}

void FPSControl()
{

}

void UpdateStatistics()
{

}

/*
 * Keep rendering time at 30 or 50 fps.
 */
bool TimeForRendering()
{
	return true;
}

/*
 * Event pump method; polling method for
 * OS messages.
 */
int PollForOSMessages(bool* quit)
{
/*
	while(SDL_PollEvent(&event))
	{
		switch(eventType)
		{
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_F12)
				{
					quit = true;
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				gameEngine->MouseClick(event.button.x, event.button.y);
				break;

			case SDL_QUIT:
				quit = true;
				break;
		} // End Switch
	}
	*/

	return 0;
}

/*
 * Check the keyboard/mouse state and identify any user
 * input. Also, if there are players over the network,
 * get their inputs.
 */
int GetInputFromClient(bool* quit)
{
	int input = 0;

	return input;
}

void SendUpdateToClient()
{
}

google::protobuf::uint32 readHdr(char *buf)
{
  google::protobuf::uint32 size;
  google::protobuf::io::ArrayInputStream ais(buf,4);
  CodedInputStream coded_input(&ais);
  coded_input.ReadVarint32(&size);//Decode the HDR and get the size
  cout<<"size of payload is "<<size<<endl;
  return size;
}

void readBody(int csock,google::protobuf::uint32 siz)
{
  int bytecount;
  net::Point payload;
  char buffer [siz+4];//size of the payload and hdr
  //Read the entire buffer including the hdr
  if((bytecount = recv(csock, (void *)buffer, 4+siz, MSG_WAITALL))== -1){
                fprintf(stderr, "Error receiving data %d\n", errno);
        }
  cout<<"Second read byte count is "<<bytecount<<endl;
  //Assign ArrayInputStream with enough memory
  google::protobuf::io::ArrayInputStream ais(buffer,siz+4);
  CodedInputStream coded_input(&ais);
  //Read an unsigned integer with Varint encoding, truncating to 32 bits.
  coded_input.ReadVarint32(&siz);
  //After the message's length is read, PushLimit() is used to prevent the CodedInputStream
  //from reading beyond that length.Limits are used when parsing length-delimited
  //embedded messages
  google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(siz);
  //De-Serialize
  payload.ParseFromCodedStream(&coded_input);
  //Once the embedded message has been parsed, PopLimit() is called to undo the limit
  coded_input.PopLimit(msgLimit);
  //Print the message
  cout<<"Message is "<<payload.DebugString();

}

void* SocketHandler(void* lp){
    int *csock = (int*)lp;

	char buffer[4];
	int bytecount=0;
	string output,pl;
	//net::Point logp;

	memset(buffer, '\0', 4);

	while (1) {
		//Peek into the socket and get the packet size
		if((bytecount = recv(*csock, buffer, 4, MSG_PEEK))== -1){
				fprintf(stderr, "Error receiving data %d\n", errno);
		}else if (bytecount == 0)
				break;
		cout<<"First read byte count is "<<bytecount<<endl;
		readBody(*csock,readHdr(buffer));
	}

FINISH:
        free(csock);
    return 0;
}

bool HasData(int& csock)
{
	int timeOut = 100; //ms
	fd_set socketReadSet;
	FD_ZERO(&socketReadSet);
	FD_SET(csock,&socketReadSet);
	struct timeval tv;
	if (timeOut) {
		tv.tv_sec  = timeOut / 1000;
		tv.tv_usec = (timeOut % 1000) * 1000;
	} else {
		tv.tv_sec  = 0;
		tv.tv_usec = 0;
	} // if

	if (select(csock+1,&socketReadSet,0,0,&tv) == -1) {
		perror("select()\n");
		return false;
	} // if
	int res = FD_ISSET(csock,&socketReadSet);

	return res != 0;
}
