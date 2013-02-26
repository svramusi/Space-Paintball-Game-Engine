#ifndef COLLISION_TESTS_H
#define COLLISION_TESTS_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "AABB.h"
#include "Sphere.h"
#include "collisiondetection.h"

using namespace CppUnit;

class CollisionDetectionTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(CollisionDetectionTest);
    CPPUNIT_TEST(testNoCollision);
    CPPUNIT_TEST(testCollision);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void tearDown(void);

    void testNoCollision(void);
    void testCollision(void);

private:
    CollisionDetection *cd;
};

#endif
