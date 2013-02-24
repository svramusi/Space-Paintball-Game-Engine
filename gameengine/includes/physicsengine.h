#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <vector>
#include "physicsinfo.h"
#include "collisioninfo.h"
#include "collisiondetection.h"

class PhysicsEngine {

public:
	float gravity;
	float airfriction;
	PhysicsEngine();
	PhysicsEngine(float grav, float air);
	int SetWorldParams(float grav, float air);
    ~PhysicsEngine();
    void updateWorld();
    physicsInfo insertPhysicsObject(aabb_t *obj, float mass, Velocity linVel, Force linAcc, Velocity angVel, Force angAcc, Point angPos);
    physicsInfo insertPhysicsObject(sphere_t *obj, float mass, Velocity linVel, Force linAcc, Velocity angVel, Force angAcc, Point angPos);
private:
    CollisionDetection *cd;

    std::vector<physicsInfo> physicsObjects;

    void calculatePosition(physicsInfo obj, float deltaT);
    void calculateLinearVelocity(physicsInfo &item, float deltaT);
    void calculateLinearAcceleration(physicsInfo &item, float deltaT);
    void calculateAngularVelocity(physicsInfo &item, float deltaT);
    void calculateAngularVelocity(physicsInfo &item, float deltaT);
    void calculateAngularAcceleration(physicsInfo &item, float deltaT);
    Point calculatePointofImapct(physicsInfo &item, float deltaT);

    void freeCollisions(collisionDetection* collisions);

};
#endif
