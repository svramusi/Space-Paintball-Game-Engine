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
void PhysicsEngine::calculateAngularVelocity(physicsInfo *item, float deltaT)
{
	//and vel = ang vel + abs(poi - pos cur) * ABS(Ang Force Cur) * sin(a)
	Velocity newV;
	Point current;
	float I;
	Point N;
		 if(item.aabbObject != NULL)
		 {
			  current =item->aabbObject->center;
			  I = (item->aabbObject->radii[0]+ item->aabbObject->radii[1])/12; //only 2d H and Width
		 }
		 else
		 {
			  current =item->sphereObject->center;
			  I = item->mass *(item->sphereObject->radius*item->sphereObject->radius)/2;
		 }
	Point poi = calculatePointofImapct(item,deltaT);
	Point temp ;
	temp.x= item->angularVelocity.x * deltaT;
	temp.y = item->angularVelocity.y * deltaT;
	temp.z = item->angularVelocity.z * deltaT;

	float alpha = calculateAngle(current,poi,temp);
	N.x = abs(poi.x - current.x)* abs(item->angularForce.x)*sin(alpha);
	N.y = abs(poi.y - current.y)* abs(item->angularForce.y)*sin(alpha);
	//We ignore Z, no 3d angular force
	newV.x= item->angularVelocity.x + (N.x/I)* deltaT;
	newV.y= item->angularVelocity.y + (N.y/I)* deltaT;
	newV.z= item->angularVelocity.z; //dummy
	item->angularVelocity = newV;
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
Point PhysicsEngine::calculatePointofImapct(physicsInfo *item, float deltaT)
{
	Point POI;
	return POI;
}


float PhysicsEngine::calculateAngle(Point POI, Point Center, Point p3)
{
	float angle = GetAngleBetweenVerticese(Center, POI, p3);
	return angle;

}

float PhysicsEngine::GetDistanceOfVertex(float x, float y)
        {
            return sqrt((x * x) + (y * y));
        }


        //V2 ALWAYS NEEDS TO BE THE MIDDLE VERTEX
       float PhysicsEngine::GetAngleBetweenVerticese(Point v1, Point v2, Point v3)
        {
            float a = GetDistanceBetweenVertices(v1, v2);
            float b = GetDistanceBetweenVertices(v2, v3);
            float c = GetDistanceBetweenVertices(v1, v3);

            return (RadiansToDegrees(cos(((a * a) + (b * b) - (c * c)) / (2 * a * b))));
        }

       float PhysicsEngine::GetDistanceBetweenVertices(Point v1, Point v2)
               {
                   float xDistance = abs(v1.x - v2.x);
                   float yDistance = abs(v1.y - v2.y);
                   return GetDistanceOfVertex(xDistance, yDistance);
               }

       float PhysicsEngine::RadiansToDegrees(float rad)
        {
            return (rad * (180.0 / PI));
        }





void PhysicsEngine::calculateAngularPosition(physicsInfo *item, float deltaT)
{
	//ang velnew = and velcurr + ang acc *deltat
	Point newP;


			/* accel.x = (item.angularForce.x/item.mass)*deltaT;
			 accel.y = (item.angularForce.y/item.mass)*deltaT;
			 accel.z = (item.angularForce.z/item.mass)*deltaT;*/
	 	 	 newP.x = item->angularPosition.x + item->angularVelocity.x * deltaT;
	 	 	 newP.y= item->angularPosition.y + item->angularVelocity.y * deltaT;
	 	 	 newP.z = item->angularPosition.z + item->angularVelocity.z * deltaT;
			 /*newV.x = item.angularVelocity.x + accel.x;
			 newV.y = item.angularVelocity.y + accel.y;
			 newV.z = item.angularVelocity.z + accel.z;*/
			 item->angularPosition= newP;

}


void PhysicsEngine::calculateLinearAcceleration(physicsInfo *item, float deltaT)
{
	//accel x = accel x - gravity*deltaT
	//accel y= accel y - wind *deltaT
	Force accel;
	accel.x = (item->linearForce.x/item->mass)+(gravity*deltaT);
	accel.y = (item->linearForce.y/item->mass)+(airfriction*deltaT);
	accel.z = (item->linearForce.z/item->mass); //no wind so no Z force

	item->linearForce.x = accel.x*item->mass;
	item->linearForce.y = accel.y*item->mass;
	item->linearForce.z = accel.z*item->mass;
}


void PhysicsEngine::calculateLinearVelocity(physicsInfo *item, float deltaT)
{
	//Velocity new = vel cur + Acc * deltaT
	     Force accel;
	     Velocity newV;
		 accel.x = (item->linearForce.x/item->mass)*deltaT;
		 accel.y = (item->linearForce.y/item->mass)*deltaT;
		 accel.z = (item->linearForce.z/item->mass)*deltaT;

		 newV.x = item->linearVelocity.x + accel.x;
		 newV.y = item->linearVelocity.y + accel.y;
		 newV.z = item->linearVelocity.z + accel.z;
		 item->linearVelocity = newV;
}

 void PhysicsEngine::calculatePosition(physicsInfo *item, float deltaT)
 {

		// using verlet integration
	 	 // postion of New = Position current + vel Cur* deltaT + acceleration (dt^2)
	 Point current;
	 if(item->aabbObject != NULL)
		  current =item->aabbObject->center;
	 else
		  current =item->sphereObject->center;
	 Velocity calcVel = item->linearVelocity;
	 Force accel;
	 Point newP;
	 float timeSqr = deltaT*deltaT;
	 calcVel.x = calcVel.x * deltaT;
	 calcVel.y =calcVel.y * deltaT;
	 calcVel.z = calcVel.z * deltaT;

	 accel.x = (item->linearForce.x/item->mass)*timeSqr;
	 accel.y = (item->linearForce.y/item->mass)*timeSqr;
	 accel.z = (item->linearForce.z/item->mass)*timeSqr;

	 newP.x = current.x + accel.x+ calcVel.x;
	 newP.y = current.y + accel.y+ calcVel.y;
	 newP.z = current.z + accel.z+ calcVel.z;

	 if(item.aabbObject != NULL)
	 {
	 		item->aabbObject->center.x =  current.x + accel.x+ calcVel.x;
	 		item->aabbObject->center.y =  current.y + accel.y+ calcVel.y;
	 		item->aabbObject->center.z =  current.z + accel.z+ calcVel.z;
	 }
	 else
	 {
		 	 item->sphereObject->center.x =  current.x + accel.x+ calcVel.x;
		 	 item->sphereObject->center.y =  current.y + accel.y+ calcVel.y;
		 	 item->sphereObject->center.z =  current.z + accel.z+ calcVel.z;
	 }
	// item.oldPosition = current;



 }

physicsInfo PhysicsEngine::insertPhysicsObject(aabb_t *obj, float m, Velocity linVel, Force linFrc, Velocity angVel, Force angFrc, Point angPos)
{
	physicsInfo newItem;
	newItem.aabbObject = obj;
	newItem.sphereObject = NULL;
	newItem.mass = m;
	newItem.linearVelocity =linVel;
	newItem.linearForce= linFrc;
	newItem.angularVelocity = angVel;
	newItem.angularForce = angFrc;
	newItem.angularPosition = angPos;
	physicsObjects.push_back(newItem);

	//newItem.oldPosition = obj->center;
	return newItem;
}

physicsInfo PhysicsEngine::insertPhysicsObject(sphere_t *obj, float m, Velocity linVel, Force linFrc, Velocity angVel, Force angFrc, Point angPos)
{
	physicsInfo newItem;
	newItem.angularPosition = angPos;
	newItem.aabbObject = NULL;
	newItem.sphereObject = obj;
	newItem.mass = m;
	newItem.linearVelocity =linVel;
	newItem.linearForce= linFrc;
	newItem.angularVelocity = angVel;
	newItem.angularForce= angFrc;
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
