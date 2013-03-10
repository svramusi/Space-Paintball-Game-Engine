#ifndef CAPSULE_CLASS_H
#define CAPSULE_CLASS_H

#include "CollidableObject.h"

class Capsule : public CollidableObject {
public:
    Capsule(int ID, Point _startCenter, Point _endCenter, float _radius);
    ~Capsule();

    Point getStart() const;
    Point getEnd() const;
    float getRadius() const;

private:
    Point startCenter;
    Point endCenter;
    float radius;
};

#endif
