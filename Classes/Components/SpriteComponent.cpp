/*
 * SpriteComponent.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: ihall1
 */

#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(Sprite * sprite) {
	this->sprite = sprite;
}

SpriteComponent::~SpriteComponent() {
	// TODO Auto-generated destructor stub
}

Sprite * SpriteComponent::getSprite() {
	return sprite;
}

