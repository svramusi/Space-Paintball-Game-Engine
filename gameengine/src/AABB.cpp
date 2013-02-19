
#include "AABB.h"

using namespace std;

int AABB::isIntersection(aabb_t aabb1, aabb_t aabb2)
{

	if(abs(aabb1.center.x - aabb2.center.x) > (aabb1.radii[0] + aabb2.radii[0]))
		return 0;

	if(abs(aabb1.center.y - aabb2.center.y) > (aabb1.radii[1] + aabb2.radii[1]))
		return 0;

	if(abs(aabb1.center.z - aabb2.center.z) > (aabb1.radii[2] + aabb2.radii[2]))
		return 0;

	return 1;
}
