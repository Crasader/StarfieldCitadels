/*
 * RenderSystem.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: ihall1
 */

#include "RenderSystem.h"

RenderSystem::RenderSystem() {
	setComponentTypes<RenderComponent, PositionComponent, GraphicsComponent>();

}

RenderSystem::~RenderSystem() {
	// TODO Auto-generated destructor stub
}

void RenderSystem::initialize() {
	renderMapper.init(*world);
	graphicsMapper.init(*world);
    positionMapper.init(*world);
}

void RenderSystem::added(Entity &e) {
    renderMapper.get(e)->getNode()->addChild(graphicsMapper.get(e)->getGraphics());
    
}

void RenderSystem::removed(Entity &e) {
    
}

void RenderSystem::begin() {
    
}

void RenderSystem::end() {
    
}

void RenderSystem::processEntity(Entity &e) {
    graphicsMapper.get(e)->getGraphics()->setPosition(Vec2(positionMapper.get(e)->posX, positionMapper.get(e)->posY));
}

