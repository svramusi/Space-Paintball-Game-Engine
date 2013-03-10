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


float
AABB::getMinX() const
{
    return  getCenter().x - getXRadius();
}

float
AABB::getMinY() const
{
    return  getCenter().y - getYRadius();
}

float
AABB::getMinZ() const
{
    return  getCenter().z - getZRadius();
}


float
AABB::getMaxX() const
{
    return  getCenter().x + getXRadius();
}

float
AABB::getMaxY() const
{
    return  getCenter().y + getYRadius();
}

float
AABB::getMaxZ() const
{
    return  getCenter().z + getZRadius();
}
