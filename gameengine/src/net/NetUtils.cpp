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

	void NetUtils::Send( net::GameEngine& input, net::Socket& socket )
	{
		///////////////////////////////////////////////////////////////////
		// Initialize payload
		///////////////////////////////////////////////////////////////////

		printf( "Size after serilizing is %d\n", input.ByteSize() );
		int size = input.ByteSize() + 4;
		char *packet = new char [size];
		google::protobuf::io::ArrayOutputStream aos(packet,size);
		CodedOutputStream *coded_output = new CodedOutputStream(&aos);
		coded_output->WriteVarint32(input.ByteSize());
		input.SerializeToCodedStream(coded_output);
		///////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////
		// Client socket work - send payload to server
		///////////////////////////////////////////////////////////////////
		bool sent = socket.Send( (void *) packet, size );

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

	net::GameEngine* NetUtils::ReadBody( net::Socket* socket, google::protobuf::uint32 size )
	{
		int bytecount;
		net::GameEngine* payload =  new net::GameEngine();
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

	/**
	 * Dummy function to generate fake message object.
	 */
	net::GameEngine* NetUtils::GetGameEnginePayload()
	{
		net::GameEngine* gameEnginePayload = new net::GameEngine();

		/*
		 * Add physics object to Game Engine object.
		 */
		net::PhysicsInfo* physicsInfo1 = gameEnginePayload->add_physicsinfo();
		net::PhysicsInfo* physicsInfo2 = gameEnginePayload->add_physicsinfo();

		SetPhysicsInfo( physicsInfo1, 1.0f );
		SetPhysicsInfo( physicsInfo2, 2.0f );

		return gameEnginePayload;
	}

	/*
	 * Dummy function to generate fake PhysicsInfo message.
	 */
	void NetUtils::SetPhysicsInfo( net::PhysicsInfo* physicsInfo, float value )
	{
		physicsInfo->set_mass( value );

		/*
		 * Aaab object.
		 */
		net::Aabb* aabbObject = new net::Aabb();
		aabbObject->add_radii( value );
		aabbObject->add_radii( value );
		aabbObject->add_radii( value );

		net::Point* center1 = new net::Point();
		center1->set_x( value );
		center1->set_y( value );
		center1->set_z( value );

		aabbObject->set_allocated_center( center1 );

		physicsInfo->set_allocated_aabbobject( aabbObject );

		/*
		 * Sphere object.
		 */
		net::Sphere* sphereObject = new net::Sphere();
		sphereObject->set_radius( value );

		net::Point* center2 = new net::Point();
		center2->set_x( value );
		center2->set_y( value );
		center2->set_z( value );

		sphereObject->set_allocated_center( center2 );

		physicsInfo->set_allocated_sphereobject( sphereObject );

		/*
		 * Linear Velocity.
		 */
		net::Velocity* linearVelocity = new net::Velocity();
		linearVelocity->set_x( value );
		linearVelocity->set_y( value );
		linearVelocity->set_z( value );

		physicsInfo->set_allocated_linearvelocity( linearVelocity );

		/*
		 * Angular Velocity.
		 */
		net::Velocity* angularVelocity = new net::Velocity();
		angularVelocity->set_x( value );
		angularVelocity->set_y( value );
		angularVelocity->set_z( value );

		physicsInfo->set_allocated_angularvelocity( angularVelocity );

		/*
		 * Angular Position.
		 */
		net::Point* angularPosition = new net::Point();
		angularPosition->set_x( value );
		angularPosition->set_y( value );
		angularPosition->set_z( value );

		physicsInfo->set_allocated_angularposition( angularPosition );

		/*
		 * Linear Force.
		 */
		net::Force* linearForce = new net::Force();
		linearForce->set_x( value );
		linearForce->set_y( value );
		linearForce->set_z( value );

		physicsInfo->set_allocated_linearforce( linearForce );

		/*
		 * Angular Force.
		 */
		net::Force* angularForce = new net::Force();
		angularForce->set_x( value );
		angularForce->set_y( value );
		angularForce->set_z( value );

		physicsInfo->set_allocated_angularforce( angularForce );
	}
}
