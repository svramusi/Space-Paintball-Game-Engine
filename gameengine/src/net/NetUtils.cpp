/*
 * NetUtils.cpp
 *
 *  Created on: Feb 10, 2013
 *      Author: amarppatel
 */

#include "net/NetUtils.h"

namespace net
{
    NetUtils::NetUtils()
    {
    }

    NetUtils::~NetUtils()
    {
    }

    void NetUtils::Wait( float seconds )
    {
        usleep( (int) ( seconds * 1000000.0f ) );
    }

    void NetUtils::Send( GameEngineMessage* input, net::Socket* socket )
    {
        ///////////////////////////////////////////////////////////////////
        // Initialize payload
        ///////////////////////////////////////////////////////////////////

        printf( "Size after serilizing is %d\n", input->ByteSize() );
        int size = input->ByteSize() + 4;
        char *packet = new char [size];
        google::protobuf::io::ArrayOutputStream aos(packet,size);
        CodedOutputStream *coded_output = new CodedOutputStream(&aos);
        coded_output->WriteVarint32(input->ByteSize());
        input->SerializeToCodedStream(coded_output);
        ///////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////
        // Client socket work - send payload to server
        ///////////////////////////////////////////////////////////////////
        bool sent = socket->Send( (void *) packet, size );

        if( sent )
        {
            // Reclaim memory.
            delete packet;
        }
        ///////////////////////////////////////////////////////////////////
    }

    google::protobuf::uint32 NetUtils::ReadHeader( char *buf )
    {
        google::protobuf::uint32 size;
        google::protobuf::io::ArrayInputStream ais( buf,4 );
        CodedInputStream coded_input( &ais );
        coded_input.ReadVarint32( &size );//Decode the HDR and get the size
        printf( "Size of payload is %d\n", size );

        return size;
    }

    GameEngineMessage* NetUtils::ReadBody( net::Socket* socket, google::protobuf::uint32 size )
    {
        int bytecount;
        GameEngineMessage* payload =  new GameEngineMessage();
        char buffer [ size + 4 ];//size of the payload and hdr
        //Read the entire buffer including the hdr
        bytecount = socket->ReceiveWaitAll( (void *)buffer, 4 + size );

        printf( "Second read byte count is %d\n", bytecount );

        //Assign ArrayInputStream with enough memory
        google::protobuf::io::ArrayInputStream ais( buffer, size + 4 );
        CodedInputStream coded_input( &ais );
        //Read an unsigned integer with Varint encoding, truncating to 32 bits.
        coded_input.ReadVarint32( &size );
        //After the message's length is read, PushLimit() is used to prevent the CodedInputStream
        //from reading beyond that length. Limits are used when parsing length-delimited
        //embedded messages
        google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit( size );
        //De-Serialize
        payload->ParseFromCodedStream( &coded_input );
        //Once the embedded message has been parsed, PopLimit() is called to undo the limit
        coded_input.PopLimit( msgLimit );
        //Print sender of message
        printf( "Message from %s\n", socket->GetSenderAddress().ToString().c_str() );
        //Print the message
        printf( "Message is %s\n", payload->DebugString().c_str() );

        return payload;
    }

    GameEngineMessage* NetUtils::GetGameEngineCreateMessage( vector<physicsInfo> physicsInfos )
    {
        GameEngineMessage* gameEnginePayload = new GameEngineMessage();
        gameEnginePayload->set_messagetype( GameEngineMessage::CREATE );

        for( int i = 0; i < physicsInfos.size(); i++ )
        {
            physicsInfo thePhysicsInfo = physicsInfos[i];
            PhysicsInfoMessage* physicsInfoMsg = gameEnginePayload->add_physicsinfo();
            SetPhysicsInfoMessage( thePhysicsInfo, physicsInfoMsg );
        }

        return gameEnginePayload;
    }

    GameEngineMessage* NetUtils::GetGameEngineRetrieveMessage( vector<physicsInfo> physicsInfos )
    {
        GameEngineMessage* gameEnginePayload = new GameEngineMessage();
        gameEnginePayload->set_messagetype( GameEngineMessage::RETRIEVE );

        for( int i = 0; i < physicsInfos.size(); i++ )
        {
            physicsInfo thePhysicsInfo = physicsInfos[i];
            PhysicsInfoMessage* physicsInfoMsg = gameEnginePayload->add_physicsinfo();
            SetPhysicsInfoMessage( thePhysicsInfo, physicsInfoMsg );
        }

        return gameEnginePayload;
    }

    GameEngineMessage* NetUtils::GetUpdateObjectMsg( map<int, Point> updateObjMap )
    {
        GameEngineMessage* gameEnginePayload = new GameEngineMessage();
        gameEnginePayload->set_messagetype( GameEngineMessage::UPDATE );

        for( map<int, Point>::iterator it = updateObjMap.begin(); it != updateObjMap.end(); ++it )
        {
            int ID = it->first;
            Point position = it->second;

            UpdateObjectMessage* updateObjectMsg = gameEnginePayload->add_updateobject();

            updateObjectMsg->set_id( ID );
            updateObjectMsg->set_allocated_position( GetPointMsg( position) );
        }

        return gameEnginePayload;
    }

