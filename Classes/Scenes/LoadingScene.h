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
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

#include "../Components/Components.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../ResourceLoader.h"

class LoadingScene : public Scene {
public:
	static Scene * createScene();

	// Override Scene::init() with our own init method for oour loading scene
	virtual bool init();

	void checkForAssetUpdates();

	// Create the create method for "LoadingScreen" and make the call to the init method using this macro
	CREATE_FUNC(LoadingScene);
private:
    ResourceLoader *_resLoader;
    
    ~LoadingScene();
};

#endif /* __LOADING_SCENE_H__ */
