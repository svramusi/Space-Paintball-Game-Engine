#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <vector>
#include "physicsinfo.h"
#include "collisioninfo.h"
#include "collisiondetection.h"

class PhysicsEngine {

public:
    PhysicsEngine();
    PhysicsEngine(float grav, float air, unsigned int startTime);
    ~PhysicsEngine();

    void SetWorldParams(float grav, float air, unsigned int startTime);

    void updateWorld(unsigned int timeStep);

    void insertPhysicsObject(CollidableObject *obj, float mass, Velocity linVel, Force linAcc, Velocity angVel, Force angAcc, Point angPos);


    std::vector<physicsInfo> getUpdatedObjects();
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

    bool isMoving(const physicsInfo *item);

    //Returns original location to make the hack work
    Point moveItem(physicsInfo *item, penetration_t penetration);
    void moveItem(physicsInfo *item, Point origCenter);

    physicsInfo* findItem(int ID);

    std::vector<int> objectsMovedThisTurn;
    bool hasObjectBeenInCollision(int ID);
};
#endif
