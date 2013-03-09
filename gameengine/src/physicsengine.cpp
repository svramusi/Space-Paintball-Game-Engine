#include <stdlib.h>
#include <math.h>


#include "physicsengine.h"

#define PI 3.14159265

using namespace std;

PhysicsEngine::PhysicsEngine()
{
    cd = new CollisionDetection();
    SetWorldParams(9.81, 1.225);
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

void
PhysicsEngine::SetWorldParams(float grav, float air)
{
    gravity = grav;
    airFriction = air;

    latestID = 0;

    lastTimeStep = 0.0f;
}

void
PhysicsEngine::updateWorld(float timeStep)
{
    //NEED DELTAT

    /*1) Add all the forces (gravity, etc.) for each object
    2) Run the physical simulation step ("Explicit Euler" or "Verlet Integration")
    3) Call the collision detection module to detect collisions
    4) For each collision detected, execute the physics code that determines their velocities after the collision (i.e. the formulas in slide 57).
    5) Execute the collision fixer*/

cout << endl << "updating world.  current time is: " << timeStep << endl << endl;

    float delta = timeStep - lastTimeStep;
    lastTimeStep = timeStep;

    for (std::vector<physicsInfo>::iterator it = physicsObjects.begin(); it != physicsObjects.end(); ++it)
    {
        if((*it).moveable) {
            calculateLinearForce(&(*it), delta);

            calculateLinearVelocity(&(*it), delta);

            calculatePosition(&(*it), delta);

            calculateAngularVelocity(&(*it),timeStep);

            calculateAngularPosition(&(*it),timeStep); //NEEDS CALCULATE POI UPDATED TO WORK

            cout << endl << "updating object. id:" << (*it).ID;
            cout << endl << "center X:" << (*it).collidableObject->getCenter().x;
            cout << endl << "center Y:" << (*it).collidableObject->getCenter().y;
            cout << endl << "center Z:" << (*it).collidableObject->getCenter().z;
            cout << endl << endl;

            cd->updateObject((*it).ID, (*it).collidableObject->getCenter());

            //are we better to just do center in constructor?
        }
    }

    collisions_t *collisions = cd->checkForAnyCollisions();

    if(collisions != NULL) {
        cout << endl << "There is a collision between object ID: " << collisions->ID
            << " and object ID: " << collisions->info->ID << endl << endl;
        penetration_t penetration = collisions->info->penetration;

        cout << endl << "penetration x: " << penetration.x << " penetration y: " << penetration.y << " penetration z: " << penetration.y << endl;

    }

    cd->freeCollisions(collisions);

/*
    detectCollision* collidableObject;

    collidableObject = (detectCollision*)malloc(sizeof(detectCollision));
    collidableObject->collidableObjectID = 1;

    collisionDetection* collisions = cd->detect_collision(collidableObject);

    freeCollisions(collisions);
    free(collidableObject);
*/
}



void PhysicsEngine::calculateAngularVelocity(physicsInfo *item, float deltaT)
{
    //and vel = ang vel + abs(poi - pos cur) * ABS(Ang Force Cur) * sin(a)
    Velocity newV;
    Point current;
    float I;
    Point N;

    current = item->collidableObject->getCenter();
    CollidableObject *collidableObject = item->collidableObject;

    if(typeid(AABB) == typeid(collidableObject))
    {
        AABB *tempAABB = dynamic_cast<AABB*>(collidableObject);
        float xRadius  = tempAABB->getXRadius();
        float yRadius  = tempAABB->getYRadius();
        I = (xRadius + yRadius)/12;
        delete tempAABB;
    }
    else if(typeid(Sphere) == typeid(collidableObject))
    {
        Sphere *sphere = dynamic_cast<Sphere*>(collidableObject);
        float radius = sphere->getRadius();
        I = item->mass * (radius * radius)/2;
        delete sphere;
    }

    Point poi = calculatePointofImapct(item,deltaT);
    Point temp;
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
    Point POI = item->collidableObject->getCenter();
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

void PhysicsEngine::calculateLinearForce(physicsInfo *item, float deltaT)
{
    float mass = item->mass;

    float xAccel = (item->linearForce.x/mass) + (airFriction * deltaT);
    float yAccel = (item->linearForce.y/mass) + (gravity * deltaT);
    float zAccel = (item->linearForce.z/mass);

    item->linearForce.x = mass * xAccel;
    item->linearForce.y = mass * yAccel;
    item->linearForce.z = mass * zAccel;
}


void PhysicsEngine::calculateLinearVelocity(physicsInfo *item, float deltaT)
{
    float mass = item->mass;

    //Velocity new = vel cur + Acc * deltaT
    float xAccel = (item->linearForce.x/mass) * deltaT;
    float yAccel = (item->linearForce.y/mass) * deltaT;
    float zAccel = (item->linearForce.z/mass) * deltaT;

    item->linearVelocity.x += xAccel;
    item->linearVelocity.y += yAccel;
    item->linearVelocity.z += zAccel;
}

 void PhysicsEngine::calculatePosition(physicsInfo *item, float deltaT)
 {
    // using verlet integration
    // postion of New = Position current + vel Cur* deltaT + acceleration (dt^2)

    Velocity velocity = item->linearVelocity;
    float xVel = velocity.x * deltaT;
    float yVel = velocity.y * deltaT;
    float zVel = velocity.z * deltaT;

    float mass = item->mass;
    float timeSqr = deltaT*deltaT;

    float xAccel = (item->linearForce.x/mass) * timeSqr;
    float yAccel = (item->linearForce.y/mass) * timeSqr;
    float zAccel = (item->linearForce.z/mass) * timeSqr;

    Point currentCenter = item->collidableObject->getCenter();
    Point newCenter;
    newCenter.x = currentCenter.x + xAccel + xVel;
    newCenter.y = currentCenter.y + yAccel + yVel;
    newCenter.z = currentCenter.z + zAccel + zVel;

    item->collidableObject->setCenter(newCenter);
 }

void PhysicsEngine::insertPhysicsObject(CollidableObject *obj, float m, Velocity linVel, Force linFrc, Velocity angVel, Force angFrc, Point angPos)
{
    physicsInfo newItem;

    newItem.ID = latestID;
    obj->setID(latestID);
    newItem.collidableObject = obj;
    newItem.moveable = obj->isMovable();

    newItem.mass = m;

    newItem.linearVelocity = linVel;
    newItem.linearForce = linFrc;

    newItem.angularVelocity = angVel;
    newItem.angularForce = angFrc;
    newItem.angularPosition = angPos;


    //newItem.oldPosition = obj->center;
    physicsObjects.push_back(newItem);

    cd->addObject(obj);

    latestID++;
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
