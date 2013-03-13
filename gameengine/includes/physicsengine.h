#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <vector>
#include "physicsinfo.h"
#include "collisioninfo.h"
#include "collisiondetection.h"

#include "CollidableObject.h"

class PhysicsEngine {

public:
    PhysicsEngine();
    PhysicsEngine(float grav, float air);
    void SetWorldParams(float grav, float air);
    ~PhysicsEngine();
    void updateWorld(float timeStep);

    void insertPhysicsObject(CollidableObject *obj, float mass, Velocity linVel, Force linAcc, Velocity angVel, Force angAcc, Point angPos);
private:
    CollisionDetection *cd;

    float gravity;
    float airFriction;

    int latestID;

    float lastTimeStep;

    std::vector<physicsInfo> physicsObjects;

    void calculatePosition(physicsInfo *item, float deltaT);
    void calculateLinearVelocity(physicsInfo *item, float deltaT);
    void calculateLinearForce(physicsInfo *item, float deltaT);
    void calculateAngularPosition(physicsInfo *item, float deltaT);
    void calculateAngularVelocity(physicsInfo *item, float deltaT);
    void calculateAngularAcceleration(physicsInfo *item, float deltaT);
    Point calculatePointofImapct(physicsInfo *item, float deltaT);
    float GetDistanceOfVertex(float x, float y);

    float calculateAngle(Point POI, Point Center, Point p3);

    void resolveCollisions();

    //V2 ALWAYS NEEDS TO BE THE MIDDLE VERTEX
    float GetAngleBetweenVerticese(Point v1, Point v2, Point v3);


    float RadiansToDegrees(float rad);
    float GetDistanceBetweenVertices(Point v1, Point v2);
    void freeCollisions(collisionDetection* collisions);

    bool isMoving(const physicsInfo *item);
    void moveItem(physicsInfo *item, penetration_t penetration);

    physicsInfo* findItem(int ID);

};
#endif
