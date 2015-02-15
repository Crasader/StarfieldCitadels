/*
 * SpriteComponent.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: ihall1
 */

#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent(Node * graphics) {
	this->graphics = graphics;
}

GraphicsComponent::~GraphicsComponent() {
	// TODO Auto-generated destructor stub
}

Node * GraphicsComponent::getGraphics() {
	return graphics;
}

