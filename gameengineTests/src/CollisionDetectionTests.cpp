#include "CollisionDetectionTests.h"

void CollisionDetectionTest::setUp(void)
{
    cd = new CollisionDetection();
}

void CollisionDetectionTest::tearDown(void)
{
    if(cd)
        delete cd;
}

void
CollisionDetectionTest::testNoCollision(void)
{
    CollidableObject *aabb1;
    CollidableObject *aabb2;

    float radii[3];

    Point point1;
    Point point2;

    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    radii[0] = 1.0f;
    radii[1] = 1.0f;
    radii[2] = 1.0f;

    aabb1 = new AABB(1, point1, radii, true);

    point2.x = 10;
    point2.y = 10;
    point2.z = 10;

    radii[0] = 1.0f;
    radii[1] = 1.0f;
    radii[2] = 1.0f;

    aabb2 = new AABB(2, point2, radii, true);

    CPPUNIT_ASSERT(0 == cd->isIntersection(aabb1, aabb2));

    cd->addObject(aabb1);
    cd->addObject(aabb2);

    collisions_t *collisions = cd->checkForAnyCollisions();
    CPPUNIT_ASSERT(NULL == collisions);

    cd->freeCollisions(collisions);

    delete aabb1;
    delete aabb2;
}

void
CollisionDetectionTest::testCollision(void)
{
    CollidableObject *aabb1;
    CollidableObject *aabb2;

    float radii[3];

    Point point1;
    Point point2;

    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    radii[0] = 1.0f;
    radii[1] = 1.0f;
    radii[2] = 1.0f;

    aabb1 = new AABB(1, point1, radii, true);

    point2.x = 1;
    point2.y = 1;
    point2.z = 1;

    radii[0] = 2.0f;
    radii[1] = 2.0f;
    radii[2] = 2.0f;

    aabb2 = new AABB(2, point2, radii, true);

    CPPUNIT_ASSERT(1 == cd->isIntersection(aabb1, aabb2));

    cd->addObject(aabb1);
    cd->addObject(aabb2);

    collisions_t *collisions = cd->checkForAnyCollisions();
    CPPUNIT_ASSERT(NULL != collisions);

    CPPUNIT_ASSERT_EQUAL(1, collisions->ID);
    CPPUNIT_ASSERT_EQUAL(2, collisions->info->ID);

    cd->freeCollisions(collisions);

    delete aabb1;
    delete aabb2;
}
