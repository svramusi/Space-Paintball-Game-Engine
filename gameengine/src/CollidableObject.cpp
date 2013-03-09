#include "CollidableObject.h"

CollidableObject::CollidableObject(int _ID, Point _center, int _movable)
{
    ID = _ID;
    center = _center;
    movable = _movable;
}

int
CollidableObject::getID() const
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

int
CollidableObject::isMovable()
{
    return movable;
}
