#ifndef COLLISION_INFO_H
#define COLLISION_INFO_H

typedef struct collision_detection_t {
    int objectID;
    int collisionID;
    collision_detection_t* prev;
    collision_detection_t* next;
} collisionDetection;

typedef struct detect_collision_t {
    int collidableObjectID;
    //GameObject* gameWorld;
} detectCollision;

#endif
