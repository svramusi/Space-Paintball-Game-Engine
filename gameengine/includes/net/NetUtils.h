/*
 * NetUtils.h
 *
 *  Created on: Feb 10, 2013
 *      Author: amarppatel
 */

#ifndef NETUTILS_H_
#define NETUTILS_H_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <errno.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "net/GameEngine.pb.h"
#include "net/Socket.h"

#include "physicsinfo.h"
#include "Point.h"
#include "SphereClass.h"
#include "AABBClass.h"
#include "CollidableObject.h"

using namespace google::protobuf::io;
using namespace std;

namespace net
{
	class NetUtils {
	public:
		NetUtils();
		virtual ~NetUtils();
		static void Wait( float seconds );
		static void Send( GameEngineMessage* input, net::Socket* socket );
		static google::protobuf::uint32 ReadHeader( char *buf );
		static GameEngineMessage* ReadBody( net::Socket* serverSocket, google::protobuf::uint32 size );
		static GameEngineMessage* GetGameEnginePayload();
		static physicsInfo GetPhysicsInfo( float value );
		static GameEngineMessage* GetGameEngineCreateMessage( vector<physicsInfo> physicsInfos );
		static void SetPhysicsInfoMessage( physicsInfo thePhysicsInfo, PhysicsInfoMessage* physicsInfoMsg );
		static AabbMessage* GetAabbObjectMsg( AABB* aabbObject );
		static SphereMessage* GetSphereObjectMsg( Sphere* sphereObject );
		static CollidableObjectMessage* GetCollidableObjectMsg( int ID, Point center, int movable );
		static PointMessage* GetPointMsg( Point point );
		static VelocityMessage* GetVelocityMsg( Velocity velocity );
		static ForceMessage* GetForceMsg( Force force );
	};
}
#endif /* NETUTILS_H_ */
