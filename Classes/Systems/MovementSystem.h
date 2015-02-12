/*
 * MovementSystem.h
 *
 *  Created on: Feb 12, 2015
 *      Author: ihall1
 */

#ifndef __MOVEMENT_SYSTEM_H__
#define __MOVEMENT_SYSTEM_H__

#include "../Components/Components.h"
#include "../Evolve/evolve2d.h"
using namespace evolve2d;

class MovementSystem: public evolve2d::EntityProcessingSystem {
private:
	ComponentMapper<PositionComponent> positionMapper;
	ComponentMapper<VelocityComponent> velocityMapper;
public:
	MovementSystem();
	virtual ~MovementSystem();
	virtual void initialize();
	virtual void processEntity(Entity &e);
};

#endif /* __MOVEMENT_SYSTEM_H__ */
