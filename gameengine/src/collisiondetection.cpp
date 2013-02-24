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

int
CollisionDetection::isIntersection(sphere_t sphere1, sphere_t sphere2)
{
    typedef std::vector<float> float_vect;
    float_vect diff_vector(3);
    diff_vector[0] = sphere1.center.x - sphere2.center.x;
    diff_vector[1] = sphere1.center.y - sphere2.center.y;
    diff_vector[2] = sphere1.center.z - sphere2.center.z;

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
    typedef std::vector<float> float_vect;

    float_vect ab(3);
    ab[0] = endPoint.x - startPoint.x;
    ab[1] = endPoint.y - startPoint.y;
    ab[2] = endPoint.z - startPoint.z;

    float_vect ac(3);
    ac[0] = vertex.x - startPoint.x;
    ac[1] = vertex.y - startPoint.y;
    ac[2] = vertex.z - startPoint.z;

    float_vect bc(3);
    bc[0] = vertex.x - endPoint.x;
    bc[1] = vertex.y - endPoint.y;
    bc[2] = vertex.z - endPoint.z;


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
