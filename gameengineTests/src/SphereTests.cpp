#include "SphereTests.h"

void SphereTest::setUp(void)
{
	sphere = new Sphere();
}

void SphereTest::tearDown(void)
{
	if(sphere)
		delete sphere;
}

void
SphereTest::testNoCollision(void)
{
	newPoint point1(3);
	point1[0] = 0;
	point1[1] = 0;
	point1[2] = 0;

	sphere_t sphere1;
	sphere1.center = point1;
	sphere1.radius = 1.0;

	newPoint point2(3);
	point2[0] = 10;
	point2[1] = 10;
	point2[2] = 10;

	sphere_t sphere2;
	sphere2.center = point2;
	sphere2.radius = 1.0;

    CPPUNIT_ASSERT(0 == sphere->isIntersection(sphere1, sphere2));
}

void
SphereTest::testCollision(void)
{
	newPoint point1(3);
	point1[0] = 0;
	point1[1] = 0;
	point1[2] = 0;

	sphere_t sphere1;
	sphere1.center = point1;
	sphere1.radius = 1.0;

	newPoint point2(3);
	point2[0] = 1;
	point2[1] = 1;
	point2[2] = 1;

	sphere_t sphere2;
	sphere2.center = point2;
	sphere2.radius = 2.0;

    CPPUNIT_ASSERT(1 == sphere->isIntersection(sphere1, sphere2));
}
