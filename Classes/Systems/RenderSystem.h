/*
 * RenderSystem.h
 *
 *  Created on: Feb 13, 2015
 *      Author: ihall1
 */

#ifndef __RENDER_SYSTEM_H__
#define __RENDER_SYSTEM_H__

#include "../Components/Components.h"
#include "../Layers/Layers.h"
#include "../Evolve/evolve2d.h"
using namespace evolve2d;

class RenderSystem: public evolve2d::EntityProcessingSystem {
private:
	ComponentMapper<RenderComponent> _renderMapper;
	ComponentMapper<GraphicsComponent> _graphicsMapper;
    ComponentMapper<PositionComponent> _positionMapper;
    ComponentMapper<AnchorPointComponent> _anchorPointMapper;
public:
	RenderSystem();
	~RenderSystem();
	void initialize();
    void added(Entity &e);
    void removed(Entity &e);
    void begin();
    void end();
	void processEntity(Entity &e);
};

#endif /* __RENDER_SYSTEM_H__ */
