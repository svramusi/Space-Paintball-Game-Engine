#ifndef SPHERE_TESTS_H
#define SPHERE_TESTS_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "SphereClass.h"
#include "collisiondetection.h"

using namespace CppUnit;

class SphereTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(SphereTest);
    CPPUNIT_TEST(testNoCollision);
    CPPUNIT_TEST(testCollision);
    CPPUNIT_TEST(testVeryCloseCollision);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void tearDown(void);

    void testNoCollision(void);
    void testCollision(void);
    void testVeryCloseCollision(void);

private:
    CollisionDetection *cd;
};

#endif
