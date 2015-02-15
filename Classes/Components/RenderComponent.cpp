/*
 * RenderComponent.cpp
 *
 *  Created on: Feb 10, 2015
 *      Author: ihall1
 */

#include "RenderComponent.h"

RenderComponent::RenderComponent(Node * node) {
	this->node = node;
}

RenderComponent::~RenderComponent() {
	// TODO Auto-generated destructor stub
}

Node * RenderComponent::getNode() {
	return node;
}

