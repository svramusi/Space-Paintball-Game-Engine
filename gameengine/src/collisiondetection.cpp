#include <stdlib.h>
#include <stdio.h>

#include "collisiondetection.h"

using namespace std;

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
