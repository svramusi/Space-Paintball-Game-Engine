#include "SphereTests.h"

#include <armadillo>

using namespace arma;

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
    float radii[3];
    Sphere *sphere1;
    Sphere *sphere2;

    Point point1;
    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    radii[0] = 1.0;
    radii[1] = 1.0;
    radii[2] = 1.0;
    sphere1 = new Sphere(1, point1, radii);

    Point point2;
    point2.x = 10;
    point2.y = 10;
    point2.z = 10;

    radii[0] = 1.0;
    radii[1] = 1.0;
    radii[2] = 1.0;
    sphere2 = new Sphere(2, point2, radii);

    CPPUNIT_ASSERT(0 == cd->isIntersection(sphere1, sphere2));

    delete sphere1;
    delete sphere2;
}

void
SphereTest::testCollision(void)
{
    float radii[3];
    Sphere *sphere1;
    Sphere *sphere2;

    Point point1;
    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    radii[0] = 1.0;
    radii[1] = 1.0;
    radii[2] = 1.0;
    sphere1 = new Sphere(1, point1, radii);

    Point point2;
    point2.x = 1;
    point2.y = 1;
    point2.z = 1;

    radii[0] = 2.0;
    radii[1] = 2.0;
    radii[2] = 2.0;
    sphere2 = new Sphere(2, point2, radii);

    CPPUNIT_ASSERT(1 == cd->isIntersection(sphere1, sphere2));


    delete sphere1;
    delete sphere2;


    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    radii[0] = 1.0;
    radii[1] = 1.0;
    radii[2] = 1.0;
    sphere1 = new Sphere(1, point1, radii);

    point2.x = 1;
    point2.y = 1;
    point2.z = 0;

    radii[0] = 2.0;
    radii[1] = 2.0;
    radii[2] = 2.0;
    sphere2 = new Sphere(2, point2, radii);

    CPPUNIT_ASSERT(1 == cd->isIntersection(sphere1, sphere2));


    std::vector<float> diff_vector = cd->getDiffVector(sphere1->getCenter(), sphere2->getCenter());

    colvec d = conv_to< colvec >::from(diff_vector);
    float dist_between_centers = dot(d, d);
    float radiusSum = sphere1->getRadius() + sphere2->getRadius();


    float p = cd->getPenetrationDistance(dist_between_centers, radiusSum);
    CPPUNIT_ASSERT_EQUAL( -1.0f, p );


    std::vector<float> normalized = cd->getNormalizedVector(sphere1->getCenter(), sphere2->getCenter());
    CPPUNIT_ASSERT_EQUAL( -1.0f, normalized[0] );
    CPPUNIT_ASSERT_EQUAL( -1.0f, normalized[1] );
    CPPUNIT_ASSERT_EQUAL( 0.0f, normalized[2] );

    std::vector<float> penetrationVector = cd->getPenetrationVector(sphere1, sphere2);
    CPPUNIT_ASSERT_EQUAL( 1.0f, penetrationVector[0] );
    CPPUNIT_ASSERT_EQUAL( 1.0f, penetrationVector[1] );
    CPPUNIT_ASSERT_EQUAL( 0.0f, penetrationVector[2] );

    delete sphere1;
    delete sphere2;




    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    radii[0] = 1.0;
    radii[1] = 1.0;
    radii[2] = 1.0;
    sphere1 = new Sphere(1, point1, radii);

    point2.x = 1;
    point2.y = 1;
    point2.z = 1;

    radii[0] = 1.0;
    radii[1] = 1.0;
    radii[2] = 1.0;
    sphere2 = new Sphere(2, point2, radii);

    CPPUNIT_ASSERT(1 == cd->isIntersection(sphere1, sphere2));

    delete sphere1;
    delete sphere2;
}
void
SphereTest::testVeryCloseCollision(void)
{
    float radii[3];

    Sphere *sphere1;
    Sphere *sphere2;

    Point point1;
    Point point2;


    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    radii[0] = 1.0;
    radii[1] = 1.0;
    radii[2] = 1.0;
    sphere1 = new Sphere(1, point1, radii);

    point2.x = 2;
    point2.y = 2;
    point2.z = 2;

    radii[0] = 2.44;
    radii[1] = 2.44;
    radii[2] = 2.44;
    sphere2 = new Sphere(2, point2, radii);

    CPPUNIT_ASSERT(0 == cd->isIntersection(sphere1, sphere2));

    delete sphere1;
    delete sphere2;


    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    radii[0] = 1.0;
    radii[1] = 1.0;
    radii[2] = 1.0;
    sphere1 = new Sphere(1, point1, radii);

    point2.x = 2;
    point2.y = 2;
    point2.z = 2;

    radii[0] = 2.464101615;
    radii[1] = 2.464101615;
    radii[2] = 2.464101615;
    sphere2 = new Sphere(2, point2, radii);

    CPPUNIT_ASSERT(1 == cd->isIntersection(sphere1, sphere2));

    delete sphere1;
    delete sphere2;


    point1.x = 0;
    point1.y = 0;
    point1.z = 0;

    radii[0] = 1.0;
    radii[1] = 1.0;
    radii[2] = 1.0;
    sphere1 = new Sphere(1, point1, radii);

    point2.x = 2;
    point2.y = 2;
    point2.z = 2;

    radii[0] = 2.47;
    radii[1] = 2.47;
    radii[2] = 2.47;
    sphere2 = new Sphere(2, point2, radii);

    CPPUNIT_ASSERT(1 == cd->isIntersection(sphere1, sphere2));

    delete sphere1;
    delete sphere2;
}
