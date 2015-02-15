/*
 * HeroScene.h
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#ifndef __HERO_SCENE_H__
#define __HERO_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HeroScene : public Scene {
public:
	static Scene * createScene();

	// Override Scene::init() with our own init method for our heroscene
	virtual bool init();

	// Create the create method for "HeroScene" and make the call to the init method using this macro
	CREATE_FUNC(HeroScene);
};

#endif /* __HERO_SCENE_H__ */
