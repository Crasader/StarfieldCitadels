/*
 * MainScene.h
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class MainScene : Scene {
public:
	static Scene * createScene();

	// Override Scene::init() with our own init method for our main scene
	virtual bool init();

	// Create the create method for "MainScene" and make the call to the init method using this macro
	CREATE_FUNC(MainScene);
};

#endif /* __MAIN_SCENE_H__ */
