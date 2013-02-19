#ifndef AABB_H
#define AABB_H

#include "Point.h"

#include <cmath>

struct aabb_t {
	Point center;
	float radii[3];
};

class AABB {
public:
    int isIntersection(aabb_t aabb1, aabb_t aabb2);

private:

};

#endif
