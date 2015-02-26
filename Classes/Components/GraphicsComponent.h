/*
 * SpriteComponent.h
 *
 *  Created on: Feb 13, 2015
 *      Author: ihall1
 */

#ifndef __SPRITE_COMPONENT_H__
#define __SPRITE_COMPONENT_H__

#include "../GameManager.h"

#include "../Evolve/evolve2d.h"
using namespace evolve2d;

#include "cocos2d.h"
USING_NS_CC;

class GraphicsComponent: public evolve2d::Component {
private:
	char _fileName[32];
public:
	//GraphicsComponent(Node * graphics);
	GraphicsComponent(std::string nameString);
	virtual ~GraphicsComponent();

	Node * getGraphics();
};

#endif /* __SPRITE_COMPONENT_H__ */
