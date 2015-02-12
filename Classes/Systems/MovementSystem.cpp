/*
 * MovementSystem.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: ihall1
 */

#include "MovementSystem.h"

MovementSystem::MovementSystem() {
	setComponentTypes<PositionComponent, VelocityComponent>();
}

MovementSystem::~MovementSystem() {
	// TODO Auto-generated destructor stub
}

void MovementSystem::initialize() {
	velocityMapper.init(*world);
	positionMapper.init(*world);
}

void MovementSystem::processEntity(Entity &e) {
	positionMapper.get(e)->posX += velocityMapper.get(e)->velocityX * world->getDelta();
	positionMapper.get(e)->posY += velocityMapper.get(e)->velocityY * world->getDelta();
}

