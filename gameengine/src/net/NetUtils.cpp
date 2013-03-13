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

	GameEngineMessage* NetUtils::GetUpdateObjectMsg( int ID, Point position )
	{
		GameEngineMessage* gameEnginePayload = new GameEngineMessage();
		gameEnginePayload->set_messagetype( GameEngineMessage::UPDATE );

		UpdateObjectMessage* updateObjectMsg = gameEnginePayload->add_updateobject();

		updateObjectMsg->set_id( ID );
		updateObjectMsg->set_allocated_position( GetPointMsg( position) );

		return gameEnginePayload;
	}

	GameEngineMessage* NetUtils::GetDeleteObjectMsg( int ID )
	{
		GameEngineMessage* gameEnginePayload = new GameEngineMessage();
		gameEnginePayload->set_messagetype( GameEngineMessage::DELETE );

		DeleteObjectMessage* deleteObjectMsg = gameEnginePayload->add_deleteobject();

		deleteObjectMsg->set_id( ID );

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

	/*
	 * Dummy function to generate fake PhysicsInfo object.
	 */
	physicsInfo NetUtils::GetPhysicsInfo( float value )
	{
		physicsInfo thePhysicsInfo;
		thePhysicsInfo.mass = value;

		/*
		 * Aaab object.
		 */
		Point center1;
		center1.x = value;
		center1.y = value;
		center1.z = value;

		int ID = (int) value;
		float radii[3] = { value, value, value };
		int movable = (int) value;

		AABB* aabbObject = new AABB( ID, center1, radii, movable );

		thePhysicsInfo.collidableObject = aabbObject;
		/*
		 * Sphere object.
		 */
/*
		Point center2;
		center2.x = value;
		center2.y = value;
		center2.z = value;

		int radius = (int) value;

		Sphere* sphereObject = new Sphere( ID, center2, radius, movable );
*/
		/*
		 * Linear Velocity.
		 */
		Velocity linearVelocity;
		linearVelocity.x = value;
		linearVelocity.y = value;
		linearVelocity.z = value;

		thePhysicsInfo.linearVelocity = linearVelocity;

		/*
		 * Angular Velocity.
		 */
		Velocity angularVelocity;
		angularVelocity.x = value;
		angularVelocity.y = value;
		angularVelocity.z = value;

		thePhysicsInfo.angularVelocity = angularVelocity;

		/*
		 * Angular Position.
		 */
		Point angularPosition;
		angularPosition.x = value;
		angularPosition.y = value;
		angularPosition.z = value;

		thePhysicsInfo.angularPosition = angularPosition;

		/*
		 * Linear Force.
		 */
		Force linearForce;
		linearForce.x = value;
		linearForce.y = value;
		linearForce.z = value;

		thePhysicsInfo.linearForce = linearForce;

		/*
		 * Angular Force.
		 */
		Force angularForce;
		angularForce.x = value;
		angularForce.y = value;
		angularForce.z = value;

		thePhysicsInfo.angularForce = angularForce;

		return thePhysicsInfo;
	}

	vector<physicsInfo> NetUtils::GetPhysicsInfoObj( GameEngineMessage* gameEngineMsg )
	{
		vector<physicsInfo> physicsInfos;

		for( int i = 0; i < gameEngineMsg->physicsinfo_size(); i++ )
		{
			physicsInfo thePhysicsInfo;
			PhysicsInfoMessage physicsInfoMsg = gameEngineMsg->physicsinfo(i);

			if( physicsInfoMsg.has_aabbobject() )
			{
				AabbMessage aabbObjectMsg = physicsInfoMsg.aabbobject();
				CollidableObjectMessage collidableObjectMsg = aabbObjectMsg.collidableobject();

				int ID = collidableObjectMsg.id();
				Point center = GetPointObj( collidableObjectMsg.center() );
				float radii[3] = {0.0f, 0.0f, 0.0f};
				radii[0] = aabbObjectMsg.radiusx();
				radii[1] = aabbObjectMsg.radiusy();
				radii[2] = aabbObjectMsg.radiusz();
				int movable = collidableObjectMsg.movable();

				AABB* aabbObject = new AABB( ID, center, radii, movable  );

				thePhysicsInfo.collidableObject = aabbObject;
			}
			else if( physicsInfoMsg.has_sphereobject() )
			{
				SphereMessage sphereObjectMsg = physicsInfoMsg.sphereobject();
				CollidableObjectMessage collidableObjectMsg = sphereObjectMsg.collidableobject();

				int ID = collidableObjectMsg.id();
				Point center = GetPointObj( collidableObjectMsg.center() );
				float radius = sphereObjectMsg.radius();
				int movable = collidableObjectMsg.movable();

				Sphere* sphereObject = new Sphere( ID, center, radius, movable );

				thePhysicsInfo.collidableObject = sphereObject;
			}

			thePhysicsInfo.mass = physicsInfoMsg.mass();

			physicsInfos.push_back( thePhysicsInfo );
		}

		return physicsInfos;
	}

	Point GetPointObj( const PointMessage& pointMsg )
	{
		Point center;

		center.x = pointMsg.x();
		center.y = pointMsg.y();
		center.z = pointMsg.z();

		return center;
	}
}
