#include "SphereClass.h"

Sphere::Sphere(int ID, Point center, float _radius) : CollidableObject(ID, center)
{
    radius = _radius;
}

Sphere::~Sphere()
{
}

float
Sphere::getRadius() const
{
    return radius;
}
