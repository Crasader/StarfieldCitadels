/*
 * LoadingScene.h
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"
// Using namespace cocos2d macro
USING_NS_CC;

class LoadingScene : Scene {
public:
	static Scene * createScene();

	// Override Scene::init() with our own init method for oour loading scene
	virtual bool init();

	// Create the create method for "LoadingScreen" and make the call to the init method using this macro
	CREATE_FUNC(LoadingScene);
};

#endif /* __LOADING_SCENE_H__ */
