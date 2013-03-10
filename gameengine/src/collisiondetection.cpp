#include <stdlib.h>
#include <stdio.h>

#include "collisiondetection.h"

using namespace std;
using namespace arma;

CollisionDetection::CollisionDetection()
{
    latestID = 0;
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

int
CollisionDetection::getNextID()
{
    return latestID + 1;
}

void
CollisionDetection::addObject(CollidableObject *collidableObject)
{
    latestID = collidableObject->getID();
    collidableObjects.push_back(collidableObject);
}

void
CollisionDetection::updateObject(int ID, Point newCenter)
{
    for(std::vector<CollidableObject*>::iterator it = collidableObjects.begin();
            it != collidableObjects.end();
            ++it) {

        if((*it)->getID() == ID) {
            if(typeid(Sphere) == typeid(*(*it)))
            {
                Sphere *tempSphere =
                    dynamic_cast<Sphere*>((*it));

                CollidableObject *capsule = new
                        Capsule(getNextID(),
                        tempSphere->getCenter(),
                        newCenter,
                        tempSphere->getRadius());
/*
            cout << endl << "id: " << capsule->getID() << endl;

            cout << endl
                << "temp sphere x: " << tempSphere->getCenter().x
                << " temp sphere y: " << tempSphere->getCenter().y
                << " new center x: " << newCenter.x
                << " new center y: " << newCenter.y << endl;

            cout << endl
                << "new cap start: " << capsule->getStart().x
                << "," << capsule->getStart().y
                << " new cap end: " << capsule->getEnd().x
                << "," << capsule->getEnd().y << endl;
*/

                addObject(capsule);
            }
            (*it)->setCenter(newCenter);
            break;
        }
    }
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


                if(typeid(Capsule) == typeid(*(*it1)))
                {
                    Capsule *c = dynamic_cast<Capsule*>((*it1));

                    cout << endl << "cap start: " << c->getStart().x
                        << "," << c->getStart().y
                        << " cap end: " << c->getEnd().x
                        << "," << c->getEnd().y << endl;
                }

//cout << endl << "found an intersection between: " << (*it1).ID << " and " << (*it2).ID << endl;

                collision_info->ID = (*it2)->getID();
                collision_info->penetration = getPenetrationVector((*it1), (*it2));
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

    removeAllCapsules();

    return collisions;
}

void
CollisionDetection::removeAllCapsules()
{
    std::vector<int> IDsToRemove;

    for(std::vector<CollidableObject*>::iterator it = collidableObjects.begin();
        it != collidableObjects.end();
        ++it)
    {
        if(typeid(Capsule) == typeid(*(*it)))
        {
            //Can't hose the iterator by deleting it here!
            IDsToRemove.push_back((*it)->getID());
        }
    }

    for(std::vector<int>::iterator it = IDsToRemove.begin();
            it != IDsToRemove.end();
            ++it)
    {
        removeObject(*it);
    }
}

float
CollisionDetection::getPenetrationDistance(const Sphere *sphere1, const Sphere *sphere2)
{
    std::vector<float> diff_vector;
    diff_vector = getDiffVector(sphere1->getCenter(), sphere2->getCenter());

    colvec d = conv_to< colvec >::from(diff_vector);
    float dist_between_centers = dot(d, d);

    float radiusSum = sphere1->getRadius() + sphere2->getRadius();
    float radiusSumSq = radiusSum * radiusSum;

    return sqrt(dist_between_centers) - sqrt(radiusSumSq);
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

penetration_t
CollisionDetection::getPenetrationVector(const CollidableObject *obj1, const CollidableObject *obj2)
{
    if((typeid(AABB) == typeid(*obj1)) && (typeid(AABB) == typeid(*obj2)))
    {
        return getPenetrationVector(dynamic_cast<const AABB*>(obj1), dynamic_cast<const AABB*>(obj2));
    }
    else if((typeid(Sphere) == typeid(*obj1)) && (typeid(Sphere) == typeid(*obj2)))
    {
        return getPenetrationVector(dynamic_cast<const Sphere*>(obj1), dynamic_cast<const Sphere*>(obj2));
    }
    else if((typeid(AABB) == typeid(*obj1)) && (typeid(Sphere) == typeid(*obj2)))
    {
        return getPenetrationVector(dynamic_cast<const AABB*>(obj1), dynamic_cast<const Sphere*>(obj2));
    }
    else if((typeid(Sphere) == typeid(*obj1)) && (typeid(AABB) == typeid(*obj2)))
    {
        return getPenetrationVector(dynamic_cast<const AABB*>(obj2), dynamic_cast<const Sphere*>(obj1));
    }
    else if((typeid(AABB) == typeid(*obj1)) && (typeid(Capsule) == typeid(*obj2)))
    {
        return getPenetrationVector(dynamic_cast<const AABB*>(obj1), dynamic_cast<const Capsule*>(obj2));
    }
    else if((typeid(Capsule) == typeid(*obj1)) && (typeid(AABB) == typeid(*obj2)))
    {
        return getPenetrationVector(dynamic_cast<const AABB*>(obj2), dynamic_cast<const Capsule*>(obj1));
    }
    else
    {
        penetration_t penetration;
        penetration.x = 0;
        penetration.y = 0;
        penetration.z = 0;

        return penetration;
    }
}

penetration_t
CollisionDetection::getPenetrationVector(const AABB *aabb1, const AABB *aabb2)
{
    penetration_t penetrationVector;

    penetrationVector.x = (aabb1->getXRadius() + aabb2->getXRadius())
                            - abs(aabb1->getCenter().x - aabb2->getCenter().x);

    penetrationVector.y = (aabb1->getYRadius() + aabb2->getYRadius())
                            - abs(aabb1->getCenter().y - aabb2->getCenter().y);

    penetrationVector.z = (aabb1->getZRadius() + aabb2->getZRadius())
                            - abs(aabb1->getCenter().z - aabb2->getCenter().z);

    return penetrationVector;
}

penetration_t
CollisionDetection::getPenetrationVector(const Sphere *sphere1, const Sphere *sphere2)
{
    float penetration = getPenetrationDistance(sphere1, sphere2);
    std::vector<float> normalized = getNormalizedVector(sphere1->getCenter(), sphere2->getCenter());

    penetration_t penetrationVector;
    penetrationVector.x = normalized[0] * penetration;
    penetrationVector.y = normalized[1] * penetration;
    penetrationVector.z = normalized[2] * penetration;

    return penetrationVector;
}

penetration_t
CollisionDetection::getPenetrationVector(const AABB *aabb, const Sphere *sphere)
{
    penetration_t penetrationVector;

    penetrationVector.x = (aabb->getXRadius() + sphere->getRadius())
                            - abs(aabb->getCenter().x - sphere->getCenter().x);

    penetrationVector.y = (aabb->getYRadius() + sphere->getRadius())
                            - abs(aabb->getCenter().y - sphere->getCenter().y);

    penetrationVector.z = (aabb->getZRadius() + sphere->getRadius())
                            - abs(aabb->getCenter().z - sphere->getCenter().z);

    return penetrationVector;
}

penetration_t
CollisionDetection::getPenetrationVector(const AABB *aabb, const Capsule *capsule)
{

    Point startingPoint = capsule->getStart();
    Point closestPoint = getClosestPoint(aabb, startingPoint);

    Point targetPoint;
    targetPoint.x = closestPoint.x + capsule->getRadius();
    targetPoint.y = closestPoint.y + capsule->getRadius();
    targetPoint.z = closestPoint.z + capsule->getRadius();

    penetration_t penetrationVector;
    penetrationVector.x = startingPoint.x - targetPoint.x;
    penetrationVector.y = startingPoint.y - targetPoint.y;
    penetrationVector.z = startingPoint.z - targetPoint.z;

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
CollisionDetection::isIntersection(const CollidableObject *obj1, const CollidableObject *obj2)
{
    if((typeid(AABB) == typeid(*obj1)) && (typeid(AABB) == typeid(*obj2)))
    {
        return isIntersection(dynamic_cast<const AABB*>(obj1), dynamic_cast<const AABB*>(obj2));
    }
    else if((typeid(Sphere) == typeid(*obj1)) && (typeid(Sphere) == typeid(*obj2)))
    {
        return isIntersection(dynamic_cast<const Sphere*>(obj1), dynamic_cast<const Sphere*>(obj2));
    }
    else if((typeid(AABB) == typeid(*obj1)) && (typeid(Sphere) == typeid(*obj2)))
    {
        return isIntersection(dynamic_cast<const AABB*>(obj1), dynamic_cast<const Sphere*>(obj2));
    }
    else if((typeid(Sphere) == typeid(*obj1)) && (typeid(AABB) == typeid(*obj2)))
    {
        return isIntersection(dynamic_cast<const AABB*>(obj2), dynamic_cast<const Sphere*>(obj1));
    }
    else if((typeid(AABB) == typeid(*obj1)) && (typeid(Capsule) == typeid(*obj2)))
    {
        return isIntersection(dynamic_cast<const AABB*>(obj1), dynamic_cast<const Capsule*>(obj2));
    }
    else if((typeid(Capsule) == typeid(*obj1)) && (typeid(AABB) == typeid(*obj2)))
    {
        return isIntersection(dynamic_cast<const AABB*>(obj2), dynamic_cast<const Capsule*>(obj1));
    }
    else
    {
        return 0;
    }
}

int
CollisionDetection::isIntersection(const AABB *aabb1, const AABB *aabb2)
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
CollisionDetection::isIntersection(const Sphere *sphere1, const Sphere *sphere2)
{
    std::vector<float> diff_vector;
    diff_vector = getDiffVectorAbs(sphere1->getCenter(), sphere2->getCenter());

    colvec d = conv_to< colvec >::from(diff_vector);
    float dist_between_centers = dot(d, d);
    float radiusSum = sphere1->getRadius() + sphere2->getRadius();

    return dist_between_centers <= radiusSum * radiusSum;
}

int
CollisionDetection::isIntersection(const AABB *aabb, const Sphere *sphere)
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
CollisionDetection::isIntersection(const AABB *aabb, const Capsule *capsule)
{
/*
    CollidableObject *startSphere = new Sphere(capsule->getID(), capsule->getStart(),
                                        capsule->getRadius(), true);
    CollidableObject *endSphere = new Sphere(capsule->getID(), capsule->getEnd(),
                                        capsule->getRadius(), true);

    if(isIntersection(aabb, startSphere))
    {
        delete startSphere;
        delete endSphere;
        return 1;
    }
    if(isIntersection(aabb, endSphere))
    {
        delete startSphere;
        delete endSphere;
        return 1;
    }

    delete startSphere;
    delete endSphere;

*/

    float squaredDistance = getSquareDistanceBetweenLineAndVertex(capsule->getStart(), capsule->getEnd(),
                                aabb->getCenter());

    float xSum = aabb->getXRadius() + capsule->getRadius();
    float ySum = aabb->getYRadius() + capsule->getRadius();
    float zSum = aabb->getZRadius() + capsule->getRadius();

    if(squaredDistance < (xSum * xSum))
        return 1;
    if(squaredDistance < (ySum * ySum))
        return 1;
    if(squaredDistance < (zSum * zSum))
        return 1;

    return 0;
}

float
CollisionDetection::getSquareDistanceBetweenLineAndVertex(Point startPoint, Point endPoint, Point vertex)
{
    std::vector<float> ab = getDiffVector(endPoint, startPoint);
    std::vector<float> ac = getDiffVector(vertex, startPoint);
    std::vector<float> bc = getDiffVector(vertex, endPoint);

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

Point
CollisionDetection::getClosestPoint(const AABB *aabb, const Point vertex)
{
    Point retVal;

    float vX = vertex.x;
    if(vX < aabb->getMinX())
        vX = aabb->getMinX();

    if(vX > aabb->getMaxX())
        vX = aabb->getMaxX();

    retVal.x = vX;

    float vY = vertex.y;
    if(vY < aabb->getMinY())
        vY = aabb->getMinY();

    if(vY > aabb->getMaxY())
        vY = aabb->getMaxY();

    retVal.y = vY;

    float vZ = vertex.z;
    if(vZ < aabb->getMinZ())
        vZ = aabb->getMinZ();

    if(vZ > aabb->getMaxZ())
        vZ = aabb->getMaxZ();

    retVal.z = vZ;

    return retVal;
}
