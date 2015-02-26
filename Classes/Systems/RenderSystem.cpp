/*
 * RenderSystem.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: ihall1
 */

#include "RenderSystem.h"

RenderSystem::RenderSystem() {
	setComponentTypes<RenderComponent, PositionComponent, GraphicsComponent, AnchorPointComponent>();

}

RenderSystem::~RenderSystem() {
	// TODO Auto-generated destructor stub
}

void RenderSystem::initialize() {
	_renderMapper.init(*world);
	_graphicsMapper.init(*world);
    _positionMapper.init(*world);
    _anchorPointMapper.init(*world);
}

void RenderSystem::added(Entity &e) {
    _renderMapper.get(e)->getNode()->addChild(_graphicsMapper.get(e)->getGraphics());
    
}

void RenderSystem::removed(Entity &e) {
    
}

void RenderSystem::begin() {
    
}

void RenderSystem::end() {
    
}

void RenderSystem::processEntity(Entity &e) {
    _graphicsMapper.get(e)->getGraphics()->setPosition(Vec2(_positionMapper.get(e)->posX, _positionMapper.get(e)->posY));
    _graphicsMapper.get(e)->getGraphics()->setAnchorPoint(Vec2(_anchorPointMapper.get(e)->getAnchorPointX(),_anchorPointMapper.get(e)->getAnchorPointY()));
}

