#include "SphereTests.h"

void SphereTest::setUp(void)
{
    cd = new CollisionDetection();
}

void SphereTest::tearDown(void)
{
    if(cd)
        delete cd;
}

void
SphereTest::testNoCollision(void)
{
	Point point1;
	point1.x = 0;
	point1.y = 0;
	point1.z = 0;

	sphere_t sphere1;
	sphere1.center = point1;
	sphere1.radius = 1.0;

	Point point2;
	point2.x = 10;
	point2.y = 10;
	point2.z = 10;

	sphere_t sphere2;
	sphere2.center = point2;
	sphere2.radius = 1.0;

    CPPUNIT_ASSERT(0 == cd->isIntersection(sphere1, sphere2));
}

void
SphereTest::testCollision(void)
{
	Point point1;
	point1.x = 0;
	point1.y = 0;
	point1.z = 0;

	sphere_t sphere1;
	sphere1.center = point1;
	sphere1.radius = 1.0;

	Point point2;
	point2.x = 1;
	point2.y = 1;
	point2.z = 1;

	sphere_t sphere2;
	sphere2.center = point2;
	sphere2.radius = 2.0;

    	CPPUNIT_ASSERT(1 == cd->isIntersection(sphere1, sphere2));

	point1.x = 0;
	point1.y = 0;
	point1.z = 0;

	sphere1.center = point1;
	sphere1.radius = 1.0;

	point2.x = 1;
	point2.y = 1;
	point2.z = 1;

	sphere2.center = point2;
	sphere2.radius = 1.0;

    	CPPUNIT_ASSERT(1 == cd->isIntersection(sphere1, sphere2));
}
void
SphereTest::testVeryCloseCollision(void)
{
	Point point1;
	point1.x = 0;
	point1.y = 0;
	point1.z = 0;

	sphere_t sphere1;
	sphere1.center = point1;
	sphere1.radius = 1.0;

	Point point2;
	point2.x = 2;
	point2.y = 2;
	point2.z = 2;

	sphere_t sphere2;
	sphere2.center = point2;
	sphere2.radius = 2.44;

    	CPPUNIT_ASSERT(0 == cd->isIntersection(sphere1, sphere2));

	point1.x = 0;
	point1.y = 0;
	point1.z = 0;

	sphere1.center = point1;
	sphere1.radius = 1.0;

	point2.x = 2;
	point2.y = 2;
	point2.z = 2;

	sphere2.center = point2;
	sphere2.radius = 2.464101615;

    	CPPUNIT_ASSERT(1 == cd->isIntersection(sphere1, sphere2));


	point1.x = 0;
	point1.y = 0;
	point1.z = 0;

	sphere1.center = point1;
	sphere1.radius = 1.0;

	point2.x = 2;
	point2.y = 2;
	point2.z = 2;

	sphere2.center = point2;
	sphere2.radius = 2.47;

    	CPPUNIT_ASSERT(1 == cd->isIntersection(sphere1, sphere2));
}
