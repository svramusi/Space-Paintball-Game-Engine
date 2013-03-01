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

    AABB *aabb = new AABB(1, point1, radii);

    point2.x = 10;
    point2.y = 10;
    point2.z = 10;


    Sphere *sphere = new Sphere(2, point2, 1.0f);

    CPPUNIT_ASSERT(0 == cd->isIntersection(aabb, sphere));

    delete aabb;
    delete sphere;
}

void
AABBSphereTest::testCollision(void)
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

    AABB *aabb = new AABB(1, point1, radii);

    point2.x = 2;
    point2.y = 2;
    point2.z = 2;

    Sphere *sphere = new Sphere(2, point2, 1.0f);

    CPPUNIT_ASSERT(1 == cd->isIntersection(aabb, sphere));

    delete aabb;
    delete sphere;
}
