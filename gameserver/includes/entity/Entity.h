/*
 * Entity.h
 *
 *  Created on: Feb 17, 2013
 *      Author: amarppatel
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include "Visitable.h"
#include "GameState.h"

using namespace std;

class Entity : public Visitable {
public:
	Entity(string name);
	virtual ~Entity();

	string ToString();
	string GetName() const;
	virtual void AcceptVisitor(GameVisitor* visitor) = 0;
	virtual GameState* GetGameState() = 0;
protected:
	string name;
	GameState* gameState;
};

struct EntityComparer
{
    bool operator()( const Entity* first , const Entity* second) const
    {
        //if ( first.x == second.x )
        //{
        //    return first.y < second.y;
        //}

    	string name1 = first->GetName();
    	string name2 = second->GetName();
    	return (name1.compare(name2) < 0);
    }
};

#endif /* ENTITY_H_ */
