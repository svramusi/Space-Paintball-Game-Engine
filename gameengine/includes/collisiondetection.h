#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "collisioninfo.h"

#include "Point.h"
#include "AABBClass.h"
#include "SphereClass.h"
#include "Capsule.h"

#include <armadillo>
#include <cmath>
#include <typeinfo>

struct collision_info_t;

struct penetration_t {
    float x;
    float y;
    float z;
};

struct collision_info_t {
    int ID; //id of the object that collides with the ID specified in collisions_t

    //grrrrrrrr
    //std::vector<float> penetration; //penetration vector that you'll use to resolve the collision
    penetration_t penetration;

    collision_info_t *next;
};

struct collisions_t {
    int ID;
    collision_info_t *info;
    collisions_t *next;
};

const float EPSILON = 0.0001f;

class CollisionDetection {
public:
    CollisionDetection();
    ~CollisionDetection();

    void freeCollisions(collisions_t *collisions);

    void addObject(CollidableObject *collidableObject);
    void removeObject(int ID);

    void updateObject(int ID, Point newCenter);

    //Don't create a capsule for this
    //This is after the physics engine has resolved a collision
    void fixObject(int ID, Point newCenter);

    int isIntersection(const CollidableObject *obj1, const CollidableObject *obj2);

    float getSquareDistanceBetweenLineAndVertex(Point startPoint, Point endPoint, Point vertex);

    float getPenetrationDistance(const Sphere *sphere1, const Sphere *sphere2);
    std::vector<float> getNormalizedVector(Point point1, Point point2);


    penetration_t getPenetrationVector(const CollidableObject *obj1, const CollidableObject *obj2);

    std::vector<float> getDiffVectorAbs(Point point1, Point point2);
    std::vector<float> getDiffVector(Point point1, Point point2);

    Point getClosestPoint(const AABB *aabb, const Point vertex);


    collisions_t* checkForAnyCollisions();


/*

collisionWorld(...);
 
Adding removing objects:
 
int
addObject(CollisionShape cs, Transform t);
 
void
removeObject(int ID);
 
Updating objects:
 
void
updateObjectNewCenter
(int ID, Point newCenterPoint);

<I UPDATED THIS TO WHAT I THINK MAKES SENSE FOR US>

 

Collision Queries:
 
bool
collision(int ID1, int ID2);
 
List<CollisionData>
checkForAnyCollisions(); 
*/



private:
    std::vector<CollidableObject*> collidableObjects;

    int isIntersection(const AABB *aabb1, const AABB *aabb2);
    int isIntersection(const Sphere *sphere1, const Sphere *sphere2);
    int isIntersection(const AABB *aabb, const Sphere *sphere);
    int isIntersection(const AABB *aabb, const Capsule *capsule);

    penetration_t getPenetrationVector(const Sphere *sphere1, const Sphere *sphere2);
    penetration_t getPenetrationVector(const AABB *aabb1, const AABB *aabb2);
    penetration_t getPenetrationVector(const AABB *aabb, const Sphere *sphere);
    penetration_t getPenetrationVector(const AABB *aabb, const Capsule *capsule);

    int getNextID();
    void removeAllCapsules();

    int latestID;

};
#endif
