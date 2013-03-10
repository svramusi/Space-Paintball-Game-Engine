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

    CPPUNIT_ASSERT(0 == cd->getSquareDistanceBetweenLineAndVertex(startPoint, endPoint, vertex));


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
    CPPUNIT_ASSERT(25 == cd->getSquareDistanceBetweenLineAndVertex(startPoint, endPoint, vertex));
}

void
SweptSphereTest::testClosestPoint(void)
{
    AABB *aabb;
    Sphere *sphere;

    float radii[3];

    Point point1;
    Point point2;

    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    radii[0] = 1.0f;
    radii[1] = 1.0f;
    radii[2] = 1.0f;

    aabb = new AABB(1, point1, radii, true);

    point2.x = 0;
    point2.y = 5;
    point2.z = 0;
    sphere = new Sphere(1, point2, 1.0f, true);

    Point closestPoint = cd->getClosestPoint(aabb, sphere->getCenter());

    CPPUNIT_ASSERT_EQUAL(0.0f, closestPoint.x);
    CPPUNIT_ASSERT_EQUAL(1.0f, closestPoint.y);
    CPPUNIT_ASSERT_EQUAL(0.0f, closestPoint.z);

    delete aabb;
    delete sphere;


    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    radii[0] = 1.0f;
    radii[1] = 1.0f;
    radii[2] = 1.0f;

    aabb = new AABB(1, point1, radii, true);

    point2.x = 5;
    point2.y = 5;
    point2.z = 0;
    sphere = new Sphere(1, point2, 1.0f, true);

    closestPoint = cd->getClosestPoint(aabb, sphere->getCenter());

    CPPUNIT_ASSERT_EQUAL(1.0f, closestPoint.x);
    CPPUNIT_ASSERT_EQUAL(1.0f, closestPoint.y);
    CPPUNIT_ASSERT_EQUAL(0.0f, closestPoint.z);

    delete aabb;
    delete sphere;
}

void
SweptSphereTest::testNoCollisionAABB(void)
{
    CollidableObject *aabb;
    CollidableObject *capsule;

    float radii[3];

    Point point1;
    Point startCenter;
    Point endCenter;

    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    radii[0] = 1.0f;
    radii[1] = 1.0f;
    radii[2] = 1.0f;

    aabb = new AABB(1, point1, radii, true);

    startCenter.x = 10;
    startCenter.y = 10;
    startCenter.z = 10;

    endCenter.x = 20;
    endCenter.y = 20;
    endCenter.z = 20;

    capsule = new Capsule(1, startCenter, endCenter, 1.0f);

    CPPUNIT_ASSERT(0 == cd->isIntersection(aabb, capsule));

    delete aabb;
    delete capsule;


    //TOUCHING! NOT INTERSECTING!
    point1.x = 0;
    point1.y = 8;
    point1.z = 0;

    radii[0] = 1.0;
    radii[1] = 1.0f;
    radii[2] = 1.0;

    aabb = new AABB(1, point1, radii, true);

    startCenter.x = 0;
    startCenter.y = 10;
    startCenter.z = 0;

    endCenter.x = 0;
    endCenter.y = 25;
    endCenter.z = 0;

    capsule = new Capsule(1, startCenter, endCenter, 1.0f);

    CPPUNIT_ASSERT(0 == cd->isIntersection(aabb, capsule));

    delete aabb;
    delete capsule;
}

void
SweptSphereTest::testTipCollisionAABB(void)
{
    CollidableObject *aabb;
    CollidableObject *capsule;

    Point point1;
    point1.x = 0;
    point1.y = 15;
    point1.z = 0;

    float radii[3];
    radii[0] = 1.0f;
    radii[1] = 1.0f;
    radii[2] = 0.0f;

    aabb = new AABB(1, point1, radii, true);


    Point startCenter;
    startCenter.x = 0;
    startCenter.y = 15.5f;
    startCenter.z = 0;

    Point endCenter;
    endCenter.x = 0;
    endCenter.y = 20;
    endCenter.z = 0;

    capsule = new Capsule(1, startCenter, endCenter, 1.0f);

    CPPUNIT_ASSERT(1 == cd->isIntersection(aabb, capsule));

    delete aabb;
    delete capsule;
}

void
SweptSphereTest::testEndCollisionAABB(void)
{
    CollidableObject *aabb;
    CollidableObject *capsule;

    Point point1;
    point1.x = 0;
    point1.y = 15;
    point1.z = 0;

    float radii[3];
    radii[0] = 1.0f;
    radii[1] = 1.0f;
    radii[2] = 0.0f;

    aabb = new AABB(1, point1, radii, true);


    Point startCenter;
    startCenter.x = 0;
    startCenter.y = 10;
    startCenter.z = 0;

    Point endCenter;
    endCenter.x = 0;
    endCenter.y = 14.5f;
    endCenter.z = 0;

    capsule = new Capsule(1, startCenter, endCenter, 1.0f);

    CPPUNIT_ASSERT(1 == cd->isIntersection(aabb, capsule));

    delete aabb;
    delete capsule;
}

void
SweptSphereTest::testPassThroughCollisionAABB(void)
{
    CollidableObject *aabb;
    CollidableObject *capsule;

    Point point1;
    point1.x = 0;
    point1.y = 15;
    point1.z = 0;

    float radii[3];
    radii[0] = 1.0f;
    radii[1] = 1.0f;
    radii[2] = 0.0f;

    aabb = new AABB(1, point1, radii, true);


    //Fall down
    Point startCenter;
    startCenter.x = 0;
    startCenter.y = 20;
    startCenter.z = 0;

    Point endCenter;
    endCenter.x = 0;
    endCenter.y = 10;
    endCenter.z = 0;

    capsule = new Capsule(1, startCenter, endCenter, 1.0f);

    CPPUNIT_ASSERT(1 == cd->isIntersection(aabb, capsule));

    penetration_t penetrationVector = cd->getPenetrationVector(aabb, capsule);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0f, penetrationVector.x, 0.01);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0f, penetrationVector.y, 0.01);
    CPPUNIT_ASSERT_EQUAL(-1.0f, penetrationVector.z );


    delete aabb;
    delete capsule;
}
