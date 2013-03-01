#include "CollidableObject.h"

CollidableObject::CollidableObject(int _ID, Point _center, float radii[3])
{
    ID = _ID;

    center = _center;
    radiusX = radii[0];
    radiusY = radii[1];
    radiusZ = radii[2];
}

int
CollidableObject::getID()
{
    return ID;
}

void
CollidableObject::setID(int _ID)
{
    ID = _ID;
}

Point
CollidableObject::getCenter() const
{
    return center;
}

void
CollidableObject::setCenter(Point newCenter)
{
    center = newCenter;
}

float
CollidableObject::getXRadius() const
{
  return radiusX;
}

float
CollidableObject::getYRadius() const
{
  return radiusY;
}

float
CollidableObject::getZRadius() const
{
    return radiusZ;
}
