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

    float getPenetrationDistance(float dist_between_centers, float radiusSum);
    std::vector<float> getNormalizedVector(Point point1, Point point2);
    std::vector<float> getPenetrationVector(sphere_t sphere1, sphere_t sphere2);

    std::vector<float> getDiffVectorAbs(Point point1, Point point2);
    std::vector<float> getDiffVector(Point point1, Point point2);


private:

};
#endif
