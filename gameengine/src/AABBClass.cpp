#include "AABBClass.h"

AABB::AABB(int ID, Point center, float radii[3], int movable) : CollidableObject(ID, center, movable)
{
    radiusX = radii[0];
    radiusY = radii[1];
    radiusZ = radii[2];
}

AABB::~AABB()
{
}

float
AABB::getXRadius() const
{
    return radiusX;
}

float
AABB::getYRadius() const
{
    return radiusY;
}

float
AABB::getZRadius() const
{
    return radiusZ;
}
