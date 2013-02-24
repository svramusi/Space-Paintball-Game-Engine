#include <stdlib.h>
#include <math.h>


#include "physicsengine.h"

#define PI 3.14159265

using namespace std;

PhysicsEngine::PhysicsEngine()
{
	cd = new CollisionDetection();
	SetWorldParams(9.81, 1.225);  //defaults to earth
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
//WE NEED TO FIGURE THIS OUT, NOT SURE HOW TO DO IT
Point calculatePointofImapct(physicsInfo *item, float deltaT)
{
	Point POI;
	return POI;
}
//WE NEED TO FIGURE THIS OUT, NOT SURE HOW TO DO IT
float calculateAngle(Point POI, Point Center)
{
	float angle;
	return angle;

}

void calculateAngularVelocity(physicsInfo *item, float deltaT)
{
	//and vel = ang vel + abs(poi - pos cur) * ABS(Ang Force Cur) * sin(a)
	Velocity newV;
	Point current;
	float I;
	Point N;
		 if(item.aabbObject != NULL)
		 {
			  current =item.aabbObject->center;
			  I = (item->abbObject->radii[0]+ item->abbObject->radii[1])/12; //only 2d H and Width
		 }
		 else
		 {
			  current =item.sphereObject->center;
			  I = item->mass (item.spereObject.radius*item.spereObject.radius*)/2
		 }
	Point poi = calculatePointofImpact(item,deltaT);
	float alpha = calculateAngle(poi, current);
	N.x = abs(poi.x - current.x)* abs(item->angularForce.x)*sin(alpha);
	N.y = abs(poi.y - current.y)* abs(item->angularForce.y)*sin(alpha);
	//We ignore Z, no 3d angular force
	newV.x= item->angularVelocity.x + (N/I)* deltaT;
	newV.y= item->angularVelocity.y + (N/I)* deltaT;
	newV.z= item->angularVelocity.z; //dummy
	item->angularVelocity = newV;
}



void calculateAngularPosition(physicsInfo *item, float deltaT)
{
	//ang velnew = and velcurr + ang acc *deltat
	Point newP;


			/* accel.x = (item.angularForce.x/item.mass)*deltaT;
			 accel.y = (item.angularForce.y/item.mass)*deltaT;
			 accel.z = (item.angularForce.z/item.mass)*deltaT;*/
	 	 	 newP.x = item.angularPosition.x + item.angularVelocity.x * deltaT;
	 	 	 newP.y= item.angularPosition.y + item.angularVelocity.y * deltaT;
	 	 	 newP.z = item.angularPosition.z + item.angularVelocity.z * deltaT;
			 /*newV.x = item.angularVelocity.x + accel.x;
			 newV.y = item.angularVelocity.y + accel.y;
			 newV.z = item.angularVelocity.z + accel.z;*/
			 item.angularPosition= newP;

}


void calculateLinearAcceleration(physicsInfo *item, float deltaT)
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


void calculateLinearVelocity(physicsInfo *item, float deltaT)
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

 void calculatePosition(physicsInfo *item, float deltaT)
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

physicsInfo insertPhysicsObject(aabb_t *obj, float m, Velocity linVel, Force linFrc, Velocity angVel, Force angFrc, Point angPos)
{
	physicsInfo newItem;
	newItem->aabbObject = obj;
	newItem->sphereObject = NULL;
	newItem->mass = m;
	newItem->linearVelocity =linVel;
	newItem->linearForce= linFrc;
	newItem->angularVelocity = angVel;
	newItem->angularForce = angFrc;
	newItem->angularPosition = angPos;
	physicsObjects.push_back(newItem);

	//newItem.oldPosition = obj->center;
	return newItem;
}

physicsInfo insertPhysicsObject(sphere_t *obj, float m, Velocity linVel, Force linFrc, Velocity angVel, Force angFrc, Point angPos)
{
	physicsInfo newItem;
	newItem->angularPosition = angPos;
	newItem->aabbObject = NULL;
	newItem->sphereObject = obj;
	newItem->mass = m;
	newItem->linearVelocity =linVel;
	newItem->linearForce= linFrc;
	newItem->angularVelocity = angVel;
	newItem->angularFrc= angFrc;
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
