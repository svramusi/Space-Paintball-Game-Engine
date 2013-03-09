#include "AABBSphereTests.h"

void AABBSphereTest::setUp(void)
{
    cd = new CollisionDetection();
}

void AABBSphereTest::tearDown(void)
{
    if(cd)
        delete cd;
}

void
AABBSphereTest::testNoCollision(void)
{
    Point point1;
    Point point2;

    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    float radii[3];
    radii[0] = 1.0f;
    radii[1] = 1.0f;
    radii[2] = 1.0f;

    AABB *aabb = new AABB(1, point1, radii, true);

    point2.x = 10;
    point2.y = 10;
    point2.z = 10;


    Sphere *sphere = new Sphere(2, point2, 1.0f, true);

    CPPUNIT_ASSERT(0 == cd->isIntersection(aabb, sphere));

    delete aabb;
    delete sphere;
}

void
AABBSphereTest::testCollision(void)
{
    CollidableObject *aabb;
    CollidableObject *sphere;

    Point point1;
    Point point2;
    float radii[3];

    penetration_t penetrationVector;

    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    radii[0] = 1.0f;
    radii[1] = 1.0f;
    radii[2] = 1.0f;

    aabb = new AABB(1, point1, radii, true);

    point2.x = 1;
    point2.y = 1;
    point2.z = 1;

    sphere = new Sphere(2, point2, 1.0f, true);

    CPPUNIT_ASSERT(1 == cd->isIntersection(aabb, sphere));

    penetrationVector = cd->getPenetrationVector(aabb, sphere);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0f, penetrationVector.x, 0.01);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0f, penetrationVector.y, 0.01);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0f, penetrationVector.z, 0.01);

    delete aabb;
    delete sphere;



    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    radii[0] = 1.0f;
    radii[1] = 1.0f;
    radii[2] = 1.0f;

    aabb = new AABB(1, point1, radii, true);

    point2.x = 1;
    point2.y = 1;
    point2.z = 0;

    sphere = new Sphere(2, point2, 1.0f, true);

    CPPUNIT_ASSERT(1 == cd->isIntersection(aabb, sphere));

    penetrationVector = cd->getPenetrationVector(aabb, sphere);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0f, penetrationVector.x, 0.01);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0f, penetrationVector.y, 0.01);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-2.0f, penetrationVector.z, 0.01);

    delete aabb;
    delete sphere;
}
