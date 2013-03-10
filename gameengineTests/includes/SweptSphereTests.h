#ifndef SWEPT_SPHERE_TESTS_H
#define SWEPT_SPHERE_TESTS_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Sphere.h"
#include "AABB.h"
#include "Capsule.h"
#include "collisiondetection.h"

using namespace CppUnit;

class SweptSphereTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(SweptSphereTest);
    CPPUNIT_TEST(testDistanceBetweenLineAndVertex);
    CPPUNIT_TEST(testNoCollisionAABB);
    CPPUNIT_TEST(testTipCollisionAABB);
    CPPUNIT_TEST(testEndCollisionAABB);
    CPPUNIT_TEST(testPassThroughCollisionAABB);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void tearDown(void);

    void testDistanceBetweenLineAndVertex(void);
    void testNoCollisionAABB(void);
    void testTipCollisionAABB(void);
    void testEndCollisionAABB(void);
    void testPassThroughCollisionAABB(void);

private:
    CollisionDetection *cd;
};

#endif
