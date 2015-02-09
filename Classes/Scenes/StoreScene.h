/*
 * StoreScene.h
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#ifndef __STORE_SCENE_H__
#define __STORE_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class StoreScene : Scene {
public:
	static Scene * createScene();

	// Override Scene::init() with our own init method for our storescene
	virtual bool init();

	// Create the create method for "StoreScene" and make the call to the init method using this macro
	CREATE_FUNC(StoreScene);
};

#endif /* __STORE_SCENE_H__ */
