#ifndef SPHERE_H
#define SPHERE_H


#include <armadillo>
#include <cmath>

typedef std::vector<float> newPoint;

struct sphere_t {
	newPoint center;
	float radius;
};

class Sphere {
public:
    int isIntersection(sphere_t sphere1, sphere_t sphere2);

private:

};

#endif
