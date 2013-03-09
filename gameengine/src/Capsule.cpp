#include "Capsule.h"

Capsule::Capsule(int ID, Point _startCenter, Point _endCenter, float _radius) : CollidableObject(ID, startCenter, false)
{
    startCenter = _startCenter;
    endCenter = _endCenter;
    radius = _radius;
}

Capsule::~Capsule()
{
}

Point
Capsule::getStart() const
{
    return startCenter;
}

Point
Capsule::getEnd() const
{
    return endCenter;
}

float
Capsule::getRadius() const
{
    return radius;
}
