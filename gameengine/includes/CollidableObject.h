#ifndef COLLIDABLE_OBJECT_CLASS_H
#define COLLIDABLE_OBJECT_CLASS_H

#include "Point.h"

class CollidableObject {
public:
    CollidableObject(int _ID, Point _center, float radii[3]);
    virtual ~CollidableObject() {};

    int getID();
    void setID(int _ID);

    Point getCenter() const;
    void setCenter(Point newCenter);

    float getXRadius() const;
    float getYRadius() const;
    float getZRadius() const;

private:
    int ID;

    Point center;

    float radiusX;
    float radiusY;
    float radiusZ;
};

#endif
