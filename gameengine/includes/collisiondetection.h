#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "collisioninfo.h"
#include "AABBClass.h"
#include "SphereClass.h"
#include "Capsule.h"
#include "Point.h"

#include <armadillo>
#include <cmath>
#include <typeinfo>

struct collision_info_t;

struct collision_info_t {
    int ID; //id of the object that collides with the ID specified in collisions_t
    //std::vector<float> p; //penetration vector that you'll use to resolve the collision
    collision_info_t *next;
};

struct collisions_t {
    int ID;
    collision_info_t *info;
    collisions_t *next;
};

class CollisionDetection {
public:
    CollisionDetection();
    ~CollisionDetection();

    void freeCollisions(collisions_t *collisions);

    //collisionDetection* detect_collision(detectCollision* collidableObject);

    void addObject(CollidableObject *collidableObject);
    void removeObject(int ID);

    int isIntersection(CollidableObject *obj1, CollidableObject *obj2);
    int isIntersection(AABB aabb1, AABB aabb2);
    int isIntersection(Sphere sphere1, Sphere sphere2);
    int isIntersection(AABB aabb, Sphere sphere);
    int isIntersection(Sphere sphere, capsule_t capsule);

    float getDistanceBetweenLineAndVertex(Point startPoint, Point endPoint, Point vertex);

    float getPenetrationDistance(float dist_between_centers, float radiusSum);
    std::vector<float> getNormalizedVector(Point point1, Point point2);
    std::vector<float> getPenetrationVector(Sphere sphere1, Sphere sphere2);

    std::vector<float> getDiffVectorAbs(Point point1, Point point2);
    std::vector<float> getDiffVector(Point point1, Point point2);


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

};
#endif
