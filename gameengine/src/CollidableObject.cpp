#include "CollidableObject.h"

CollidableObject::CollidableObject(int _ID, Point center, float radii[3])
{
  ID = _ID;

  centerX = center.X;
  centerY = center.Y;
  centerZ = center.Z;

  radiusX = radii[0];
  radiusY = radii[1];
  radiusZ = radii[2];
}

int
CollidableObject::GetID()
{
    return ID;
}

Point
CollidableObject::GetCenter()
{
    Point center;
    center.x = centerX;
    center.y = centerY;
    center.z = centerZ;

    return center;
}

float
CollidableObject::GetXRadius()
{
  return radiusX;
}

float
CollidableObject::GetYRadius()
{
  return radiusY;
}

float
CollidableObject::GetZRadius()
{
    return radiusZ;
}
