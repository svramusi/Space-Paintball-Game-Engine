#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <vector>
#include "physicsinfo.h"
#include "collisioninfo.h"
#include "collisiondetection.h"

#include "CollidableObject.h"

class PhysicsEngine {

public:
    float gravity;
    float airfriction;
    PhysicsEngine();
    PhysicsEngine(float grav, float air);
    void SetWorldParams(float grav, float air);
    ~PhysicsEngine();
    void updateWorld(float timeStep);

    void insertPhysicsObject(CollidableObject *obj, float mass, Velocity linVel, Force linAcc, Velocity angVel, Force angAcc, Point angPos);
private:
    CollisionDetection *cd;

    int latestID;

    std::vector<physicsInfo> physicsObjects;

    void calculatePosition(physicsInfo *item, float deltaT);
    void calculateLinearVelocity(physicsInfo *item, float deltaT);
    void calculateLinearAcceleration(physicsInfo *item, float deltaT);
    void calculateAngularPosition(physicsInfo *item, float deltaT);
    void calculateAngularVelocity(physicsInfo *item, float deltaT);
    void calculateAngularAcceleration(physicsInfo *item, float deltaT);
    Point calculatePointofImapct(physicsInfo *item, float deltaT);
    float GetDistanceOfVertex(float x, float y);

    float calculateAngle(Point POI, Point Center, Point p3);


    //V2 ALWAYS NEEDS TO BE THE MIDDLE VERTEX
    float GetAngleBetweenVerticese(Point v1, Point v2, Point v3);


    float RadiansToDegrees(float rad);
    float GetDistanceBetweenVertices(Point v1, Point v2);

};
#endif
