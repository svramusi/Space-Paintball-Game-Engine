#ifndef AABB_CLASS_H
#define AABB_CLASS_H

#include "CollidableObject.h"
#include "Point.h"

class AABB: public CollidableObject {
public:
    AABB(int ID, Point center, float radii[3], int movable);
    ~AABB();

    float getXRadius() const;
    float getYRadius() const;
    float getZRadius() const;

    float getMinX() const;
    float getMinY() const;
    float getMinZ() const;

    float getMaxX() const;
    float getMaxY() const;
    float getMaxZ() const;

private:
    float radiusX;
    float radiusY;
    float radiusZ;
};

#endif
