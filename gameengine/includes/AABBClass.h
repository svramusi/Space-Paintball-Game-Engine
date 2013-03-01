#ifndef AABB_CLASS_H
#define AABB_CLASS_H

#include "CollidableObject.h"
#include "Point.h"

class AABB: public CollidableObject {
public:
    AABB(int ID, Point center, float radii[3]);
    ~AABB();

    float getXRadius() const;
    float getYRadius() const;
    float getZRadius() const;

private:
    float radiusX;
    float radiusY;
    float radiusZ;
};

#endif
