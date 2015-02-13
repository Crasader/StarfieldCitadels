/*
 * RenderComponent.cpp
 *
 *  Created on: Feb 10, 2015
 *      Author: ihall1
 */

#include "RenderComponent.h"

RenderComponent::RenderComponent(Layer * layer) {
	this->layer = layer;
}

RenderComponent::~RenderComponent() {
	// TODO Auto-generated destructor stub
}

Layer * RenderComponent::getLayer() {
	return layer;
}

