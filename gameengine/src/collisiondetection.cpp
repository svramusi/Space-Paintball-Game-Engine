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

void
CollisionDetection::freeCollisions(collisions_t *collisions)
{
    collisions_t *current = collisions;
    collisions_t *next_current = collisions;

    collision_info_t *current_info = NULL;
    collision_info_t *next_current_info = NULL;

    while(current != NULL) {
        current_info = current->info;

        while(current_info != NULL) {
            next_current_info = current_info->next;
            free(current_info);
            current_info = next_current_info;
        }

        next_current = current->next;
        free(current);
        current = next_current;
    }
}

void
CollisionDetection::addObject(CollidableObject *collidableObject)
{
    collidableObjects.push_back(collidableObject);
}

void
CollisionDetection::removeObject(int ID)
{
    int counter = 0;
    for(std::vector<CollidableObject*>::iterator it = collidableObjects.begin();
            it != collidableObjects.end();
            ++it) {

        if((*it)->getID() == ID) {
            collidableObjects.erase(collidableObjects.begin() + counter);
            break;
        }

        counter++;
    }
}

/*
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
*/

collisions_t*
CollisionDetection::checkForAnyCollisions()
{
    collisions_t *collisions;
    collisions_t *current;

    collisions = NULL;
    current = NULL;

    //THIS IS BEYOND TERRIBLE!!
    //MUST FIX!!!!
    for(std::vector<CollidableObject*>::iterator it1 = collidableObjects.begin(); it1 != collidableObjects.end(); ++it1) {
        for(std::vector<CollidableObject*>::iterator it2 = collidableObjects.begin(); it2 != collidableObjects.end(); ++it2) {
            if((*it1)->getID() == (*it2)->getID())
                continue;

            if(isIntersection(*it1, *it2)) {
                collision_info_t *collision_info;
                collision_info = (collision_info_t*)malloc(sizeof(collision_info_t));

//cout << endl << "found an intersection between: " << (*it1).ID << " and " << (*it2).ID << endl;
//cout << endl << "found a collision and mallocing!!!" << endl;

                collision_info->ID = (*it2)->getID();
                //NEED TO FIX BOTH OF THESE!
                //collision_info->p = std::vector<float>(3);
                collision_info->next = NULL;

                if(collisions == NULL) {
                    collisions = (collisions_t*)malloc(sizeof(collisions_t));
                    collisions->ID = (*it1)->getID();
                    collisions->info = collision_info;
                    collisions->next = NULL;

                    current = collisions;
                }
                else {
                    collisions_t *newCollision = (collisions_t*)malloc(sizeof(collisions_t));
                    newCollision->ID = (*it1)->getID();
                    newCollision->info = collision_info;
                    newCollision->next = NULL;

                    current->next = newCollision;
                    current = newCollision;
                }
            }
        }
    }

    return collisions;
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
CollisionDetection::getPenetrationVector(Sphere *sphere1, Sphere *sphere2)
{
    std::vector<float> diff_vector;
    diff_vector = getDiffVector(sphere1->getCenter(), sphere2->getCenter());

    colvec d = conv_to< colvec >::from(diff_vector);
    float dist_between_centers = dot(d, d);
    float radiusSum = sphere1->getRadius() + sphere2->getRadius();

    float penetration = getPenetrationDistance(dist_between_centers, radiusSum);
    std::vector<float> normalized = getNormalizedVector(sphere1->getCenter(), sphere2->getCenter());


    std::vector<float> penetrationVector(3);
    penetrationVector[0] = normalized[0] * penetration;
    penetrationVector[1] = normalized[1] * penetration;
    penetrationVector[2] = normalized[2] * penetration;

    return penetrationVector;
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
CollisionDetection::isIntersection(CollidableObject *obj1, CollidableObject *obj2)
{
    //TYPE* dynamic_cast<TYPE*> (object);
    //typeid(Poly_Base)==typeid(*ppolybase)
    if((typeid(AABB) == typeid(*obj1)) && (typeid(AABB) == typeid(*obj2)))
        return isIntersection(dynamic_cast<AABB*>(obj1), dynamic_cast<AABB*>(obj2));
    else if((typeid(Sphere) == typeid(*obj1)) && (typeid(Sphere) == typeid(*obj2)))
        return isIntersection(dynamic_cast<Sphere*>(obj1), dynamic_cast<Sphere*>(obj2));
    else if((typeid(AABB) == typeid(*obj1)) && (typeid(Sphere) == typeid(*obj2)))
        return isIntersection(dynamic_cast<AABB*>(obj1), dynamic_cast<Sphere*>(obj2));
    else
        return -1;
}

int
CollisionDetection::isIntersection(AABB *aabb1, AABB *aabb2)
{
    if(abs(aabb1->getCenter().x - aabb2->getCenter().x) >
                (aabb1->getXRadius() + aabb2->getXRadius()))
        return 0;

    if(abs(aabb1->getCenter().y - aabb2->getCenter().y) >
                (aabb1->getYRadius() + aabb2->getYRadius()))
        return 0;

    if(abs(aabb1->getCenter().z - aabb2->getCenter().z) >
                (aabb1->getZRadius() + aabb2->getZRadius()))
        return 0;

    return 1;
}

int
CollisionDetection::isIntersection(Sphere *sphere1, Sphere *sphere2)
{
    std::vector<float> diff_vector;
    diff_vector = getDiffVectorAbs(sphere1->getCenter(), sphere2->getCenter());

    colvec d = conv_to< colvec >::from(diff_vector);
    float dist_between_centers = dot(d, d);
    float radiusSum = sphere1->getRadius() + sphere2->getRadius();

    return dist_between_centers <= radiusSum * radiusSum;
}

int
CollisionDetection::isIntersection(AABB *aabb, Sphere *sphere)
{
    if(abs(aabb->getCenter().x - sphere->getCenter().x) >
                (aabb->getXRadius() + sphere->getRadius()))
        return 0;

    if(abs(aabb->getCenter().y - sphere->getCenter().y) >
                (aabb->getYRadius() + sphere->getRadius()))
        return 0;

    if(abs(aabb->getCenter().z - sphere->getCenter().z) >
                (aabb->getZRadius() + sphere->getRadius()))
        return 0;

    return 1;
}

int
CollisionDetection::isIntersection(Sphere sphere, capsule_t capsule)
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
