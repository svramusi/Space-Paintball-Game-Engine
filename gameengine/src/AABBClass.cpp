#include "AABBClass.h"

AABB::AABB(int ID, Point center, float radii[3]) : CollidableObject(ID, center, radii)
{
}

AABB::~AABB()
{
}
