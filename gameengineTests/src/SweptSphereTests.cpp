#include "SweptSphereTests.h"

#include <iostream>
using namespace std;

void SweptSphereTest::setUp(void)
{
    cd = new CollisionDetection();
}

void SweptSphereTest::tearDown(void)
{
    if(cd)
        delete cd;
}

void
SweptSphereTest::testDistanceBetweenLineAndVertex(void)
{

    Point startPoint;
    Point endPoint;
    Point vertex;

    startPoint.x = 0;
    startPoint.y = 0;
    startPoint.z = 0;

    endPoint.x = 10;
    endPoint.y = 0;
    endPoint.z = 0;

    vertex.x = 5;
    vertex.y = 0;
    vertex.z = 0;

    CPPUNIT_ASSERT(0 == cd->getDistanceBetweenLineAndVertex(startPoint, endPoint, vertex));


    startPoint.x = 0;
    startPoint.y = 0;
    startPoint.z = 0;

    endPoint.x = 10;
    endPoint.y = 0;
    endPoint.z = 0;

    vertex.x = 0;
    vertex.y = 5;
    vertex.z = 0;

    //Squared Distance!
    CPPUNIT_ASSERT(25 == cd->getDistanceBetweenLineAndVertex(startPoint, endPoint, vertex));
}

void
SweptSphereTest::testNoCollisionSphere(void)
{
    Point point1;
    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    sphere_t sphere;
    sphere.center = point1;
    sphere.radius = 1.0;


    Point startCenter;
    startCenter.x = 10;
    startCenter.y = 10;
    startCenter.z = 10;

    Point endCenter;
    endCenter.x = 20;
    endCenter.y = 20;
    endCenter.z = 20;

    capsule_t capsule;
    capsule.startCenter = startCenter;
    capsule.endCenter = endCenter;
    capsule.radius = 1.0;

    //CPPUNIT_ASSERT(0 == cd->isIntersection(sphere, capsule));
}

void
SweptSphereTest::testCollisionSphere(void)
{
    Point point1;
    point1.x = 15;
    point1.y = 15;
    point1.z = 15;

    sphere_t sphere;
    sphere.center = point1;
    sphere.radius = 1.0;


    Point startCenter;
    startCenter.x = 10;
    startCenter.y = 10;
    startCenter.z = 10;

    Point endCenter;
    endCenter.x = 20;
    endCenter.y = 20;
    endCenter.z = 20;

    capsule_t capsule;
    capsule.startCenter = startCenter;
    capsule.endCenter = endCenter;
    capsule.radius = 1.0;

    //CPPUNIT_ASSERT(1 == cd->isIntersection(sphere, capsule));
}
