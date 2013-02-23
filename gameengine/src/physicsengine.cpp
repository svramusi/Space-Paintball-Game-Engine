#include <stdlib.h>

#include "physicsengine.h"


using namespace std;

PhysicsEngine::PhysicsEngine()
{
	cd = new CollisionDetection();
	//physicObjects = new vector<physicInfo*>();
	SetWorldParams(9.81, 1.225);  //defaults to earth
}
PhysicsEngine::PhysicsEngine(float grav, float air)
{
	cd = new CollisionDetection();
	//physicObjects = new vector<physicInfo*>();
	SetWorldParams(grav,air);
}

PhysicsEngine::~PhysicsEngine()
{
	if(cd)
		delete cd;
}

void PhysicsEngine::SetWorldParams(float grav, float air)
{
	gravity =grav;
	airfriction= air;
}

void
PhysicsEngine::updateWorld()
{
	/*detectCollision* collidableObject;

	collidableObject = (detectCollision*)malloc(sizeof(detectCollision));
	collidableObject->collidableObjectID = 1;

	collisionDetection* collisions = cd->detect_collision(collidableObject);

	freeCollisions(collisions);
	free(collidableObject);*/
}

void
PhysicsEngine::freeCollisions(collisionDetection* collisions)
{
/*	collisionDetection* current;
	collisionDetection* next;

	current = collisions;

	while(current != NULL)
	{
		//next = current->next;
		free(current);
		current = next;
	}*/
}


void calculateCenterOfMass()
{
	//totalcm = sum(mass(part) * center(part)/sum(mass(total)))

}

void calculateSpeed()
{
	//speed = initspeed + acc*t
	// using verlet integration
	//v(t2) = pos(t2) - pos(t1)/change in time
}

void calculateAcceleration()
{
	//acc= force/mass
}

void calculateAngularVelocity()
{
	//w(t2) = w(t1) + N(t1)/i * change in time

}

void calculateAngularPosition()
{
	//O(t2) = O(t1) + vel(t1)*change im time
}
//see slide 44 for sums of angular forces

void calculatePosition()
{
	// pos = initpos + v*t basic formula
	// using verlet integration
	//pos(2) = 2*pos - pos(curtime - change in time) + (Force(t1)/mass)*(change in time)^2
}

void solveCollisionEquation()
{
  ;//see slide 58-63
}
void insertPhysicsObject() //add objects to init items
{

}
void removePhysicsObject(physicsInfo id)
{

}

 void updatePhysics(int ms)
{
     //list of collisions needed
	 //for each object
	    //update all params
	 //apply gravity
	 //apply friction (wind resistance)
	 //update linear vel and acc
	 //update and vel and acc
	 //update position of all objects
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
