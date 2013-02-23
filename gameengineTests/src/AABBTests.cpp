#include "AABBTests.h"

void AABBTest::setUp(void)
{
    cd = new CollisionDetection();
}

void AABBTest::tearDown(void)
{
    if(cd)
        delete cd;
}

void
AABBTest::testNoCollision(void)
{
    Point point1;
    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    aabb_t aabb1;
    aabb1.center = point1;
    aabb1.radii[0] = 1.0;
    aabb1.radii[1] = 1.0;
    aabb1.radii[2] = 1.0;

    Point point2;
    point2.x = 10;
    point2.y = 10;
    point2.z = 10;

    aabb_t aabb2;
    aabb2.center = point2;
    aabb2.radii[0] = 1.0;
    aabb2.radii[1] = 1.0;
    aabb2.radii[2] = 1.0;

    CPPUNIT_ASSERT(0 == cd->isIntersection(aabb1, aabb2));
}

void
AABBTest::testCollision(void)
{
    Point point1;
    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    aabb_t aabb1;
    aabb1.center = point1;
    aabb1.radii[0] = 1.0;
    aabb1.radii[1] = 1.0;
    aabb1.radii[2] = 1.0;

    Point point2;
    point2.x = 1;
    point2.y = 1;
    point2.z = 1;

    aabb_t aabb2;
    aabb2.center = point2;
    aabb2.radii[0] = 2.0;
    aabb2.radii[1] = 2.0;
    aabb2.radii[2] = 2.0;

    CPPUNIT_ASSERT(1 == cd->isIntersection(aabb1, aabb2));
}
