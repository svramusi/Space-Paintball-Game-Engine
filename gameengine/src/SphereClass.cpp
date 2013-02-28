#include "SphereClass.h"

Sphere::Sphere(int ID, Point center, float radii[3]) : CollidableObject(ID, center, radii)
{
}

Sphere::~Sphere()
{
}

float
Sphere::getRadius()
{
    return getXRadius();
}
