#ifndef CAPSULE_H
#define CAPSULE_H

#include "Point.h"

struct capsule_t {
    Point startCenter;
    Point endCenter;
    float radius;
};

#endif
