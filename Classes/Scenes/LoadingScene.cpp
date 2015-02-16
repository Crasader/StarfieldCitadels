/*
 * LoadingScene.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#include "LoadingScene.h"

Scene * LoadingScene::createScene()
{
	auto scene = LoadingScene::create();

	return scene;
}

bool LoadingScene::init()
{
	// Call super init first
	if(!Scene::init())
	{
		return false;
	}
    
    
    //this->scheduleUpdate();

	return true;
}

void LoadingScene::update(float delta) {
	world.loopStart();
	world.setDelta(delta);

	//CCLOG("X: %f", comp->posX);
	//CCLOG("Y: %f", comp->posY);
}
