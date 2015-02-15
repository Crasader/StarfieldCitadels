/*
 * CombatScene.h
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#ifndef __COMBAT_SCENE_H__
#define __COMBAT_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class CombatScene : public Scene {
public:
	static Scene * createScene();

	// Override Scene::init() with our own init method for our combatscene
	virtual bool init();

	// Create the create method for "CombatScene" and make the call to the init method using this macro
	CREATE_FUNC(CombatScene);
};

#endif /* __COMBAT_SCENE_H__ */
