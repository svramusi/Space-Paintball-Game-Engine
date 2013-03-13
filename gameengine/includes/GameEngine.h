/*
 * GameEngine.h
 *
 *  Created on: Feb 13, 2013
 *      Author: amarppatel
 */

#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <stdio.h>

#include "SphereClass.h"
#include "physicsengine.h"


using namespace std;

class GameEngine {
public:
    GameEngine(unsigned int startTime);
    virtual ~GameEngine();

    void insertPhysicsObject(
        CollidableObject *obj, float mass, Velocity linVel, Force linForce,
        Velocity angVel, Force angForce, Point angPos
    );

    std::vector<physicsInfo> getUpdatedObjects();

    bool TimeForUpdatingAI();
    bool TimeForUpdatingPhysics();
    void UpdateAI(int imput);
    void UpdatePhysics(unsigned int timeStep);
    void UpdateGameState(int input);
    void Render();

private:
    PhysicsEngine *physics;
};

#endif /* GAMEENGINE_H_ */
