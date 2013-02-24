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
    void calculateLinearVelocity(physicsInfo *item, float deltaT);
    void calculateLinearAcceleration(physicsInfo *item, float deltaT);
    void calculateAngularVelocity(physicsInfo *item, float deltaT);
    void calculateAngularVelocity(physicsInfo *item, float deltaT);
    void calculateAngularAcceleration(physicsInfo *item, float deltaT);
    Point calculatePointofImapct(physicsInfo *item, float deltaT);
    float GetDistanceOfVertex(float x, float y);

    float calculateAngle(Point POI, Point Center, Point p3);

    Point calculatePointofImapct(physicsInfo *item, float deltaT);

            //V2 ALWAYS NEEDS TO BE THE MIDDLE VERTEX
    float GetAngleBetweenVerticese(Point v1, Point v2, Point v3);


    float RadiansToDegrees(float rad);
    float GetDistanceBetweenVertices(Point v1, Point v2);
    void freeCollisions(collisionDetection* collisions);

};
#endif
