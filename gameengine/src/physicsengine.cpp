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
	collisionDetection* prev;
	collisionDetection* current;

	current = collisions;

	//Go to the end of the list of collisions
	while(current->next != NULL)
	{
		current = current->next;
	}

	//Need to delete from the bottom up
	do
	{
		prev = current->prev;
		free(current);
		current = prev;
	} while(current != NULL);
	//My first ever do while loop!!
}
