/*
 * RenderSystem.h
 *
 *  Created on: Feb 13, 2015
 *      Author: ihall1
 */

#ifndef __RENDER_SYSTEM_H__
#define __RENDER_SYSTEM_H__

#include "../Components/Components.h"
#include "../Evolve/evolve2d.h"
using namespace evolve2d;

class RenderSystem: public evolve2d::EntityProcessingSystem {
private:
	ComponentMapper<RenderComponent> renderMapper;
	ComponentMapper<SpriteComponent> spriteMapper;
public:
	RenderSystem();
	~RenderSystem();
	void initialize();
	void processEntity(Entity &e);
};

#endif /* __RENDER_SYSTEM_H__ */
