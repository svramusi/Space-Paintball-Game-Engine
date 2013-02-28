#ifndef AABB_H
#define AABB_H

#include "Point.h"

struct aabb_t {
    int ID;
    Point center;
    float radii[3];
};

#endif
