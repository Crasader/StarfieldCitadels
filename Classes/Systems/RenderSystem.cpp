/*
 * RenderSystem.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: ihall1
 */

#include "RenderSystem.h"

RenderSystem::RenderSystem() {
	setComponentTypes<RenderComponent, PositionComponent, SpriteComponent>();

}

RenderSystem::~RenderSystem() {
	// TODO Auto-generated destructor stub
}

void RenderSystem::initialize() {
	renderMapper.init(*world);
	spriteMapper.init(*world);
    positionMapper.init(*world);
}

void RenderSystem::added(Entity &e) {
    renderMapper.get(e)->getNode()->addChild(spriteMapper.get(e)->getSprite());
    
}

void RenderSystem::removed(Entity &e) {
    
}

void RenderSystem::begin() {
    
}

void RenderSystem::end() {
    
}

void RenderSystem::processEntity(Entity &e) {
    spriteMapper.get(e)->getSprite()->setPosition(Vec2(positionMapper.get(e)->posX, positionMapper.get(e)->posY));
}

