#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H
#include <vector>
#include "physicsinfo.h"
#include "collisioninfo.h"
#include "collisiondetection.h"

class PhysicsEngine {


public:
	PhysicsEngine();
	PhysicsEngine(float grav, float air);
	void SetWorldParams(float grav, float air);
    ~PhysicsEngine();
    void updateWorld();

private:
    CollisionDetection *cd;
    float gravity, airfriction;
    vector<physicsInfo*> physicObjects;

    void freeCollisions(collisionDetection* collisions);
    void calculateCenterOfMass();
    void calculateSpeed();
    void calculateAcceleration();
    void calculateAngularVelocity();
    void calculateAngularPosition();
    void calculatePosition();
    void solveCollisionEquation();
    void insertPhysicsObject(); //add objects to init items
    void removePhysicsObject(physicsInfo id);

    void updatePhysics(int ms);
};
#endif
