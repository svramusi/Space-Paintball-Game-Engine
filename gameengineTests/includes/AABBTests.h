#ifndef AABB_TESTS_H
#define AABB_TESTS_H


#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "AABB.h"

using namespace CppUnit;


class AABBTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(AABBTest);
	CPPUNIT_TEST(testNoCollision);
	CPPUNIT_TEST(testCollision);
	CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void tearDown(void);

    void testNoCollision(void);
    void testCollision(void);

private:
    AABB *aabb;
};

#endif
