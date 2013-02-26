#include <stdlib.h>
#include <stdio.h>

#include "collisiondetection.h"

using namespace std;
using namespace arma;

CollisionDetection::CollisionDetection()
{
}

CollisionDetection::~CollisionDetection()
{
}

collisionDetection*
CollisionDetection::detect_collision(detectCollision* collidableObject)
{
    collisionDetection *cd;
    cd = (collisionDetection*)malloc(sizeof(collisionDetection));

    cd->prev = NULL;
    cd->next = NULL;
    cd->objectID = 0;
    cd->collisionID = 0;

    //detect collisions
    printf("collidable object id: %i\n",collidableObject->collidableObjectID);

    return cd;
}

float
CollisionDetection::getPenetrationDistance(float dist_between_centers, float radiusSum)
{
    return dist_between_centers - radiusSum;
}

std::vector<float>
CollisionDetection::getNormalizedVector(Point point1, Point point2)
{
    std::vector<float> numerator;
    std::vector<float> denom;

    numerator = getDiffVector(point1, point2);
    denom = getDiffVectorAbs(point1, point2);

    std::vector<float> normalized;
    normalized.resize(3);

    if(denom[0] != 0)
        normalized[0] = numerator[0]/denom[0];
    else
        normalized[0] = numerator[0];

    if(denom[1] != 0)
        normalized[1] = numerator[1]/denom[1];
    else
        normalized[1] = numerator[1];

    if(denom[2] != 0)
        normalized[2] = numerator[2]/denom[2];
    else
        normalized[2] = numerator[2];

    return normalized;
}

std::vector<float>
CollisionDetection::getPenetrationVector(sphere_t sphere1, sphere_t sphere2)
{
    std::vector<float> diff_vector;
    diff_vector = getDiffVector(sphere1.center, sphere2.center);

    colvec d = conv_to< colvec >::from(diff_vector);
    float dist_between_centers = dot(d, d);
    float radiusSum = sphere1.radius + sphere2.radius;

    float penetration = getPenetrationDistance(dist_between_centers, radiusSum);
    std::vector<float> normalized = getNormalizedVector(sphere1.center, sphere2.center);


    std::vector<float> penetrationVector(3);
    penetrationVector[0] = normalized[0] * penetration;
    penetrationVector[1] = normalized[1] * penetration;
    penetrationVector[2] = normalized[2] * penetration;

    return penetrationVector;
}

int
CollisionDetection::isIntersection(aabb_t aabb1, aabb_t aabb2)
{
    if(abs(aabb1.center.x - aabb2.center.x) > (aabb1.radii[0] + aabb2.radii[0]))
        return 0;

    if(abs(aabb1.center.y - aabb2.center.y) > (aabb1.radii[1] + aabb2.radii[1]))
        return 0;

    if(abs(aabb1.center.z - aabb2.center.z) > (aabb1.radii[2] + aabb2.radii[2]))
        return 0;

    return 1;
}

std::vector<float>
CollisionDetection::getDiffVectorAbs(Point point1, Point point2)
{
    std::vector<float> diff_vector(3);
    diff_vector[0] = abs(point1.x - point2.x);
    diff_vector[1] = abs(point1.y - point2.y);
    diff_vector[2] = abs(point1.z - point2.z);

    return diff_vector;
}

std::vector<float>
CollisionDetection::getDiffVector(Point point1, Point point2)
{
    std::vector<float> diff_vector(3);
    diff_vector[0] = point1.x - point2.x;
    diff_vector[1] = point1.y - point2.y;
    diff_vector[2] = point1.z - point2.z;

    return diff_vector;
}

int
CollisionDetection::isIntersection(sphere_t sphere1, sphere_t sphere2)
{
    std::vector<float> diff_vector;
    diff_vector = getDiffVectorAbs(sphere1.center, sphere2.center);

    colvec d = conv_to< colvec >::from(diff_vector);
    float dist_between_centers = dot(d, d);
    float radiusSum = sphere1.radius + sphere2.radius;

    return dist_between_centers <= radiusSum * radiusSum;
}

int
CollisionDetection::isIntersection(aabb_t aabb, sphere_t sphere)
{
    if(abs(aabb.center.x - sphere.center.x) > (aabb.radii[0] + sphere.radius))
        return 0;

    if(abs(aabb.center.y - sphere.center.y) > (aabb.radii[1] + sphere.radius))
        return 0;

    if(abs(aabb.center.z - sphere.center.z) > (aabb.radii[2] + sphere.radius))
        return 0;

    return 1;
}

int
CollisionDetection::isIntersection(sphere_t sphere, capsule_t capsule)
{
    return 1;
}

float
CollisionDetection::getDistanceBetweenLineAndVertex(Point startPoint, Point endPoint, Point vertex)
{
    std::vector<float> ab = getDiffVectorAbs(endPoint, startPoint);
    std::vector<float> ac = getDiffVectorAbs(vertex, startPoint);
    std::vector<float> bc = getDiffVectorAbs(vertex, endPoint);

    colvec cv_ac = conv_to< colvec >::from(ac);
    colvec cv_ab = conv_to< colvec >::from(ab);

    float e = dot(cv_ac, cv_ab);

    if(e <= 0.0f)
        return dot(cv_ac, cv_ac);

    float f = dot(cv_ab, cv_ab);

    if(e >= f)
    {
        colvec cv_bc = conv_to< colvec >::from(bc);
        return dot(cv_bc, cv_bc);
    }

    return dot(cv_ac, cv_ac) - e * e / f;
}
