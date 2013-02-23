#include <stdlib.h>
#include <stdio.h>

#include "collisiondetection.h"

using namespace std;
using namespace arma;

CollisionDetection::CollisionDetection()
{
}

CollisionDetection::~CollisionDetection()
{
}

collisionDetection*
CollisionDetection::detect_collision(detectCollision* collidableObject)
{
	collisionDetection *cd;
	cd = (collisionDetection*)malloc(sizeof(collisionDetection));

	cd->prev = NULL;
	cd->next = NULL;
	cd->objectID = 0;
	cd->collisionID = 0;

	//detect collisions
	printf("collidable object id: %i\n",collidableObject->collidableObjectID);

	return cd;
}

int
CollisionDetection::isIntersection(aabb_t aabb1, aabb_t aabb2)
{

	if(abs(aabb1.center.x - aabb2.center.x) > (aabb1.radii[0] + aabb2.radii[0]))
		return 0;

	if(abs(aabb1.center.y - aabb2.center.y) > (aabb1.radii[1] + aabb2.radii[1]))
		return 0;

	if(abs(aabb1.center.z - aabb2.center.z) > (aabb1.radii[2] + aabb2.radii[2]))
		return 0;

	return 1;
}

int
CollisionDetection::isIntersection(sphere_t sphere1, sphere_t sphere2)
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
