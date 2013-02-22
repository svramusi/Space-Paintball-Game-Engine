
#include "Sphere.h"

using namespace std;
using namespace arma;

int Sphere::isIntersection(sphere_t sphere1, sphere_t sphere2)
{
	typedef std::vector<float> float_vect;
	float_vect diff_vector(3);
	diff_vector[0] = sphere1.center.x - sphere2.center.x;
	diff_vector[1] = sphere1.center.y - sphere2.center.y;
	diff_vector[2] = sphere1.center.z - sphere2.center.z;

	colvec d = conv_to< colvec >::from(diff_vector);
	float dist_between_centers = dot(d, d);
	float radiusSum = sphere1.radius + sphere2.radius;

	return dist_between_centers <= radiusSum * radiusSum;
}