    GameEngineMessage* NetUtils::GetDeleteObjectMsg( vector<int> deleteObjVector )
    {
        GameEngineMessage* gameEnginePayload = new GameEngineMessage();
        gameEnginePayload->set_messagetype( GameEngineMessage::DELETE );

        for( int i = 0; i < deleteObjVector.size(); i++ )
        {
            DeleteObjectMessage* deleteObjectMsg = gameEnginePayload->add_deleteobject();

            deleteObjectMsg->set_id( deleteObjVector[ i ] );
        }

        return gameEnginePayload;
    }

    void NetUtils::SetPhysicsInfoMessage( physicsInfo thePhysicsInfo, PhysicsInfoMessage* physicsInfoMsg )
    {
        AABB* aabbObject = dynamic_cast<AABB*>( thePhysicsInfo.collidableObject );
        if( aabbObject != 0)
        {
           // aabbObject  was safely cast to AABBClass
           physicsInfoMsg->set_physicsinfomessagetype( PhysicsInfoMessage::AABB );
           physicsInfoMsg->set_allocated_aabbobject( GetAabbObjectMsg( aabbObject ) );
        }
        else
        {
            Sphere* sphereObject = dynamic_cast<Sphere*>( thePhysicsInfo.collidableObject );
            if( sphereObject != 0 )
            {
                // sphereObject was safely cast to SphereClass
                physicsInfoMsg->set_physicsinfomessagetype( PhysicsInfoMessage::SPHERE );
                physicsInfoMsg->set_allocated_sphereobject( GetSphereObjectMsg( sphereObject ) );
            }
        }

        physicsInfoMsg->set_mass( thePhysicsInfo.mass );
        physicsInfoMsg->set_allocated_linearvelocity( GetVelocityMsg( thePhysicsInfo.linearVelocity ) );
        physicsInfoMsg->set_allocated_linearforce( GetForceMsg( thePhysicsInfo.linearForce ) );
        physicsInfoMsg->set_allocated_angularvelocity( GetVelocityMsg( thePhysicsInfo.angularVelocity ) );
        physicsInfoMsg->set_allocated_angularforce( GetForceMsg( thePhysicsInfo.angularForce ) );
        physicsInfoMsg->set_allocated_angularposition( GetPointMsg( thePhysicsInfo.angularPosition ) );
    }

    AabbMessage* NetUtils::GetAabbObjectMsg( AABB* aabbObject )
    {
        AabbMessage* aabbMsg = new AabbMessage();

        aabbMsg->set_allocated_collidableobject( GetCollidableObjectMsg( aabbObject->getID(), aabbObject->getCenter(), aabbObject->isMovable() ) );
        aabbMsg->set_radiusx( aabbObject->getXRadius() );
        aabbMsg->set_radiusy( aabbObject->getYRadius() );
        aabbMsg->set_radiusz( aabbObject->getZRadius() );

        return aabbMsg;
    }

    SphereMessage* NetUtils::GetSphereObjectMsg( Sphere* sphereObject )
    {
        SphereMessage* sphereMsg = new SphereMessage();

        sphereMsg->set_allocated_collidableobject( GetCollidableObjectMsg( sphereObject->getID(), sphereObject->getCenter(), sphereObject->isMovable() ) );
        sphereMsg->set_radius( sphereObject->getRadius() );

        return sphereMsg;
    }

    CollidableObjectMessage* NetUtils::GetCollidableObjectMsg( int ID, Point center, int movable )
    {
        CollidableObjectMessage* collidableObjectMsg = new CollidableObjectMessage();

        collidableObjectMsg->set_id( ID );
        collidableObjectMsg->set_allocated_center( GetPointMsg( center ) );
        collidableObjectMsg->set_movable( movable );

        return collidableObjectMsg;
    }

    PointMessage* NetUtils::GetPointMsg( Point point )
    {
        PointMessage* pointMsg = new PointMessage();

        pointMsg->set_x( point.x );
        pointMsg->set_y( point.y );
        pointMsg->set_z( point.z );

        return pointMsg;
    }

    VelocityMessage* NetUtils::GetVelocityMsg( Velocity velocity )
    {
        VelocityMessage* velocityMsg = new VelocityMessage();

        velocityMsg->set_x( velocity.x );
        velocityMsg->set_y( velocity.y );
        velocityMsg->set_z( velocity.z );

        return velocityMsg;
    }

    ForceMessage* NetUtils::GetForceMsg( Force force )
    {
        ForceMessage* forceMsg = new ForceMessage();

        forceMsg->set_x( force.x );
        forceMsg->set_y( force.y );
        forceMsg->set_z( force.z );

        return forceMsg;
    }

