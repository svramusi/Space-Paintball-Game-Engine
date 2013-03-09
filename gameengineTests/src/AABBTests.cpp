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

    delete aabb1;
    delete aabb2;
}

void
AABBTest::testCollision(void)
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

    delete aabb1;
    delete aabb2;


    penetration_t penetrationVector;

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

    radii[0] = 1.0f;
    radii[1] = 1.0f;
    radii[2] = 1.0f;

    aabb2 = new AABB(2, point2, radii, true);

    CPPUNIT_ASSERT(1 == cd->isIntersection(aabb1, aabb2));

    penetrationVector = cd->getPenetrationVector(aabb1, aabb2);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, penetrationVector.x, 0.01);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, penetrationVector.y, 0.01);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, penetrationVector.z, 0.01);

    delete aabb1;
    delete aabb2;



    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    radii[0] = 1.0f;
    radii[1] = 1.0f;
    radii[2] = 1.0f;

    aabb1 = new AABB(1, point1, radii, true);

    point2.x = 1;
    point2.y = 1;
    point2.z = 0;

    radii[0] = 1.0f;
    radii[1] = 1.0f;
    radii[2] = 1.0f;

    aabb2 = new AABB(2, point2, radii, true);

    CPPUNIT_ASSERT(1 == cd->isIntersection(aabb1, aabb2));

    penetrationVector = cd->getPenetrationVector(aabb1, aabb2);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, penetrationVector.x, 0.01);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, penetrationVector.y, 0.01);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0f, penetrationVector.z, 0.01);

    delete aabb1;
    delete aabb2;
}
