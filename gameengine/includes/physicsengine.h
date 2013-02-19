#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include "collisioninfo.h"
#include "collisiondetection.h"

class PhysicsEngine {
	float gravity, airfriction;
public:
	PhysicsEngine();
	PhysicsEngine(float grav, float air);
	SetWorldParams(float grav, float air)
    ~PhysicsEngine();
    void updateWorld();

private:
    CollisionDetection *cd;

    void freeCollisions(collisionDetection* collisions);

};
#endif
