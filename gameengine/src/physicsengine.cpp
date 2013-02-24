#include <stdlib.h>

#include "physicsengine.h"

using namespace std;

PhysicsEngine::PhysicsEngine()
{
	cd = new CollisionDetection();
	SetWorldParams(9.78,air);
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

void calculateAngularVelocity(physicsInfo &item, float deltaT)
{
	//ang velnew = and velcurr + ang acc *deltat
	Velocity newV;
	 Force accel;

			 accel.x = (item.angularForce.x/item.mass)*deltaT;
			 accel.y = (item.angularForce.y/item.mass)*deltaT;
			 accel.z = (item.angularForce.z/item.mass)*deltaT;

			 newV.x = item.angularVelocity.x + accel.x;
			 newV.y = item.angularVelocity.y + accel.y;
			 newV.z = item.angularVelocity.z + accel.z;
			 item.angularVelocity = newV;

}
void calculateLinearAcceleration(physicsInfo &item, float deltaT)
{
	//accel x = accel x - gravity*deltaT
	//accel y= accel y - wind *deltaT
	Force accel;
	accel.x = (item.linearForce.x/item.mass)+(gravity*deltaT);
	accel.y = (item.linearForce.y/item.mass)+(airfriction*deltaT);
	accel.z = (item.linearForce.z/item.mass); //no wind so no Z force

	item.linearForce.x = accel.x*item.mass;
	item.linearForce.y = accel.y*item.mass;
	item.linearForce.z = accel.z*item.mass;
}


void calculateLinearVelocity(physicsInfo &item, float deltaT)
{
	//Velocity new = vel cur + Acc * deltaT
	     Force accel;
	     Velocity newV;
		 accel.x = (item.linearForce.x/item.mass)*deltaT;
		 accel.y = (item.linearForce.y/item.mass)*deltaT;
		 accel.z = (item.linearForce.z/item.mass)*deltaT;

		 newV.x = item.linearVelocity.x + accel.x;
		 newV.y = item.linearVelocity.y + accel.y;
		 newV.z = item.linearVelocity.z + accel.z;
		 item.linearVelocity = newV;
}

 void calculatePosition(physicsInfo &item, float deltaT)
 {

		// using verlet integration
	 	 // postion of New = Position current + vel Cur* deltaT + acceleration (dt^2)
	 Point current;
	 if(item.aabbObject != NULL)
		  current =item.aabbObject->center;
	 else
		  current =item.sphereObject->center;
	 Point calcVel = item.linearVelocity;
	 Force accel;
	 Point newP;
	 float timeSqr = deltaT*deltaT;
	 calcVel.x = calcVel.x * deltaT;
	 calcVel.y =calcVel.y * deltaT;
	 calcVel.z = calcVel.z * deltaT;

	 accel.x = (item.linearForce.x/item.mass)*timeSqr;
	 accel.y = (item.linearForce.y/item.mass)*timeSqr;
	 accel.z = (item.linearForce.z/item.mass)*timeSqr;

	 newP.x = current.x + accel.x+ calcVel.x;
	 newP.y = current.y + accel.y+ calcVel.y;
	 newP.z = current.z + accel.z+ calcVel.z;

	 if(item.aabbObject != NULL)
	 {
	 		item.aabbObject->center.x =  current.x + accel.x+ calcVel.x;
	 		item.aabbObject->center.y =  current.y + accel.y+ calcVel.y;
	 		item.aabbObject->center.z =  current.z + accel.z+ calcVel.z;
	 }
	 else
	 {
		 	 item.sphereObject->center.x =  current.x + accel.x+ calcVel.x;
		 	 item.sphereObject->center.y =  current.y + accel.y+ calcVel.y;
		 	 item.sphereObject->center.z =  current.z + accel.z+ calcVel.z;
	 }
	// item.oldPosition = current;



 }

physicsInfo insertPhysicsObject(aabb_t *obj, float m, Velocity linVel, Force linFrc, Velocity angVel, Force angFrc)
{
	physicsInfo newItem;
	newItem.aabbObject = obj;
	newItem.sphereObject = NULL;
	newItem.mass = m;
	newItem.linearVelocity =linVel;
	newItem.linearForce= linFrc;
	newItem.angularVelocity = angVel;
	newItem.angularForce = angFrc;
	physicsObjects.push_back(newItem);
	//newItem.oldPosition = obj->center;
	return newItem;
}

physicsInfo insertPhysicsObject(sphere_t *obj, float m, Velocity linVel, Force linFrc, Velocity angVel, Force angFrc)
{
	physicsInfo newItem;
	newItem.aabbObject = NULL;
	newItem.sphereObject = obj;
	newItem.mass = m;
	newItem.linearVelocity =linVel;
	newItem.linearForce= linFrc;
	newItem.angularVelocity = angVel;
	newItem.angularFrc= angFrc;
	//newItem.oldPosition = obj->center;
	physicsObjects.push_back(newItem);
	return newItem;
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