    physicsInfo NetUtils::GetPhysicsInfo( CollidableObject *obj, float mass, Velocity linVel, Force linForce,
            Velocity angVel, Force angForce, Point angPos )
    {
        physicsInfo thePhysicsInfo;
        thePhysicsInfo.mass = mass;

        thePhysicsInfo.collidableObject = obj;
        thePhysicsInfo.linearVelocity = linVel;
        thePhysicsInfo.angularVelocity = angVel;
        thePhysicsInfo.angularPosition = angPos;
        thePhysicsInfo.linearForce = linForce;
        thePhysicsInfo.angularForce = angForce;

        return thePhysicsInfo;
    }

    vector<physicsInfo> NetUtils::GetGameEngineCreateObj( GameEngineMessage* gameEngineMsg )
    {
        return GetGameEngineRetrieveObj( gameEngineMsg );
    }

    vector<physicsInfo> NetUtils::GetGameEngineRetrieveObj( GameEngineMessage* gameEngineMsg )
    {
        vector<physicsInfo> physicsInfos;

        for( int i = 0; i < gameEngineMsg->physicsinfo_size(); i++ )
        {
            physicsInfo thePhysicsInfo;
            PhysicsInfoMessage physicsInfoMsg = gameEngineMsg->physicsinfo(i);

            if( physicsInfoMsg.has_aabbobject() )
            {
                thePhysicsInfo.collidableObject = GetAABBObj( physicsInfoMsg.aabbobject() );
            }
            else if( physicsInfoMsg.has_sphereobject() )
            {
                thePhysicsInfo.collidableObject = GetSphereObj( physicsInfoMsg.sphereobject() );
            }

            thePhysicsInfo.mass = physicsInfoMsg.mass();

            thePhysicsInfo.linearVelocity = GetVelocityObj( physicsInfoMsg.linearvelocity() );
            thePhysicsInfo.linearForce = GetForceObj( physicsInfoMsg.linearforce() );
            thePhysicsInfo.angularVelocity = GetVelocityObj( physicsInfoMsg.angularvelocity() );
            thePhysicsInfo.angularForce = GetForceObj( physicsInfoMsg.angularforce() );
            thePhysicsInfo.angularPosition = GetPointObj( physicsInfoMsg.angularposition() );

            physicsInfos.push_back( thePhysicsInfo );
        }

        return physicsInfos;
    }

    map<int, Point> NetUtils::GetUpdateObj( GameEngineMessage* gameEngineMsg )
    {
        map<int, Point> updateObjMap;

        for( int i = 0; i < gameEngineMsg->updateobject_size(); i++ )
        {
            UpdateObjectMessage updateObjMsg = gameEngineMsg->updateobject( i );
            int ID = updateObjMsg.id();
            Point position = GetPointObj( updateObjMsg.position() );

            updateObjMap.insert( pair<int, Point>( ID, position ) );
        }

        return updateObjMap;
    }

    vector<int> NetUtils::GetDeleteObj( GameEngineMessage* gameEngineMsg )
    {
        vector<int> deleteObjVector;

        for( int i = 0; i < gameEngineMsg->deleteobject_size(); i++ )
        {
            DeleteObjectMessage deleteObjMsg = gameEngineMsg->deleteobject( i );

            int ID = deleteObjMsg.id();

            deleteObjVector.push_back( ID );
        }

        return deleteObjVector;
    }

    AABB* NetUtils::GetAABBObj( const AabbMessage& aabbObjectMsg )
    {
        CollidableObjectMessage collidableObjectMsg = aabbObjectMsg.collidableobject();

        int ID = collidableObjectMsg.id();
        Point center = GetPointObj( collidableObjectMsg.center() );
        float radii[3] = {0.0f, 0.0f, 0.0f};
        radii[0] = aabbObjectMsg.radiusx();
        radii[1] = aabbObjectMsg.radiusy();
        radii[2] = aabbObjectMsg.radiusz();
        int movable = collidableObjectMsg.movable();

        AABB* aabbObject = new AABB( ID, center, radii, movable  );

        return aabbObject;
    }

    Sphere* NetUtils::GetSphereObj( const SphereMessage& sphereObjectMsg )
    {
        CollidableObjectMessage collidableObjectMsg = sphereObjectMsg.collidableobject();

        int ID = collidableObjectMsg.id();
        Point center = GetPointObj( collidableObjectMsg.center() );
        float radius = sphereObjectMsg.radius();
        int movable = collidableObjectMsg.movable();

        Sphere* sphereObject = new Sphere( ID, center, radius, movable );

        return sphereObject;
    }

    Point NetUtils::GetPointObj( const PointMessage& pointMsg )
    {
        Point center;

        center.x = pointMsg.x();
        center.y = pointMsg.y();
        center.z = pointMsg.z();

        return center;
    }

    Velocity NetUtils::GetVelocityObj( const VelocityMessage& velocityMsg )
    {
        Velocity velocity;

        velocity.x = velocityMsg.x();
        velocity.y = velocityMsg.y();
        velocity.z = velocityMsg.z();

        return velocity;
    }

    Force NetUtils::GetForceObj( const ForceMessage& forceMsg )
    {
        Force force;

        force.x = forceMsg.x();
        force.y = forceMsg.y();
        force.z = forceMsg.z();

        return force;
    }
}
