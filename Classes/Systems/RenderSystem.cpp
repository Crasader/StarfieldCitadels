/*
 * RenderSystem.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: ihall1
 */

#include "RenderSystem.h"

RenderSystem::RenderSystem() {
	setComponentTypes<RenderComponent, SpriteComponent>();

}

RenderSystem::~RenderSystem() {
	// TODO Auto-generated destructor stub
}

void RenderSystem::initialize() {
	renderMapper.init(*world);
	spriteMapper.init(*world);
}

void RenderSystem::processEntity(Entity &e) {
	renderMapper.get(e)->getLayer()->addChild(spriteMapper.get(e)->getSprite());
}

