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

GraphicsComponent::GraphicsComponent(std::string nameString, int zOrder) {
	GETFILENAME(_fileName, 32, nameString.c_str());
    _graphics = Sprite::create(_fileName);
    SCALENODE_XY(_graphics);
    _graphics->retain();
    this->_zOrder = zOrder;
}

GraphicsComponent::~GraphicsComponent() {
	// TODO Auto-generated destructor stub
}

Node * GraphicsComponent::getGraphics() {
    return _graphics;
}

int GraphicsComponent::getOrder() {
    return _zOrder;
}

