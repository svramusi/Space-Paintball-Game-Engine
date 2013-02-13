#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include "collisioninfo.h"
#include "collisiondetection.h"

class PhysicsEngine {
public:
	PhysicsEngine();
    ~PhysicsEngine();
    void updateWorld();

private:
    CollisionDetection *cd;

    void freeCollisions(collisionDetection* collisions);

};
#endif
