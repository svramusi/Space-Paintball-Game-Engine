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
#include <vector>
#include <map>

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
        static physicsInfo GetPhysicsInfo( CollidableObject *obj, float mass, Velocity linVel, Force linForce, Velocity angVel, Force angForce, Point angPos );

        /*
         * Functions that convert from game objects to game messages.
         */
        static GameEngineMessage* GetClientQuitStateMessage();
        static GameEngineMessage* GetGameEngineCreateMessage( vector<physicsInfo> physicsInfos );
        static GameEngineMessage* GetGameEngineRetrieveMessage( vector<physicsInfo> physicsInfos );
        static GameEngineMessage* GetUpdateObjectMsg( map<int, Point> updateObjMap );
        static GameEngineMessage* GetDeleteObjectMsg( vector<int> deleteObjVector );
        static void SetPhysicsInfoMessage( physicsInfo thePhysicsInfo, PhysicsInfoMessage* physicsInfoMsg );
        static AabbMessage* GetAabbObjectMsg( AABB* aabbObject );
        static SphereMessage* GetSphereObjectMsg( Sphere* sphereObject );
        static CollidableObjectMessage* GetCollidableObjectMsg( int ID, Point center, int movable );
        static PointMessage* GetPointMsg( Point point );
        static VelocityMessage* GetVelocityMsg( Velocity velocity );
        static ForceMessage* GetForceMsg( Force force );

        /*
         * Functions that convert from game messages to game object.
         */
        static bool GetClientQuitState( GameEngineMessage* gameEngineMsg );
        static vector<physicsInfo> GetGameEngineCreateObj( GameEngineMessage* gameEngineMsg );
        static vector<physicsInfo> GetGameEngineRetrieveObj( GameEngineMessage* gameEngineMsg );
        static map<int, Point> GetUpdateObj( GameEngineMessage* gameEngineMsg );
        static vector<int> GetDeleteObj( GameEngineMessage* gameEngineMsg );
        static AABB* GetAABBObj( const AabbMessage& aabbObjectMsg );
        static Sphere* GetSphereObj( const SphereMessage& sphereOjbectMsg );
        static Point GetPointObj( const PointMessage& pointMsg );
        static Velocity GetVelocityObj( const VelocityMessage& velocityMsg );
        static Force GetForceObj( const ForceMessage& forceMsg );
    };
}
#endif /* NETUTILS_H_ */
