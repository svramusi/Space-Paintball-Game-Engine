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
    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    aabb_t aabb;
    aabb.center = point1;
    aabb.radii[0] = 1.0;
    aabb.radii[1] = 1.0;
    aabb.radii[2] = 1.0;

    Point point2;
    point2.x = 10;
    point2.y = 10;
    point2.z = 10;

    sphere_t sphere;
    sphere.center = point2;
    sphere.radius = 1.0;

    CPPUNIT_ASSERT(0 == cd->isIntersection(aabb, sphere));
}

void
AABBSphereTest::testCollision(void)
{
    Point point1;
    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    aabb_t aabb;
    aabb.center = point1;
    aabb.radii[0] = 1.0;
    aabb.radii[1] = 1.0;
    aabb.radii[2] = 1.0;

    Point point2;
    point2.x = 2;
    point2.y = 2;
    point2.z = 2;

    sphere_t sphere;
    sphere.center = point2;
    sphere.radius = 1.0;

    CPPUNIT_ASSERT(1 == cd->isIntersection(aabb, sphere));
}
