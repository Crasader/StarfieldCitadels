/*
 * SpriteComponent.h
 *
 *  Created on: Feb 13, 2015
 *      Author: ihall1
 */

#ifndef __SPRITE_COMPONENT_H__
#define __SPRITE_COMPONENT_H__

#include "../Evolve/evolve2d.h"

#include "cocos2d.h"
USING_NS_CC;

class SpriteComponent: public evolve2d::Component {
private:
	Sprite * sprite;
public:
	SpriteComponent(Sprite * sprite);
	virtual ~SpriteComponent();

	Sprite * getSprite();
};

#endif /* __SPRITE_COMPONENT_H__ */
