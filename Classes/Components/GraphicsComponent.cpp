/*
 * GraphicsComponent.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: ihall1
 */

#include "GraphicsComponent.h"

/*GraphicsComponent::GraphicsComponent(Node * graphics) {
	this->graphics = graphics;
}*/

GraphicsComponent::GraphicsComponent(Node * graphics, int zOrder) {
    this->_graphics = graphics;
    this->_zOrder = zOrder;
}

GraphicsComponent::GraphicsComponent(std::string fileName, int zOrder) {
    _graphics = Sprite::create(fileName);
    SCALENODE_XY(_graphics);
    _graphics->retain();
    this->_zOrder = zOrder;
}

GraphicsComponent::~GraphicsComponent() {
	_graphics->release();
}

Node * GraphicsComponent::getGraphics() {
    return _graphics;
}

int GraphicsComponent::getOrder() {
    return _zOrder;
}

