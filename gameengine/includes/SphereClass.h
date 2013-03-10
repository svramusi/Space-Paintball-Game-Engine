#ifndef SPHERE_CLASS_H
#define SPHERE_CLASS_H

#include "CollidableObject.h"

class Sphere: public CollidableObject {
public:
    Sphere(int ID, Point center, float radius, int movable);
    ~Sphere();

    float getRadius() const;

private:
    float radius;
};

#endif
