#ifndef COLLIDABLE_OBJECT_CLASS_H
#define COLLIDABLE_OBJECT_CLASS_H

#include "Point.h"

class CollidableObject {
public:
    CollidableObject(int _ID, Point _center, int movable);
    virtual ~CollidableObject() {};

    int getID() const;
    void setID(int _ID);

    Point getCenter() const;
    void setCenter(Point newCenter);

    int isMovable();

private:
    int ID;
    Point center;
    int movable;
};

#endif
