#ifndef COLLIDABLE_OBJECT_CLASS_H
#define COLLIDABLE_OBJECT_CLASS_H

#include "Point.h"

class CollidableObject {
public:
    CollidableObject(int _ID, Point _center);
    virtual ~CollidableObject() {};

    int getID();
    void setID(int _ID);

    Point getCenter() const;
    void setCenter(Point newCenter);

private:
    int ID;
    Point center;
};

#endif
