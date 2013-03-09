#ifndef PHYSICS_INFO_H
#define PHYSICS_INFO_H

#include "CollidableObject.h"
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
    int ID;
    CollidableObject *collidableObject;
    //Point oldPosition;
    Velocity linearVelocity;
    float mass;
    Point angularPosition; //point used for rendering
    Velocity angularVelocity; //One value will always be 0, only 2d ANgular velocity
    Force linearForce;//force actual acc = force/mass
    Force angularForce;//One value will always be 0, only 2d ANgular velocity

    int movable;

} physicsInfo;
#endif
