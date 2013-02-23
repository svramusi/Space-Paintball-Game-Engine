#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <vector>
#include "physicsinfo.h"
#include "collisioninfo.h"
#include "collisiondetection.h"

class PhysicsEngine {
	float gravity, airfriction;
public:
	PhysicsEngine();
	PhysicsEngine(float grav, float air);
	int SetWorldParams(float grav, float air);
    ~PhysicsEngine();
    void updateWorld();
    physicsInfo insertPhysicsObject(aabb_t *obj, float mass, Velocity linVel, Force linAcc, Velocity angVel, Force angAcc);
    physicsInfo insertPhysicsObject(sphere_t *obj, float mass, Velocity linVel, Force linAcc, Velocity angVel, Force angAcc);
private:
    CollisionDetection *cd;
   vector<physicsInfo> physicsObjects;

    void freeCollisions(collisionDetection* collisions);

};
#endif
