
#include "Sphere.h"

using namespace std;
using namespace arma;

int Sphere::isIntersection(sphere_t sphere1, sphere_t sphere2)
{
	colvec d = conv_to< colvec >::from(sphere1.center);
	float dist2 = dot(d, d);

	float radiusSum = sphere1.radius + sphere2.radius;

	return dist2 <= radiusSum * radiusSum;
}
