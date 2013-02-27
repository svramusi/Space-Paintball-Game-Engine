#include "CollidableObject.h"

CollidableObject::CollidableObject(int _ID, Point center, float radii[3])
{
  ID = _ID;

  centerX = center.x;
  centerY = center.y;
  centerZ = center.z;

  radiusX = radii[0];
  radiusY = radii[1];
  radiusZ = radii[2];
}

int
CollidableObject::getID()
{
    return ID;
}

Point
CollidableObject::getCenter()
{
    Point center;
    center.x = centerX;
    center.y = centerY;
    center.z = centerZ;

    return center;
}

float
CollidableObject::getXRadius()
{
  return radiusX;
}

float
CollidableObject::getYRadius()
{
  return radiusY;
}

float
CollidableObject::getZRadius()
{
    return radiusZ;
}
