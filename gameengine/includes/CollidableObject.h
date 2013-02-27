#ifndef COLLIDABLE_OBJECT_CLASS_H
#define COLLIDABLE_OBJECT_CLASS_H

#include "Point.h"

class CollidableObject {
public:
    CollidableObject(int _ID, Point center, float radii[3]);
    virtual ~CollidableObject();

    int getID();

    Point getCenter();

    float getXRadius();
    float getYRadius();
    float getZRadius();

private:
    int ID;

    float centerX;
    float centerY;
    float centerZ;

    float radiusX;
    float radiusY;
    float radiusZ;
};

#endif
