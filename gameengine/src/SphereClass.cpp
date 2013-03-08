#include "SphereClass.h"

Sphere::Sphere(int ID, Point center, float _radius, int movable) : CollidableObject(ID, center, movable)
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
