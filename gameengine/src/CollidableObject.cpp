#include "CollidableObject.h"

CollidableObject::CollidableObject(int _ID, Point _center)
{
    ID = _ID;
    center = _center;
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
