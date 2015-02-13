/*
 * RenderComponent.h
 *
 *  Created on: Feb 10, 2015
 *      Author: ihall1
 */

#ifndef __RENDER_COMPONENT_H__
#define __RENDER_COMPONENT_H__

#include "../Evolve/evolve2d.h"
#include "cocos2d.h"
USING_NS_CC;

class RenderComponent : public evolve2d::Component {
private:
	Layer * layer;
public:
	RenderComponent(Layer * layer);
	~RenderComponent();
	Layer * getLayer();
};

#endif /* __RENDER_COMPONENT_H__ */
