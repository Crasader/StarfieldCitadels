/*
 * LoadingScene.h
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__
#define COCOS2D_DEBUG 1

#include "../Evolve/evolve2d.h"
using namespace evolve2d;

#include "cocos2d.h"
// Using namespace cocos2d macro
USING_NS_CC;

#include "../Components/Components.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../ResourceLoader.h"

class LoadingScene : public Scene {
private:
	World _world;
	SystemManager *_sm;
	EntityManager *_em;

	// System declaration
	RenderSystem *_renderSys;

	// Entity declaration

	// Component declaration
	PositionComponent *_comp;
public:
	static Scene * createScene();

	// Override Scene::init() with our own init method for oour loading scene
	virtual bool init();

	virtual void update(float delta);

	void checkForAssetUpdates();

	// Create the create method for "LoadingScreen" and make the call to the init method using this macro
	CREATE_FUNC(LoadingScene);
};

#endif /* __LOADING_SCENE_H__ */
