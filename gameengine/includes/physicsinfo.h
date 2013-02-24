#ifndef PHYSICS_INFO_H
#define PHYSICS_INFO_H

#include "AABB.h"
#include "Sphere.h"
#include "Point.h"
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
	aabb_t *aabbObject;   //one will always be NULL
	sphere_t *sphereObject; //.center for Position
	//Point oldPosition;
	Velocity linearVelocity;
	float mass;

	Velocity angularVelocity; //One value will always be 0, only 2d ANgular velocity
	Force linearForce;//force actual acc = force/mass
	Force angularForce;//One value will always be 0, only 2d ANgular velocity

} physicsInfo;
