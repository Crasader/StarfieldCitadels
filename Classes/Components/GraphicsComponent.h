/*
 * GraphicsComponent.h
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
    Node * _graphics;
	char _fileName[32];
    int _zOrder;
public:
	GraphicsComponent(Node * graphics, int zOrder);
	GraphicsComponent(std::string nameString, int zOrder);
	virtual ~GraphicsComponent();

	Node * getGraphics();
    int getOrder();
};

#endif /* __SPRITE_COMPONENT_H__ */
