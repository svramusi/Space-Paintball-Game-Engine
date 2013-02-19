#ifndef PHYSICS_INFO_H
#define PHYSICS_INFO_H

//Shape, position, rotation, mass, moment of inertia, linear and angular velocities
// Maintains physics-relevant information: shapes, mass, velocities, accelerations, etc.
/*Shape
Position (of the CM)
Mass
Linear velocity
Linear acceleration
Angular velocity
Angular acceleration*/
typedef struct physics_info_t { //all units MKS: meters, kilograms, seconds
	float xPos;
	float yPos;
	float zPos;
	float mass;
	float linearVelovity;
	float angularVelocity;
	float linearAcceleration;
	float angularAcceleration;
	//point centerOfMass

} physicsInfo;
