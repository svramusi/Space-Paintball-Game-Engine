#include <stdlib.h>

#include "physicsengine.h"

using namespace std;

PhysicsEngine::PhysicsEngine()
{
	cd = new CollisionDetection();
}

PhysicsEngine::~PhysicsEngine()
{
	if(cd)
		delete cd;
}

void
PhysicsEngine::updateWorld()
{
	detectCollision* collidableObject;

	collidableObject = (detectCollision*)malloc(sizeof(detectCollision));
	collidableObject->collidableObjectID = 1;

	collisionDetection* collisions = cd->detect_collision(collidableObject);

	freeCollisions(collisions);
	free(collidableObject);
}

void
PhysicsEngine::freeCollisions(collisionDetection* collisions)
{
	collisionDetection* current;
	collisionDetection* next;

	current = collisions;

	while(current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}
