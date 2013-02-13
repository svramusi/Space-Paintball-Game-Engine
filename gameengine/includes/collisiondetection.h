#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "collisioninfo.h"

class CollisionDetection {
public:
	CollisionDetection();
    ~CollisionDetection();
    collisionDetection* detect_collision(detectCollision* collidableObject);

private:

};
#endif
