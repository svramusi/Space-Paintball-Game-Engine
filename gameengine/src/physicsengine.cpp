#include <stdlib.h>

#include "physicsengine.h"

using namespace std;

PhysicsEngine::PhysicsEngine()
{
	cd = new CollisionDetection();
}
PhysicsEngine::PhysicsEngine(float grav, float air)
{
	cd = new CollisionDetection();
	SetWorldParams(grav,air);
}

PhysicsEngine::~PhysicsEngine()
{
	if(cd)
		delete cd;
}

int
PhysicsEngine::SetWorldParams(float grav, float air)
{
	gravity =grav;
	airfriction= air;

    return 0;
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

physicsInfo insertPhysicsObject(aabb_t *obj, float m, Velocity linVel, Force linAcc, Velocity angVel, Force angAcc)
{
	physicsInfo newItem;
	newItem.aabbObject = obj;
	newItem.sphereObject = NULL;
	newItem.mass = m;
	newItem.linearVelocity =linVel;
	newItem.linearAcceleration = linAcc;
	newItem.angularVelocity = angVel;
	newItem.angularAcceleration = angAcc;
	physicsObjects.push_back(*newItem);
}

physicsInfo insertPhysicsObject(sphere_t *obj, float m, Velocity linVel, Force linAcc, Velocity angVel, Force angAcc)
{
	physicsInfo newItem;
	newItem.aabbObject = NULL;
	newItem.sphereObject = obj;
	newItem.mass = m;
	newItem.linearVelocity =linVel;
	newItem.linearAcceleration = linAcc;
	newItem.angularVelocity = angVel;
	newItem.angularAcceleration = angAcc;
	physicsObjects.push_back(*newItem);
}
// combined formula pos = initpos + intvel*t + 1/2 acc *t^2
/*•  You will need:
•  Constructor: initializes an empty “physics world”
•  Set gravity
•  Add objects:
•  Shape, position, rotation, mass, moment of inertia, linear and angular
velocities
•  Remove objects
•  Simulate one step:
•  1) Add up all the forces that act on each object
•  2) Run numerical integration (e.g. Explicit Euler)
•  3) Resolve collisions
•  4) Resolve constraints*/
