#ifndef SPHERE_H
#define SPHERE_H


#include "Point.h"
#include <armadillo>
#include <cmath>

struct sphere_t {
	Point center;
	float radius;
};

class Sphere {
public:
    int isIntersection(sphere_t sphere1, sphere_t sphere2);

private:

};

#endif
