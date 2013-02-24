#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "collisioninfo.h"
#include "AABB.h"
#include "Sphere.h"
#include "Capsule.h"

#include <armadillo>
#include <cmath>

class CollisionDetection {
public:
    CollisionDetection();
    ~CollisionDetection();
    collisionDetection* detect_collision(detectCollision* collidableObject);

    int isIntersection(aabb_t aabb1, aabb_t aabb2);
    int isIntersection(sphere_t sphere1, sphere_t sphere2);
    int isIntersection(aabb_t aabb, sphere_t sphere);
    int isIntersection(sphere_t sphere, capsule_t capsule);

    float getDistanceBetweenLineAndVertex(Point startPoint, Point endPoint, Point vertex);

private:

};
#endif
