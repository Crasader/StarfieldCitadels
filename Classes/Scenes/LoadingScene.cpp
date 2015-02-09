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

	// Generate Scene layers
	auto layer = LayerColor::create(Color4B(255,255,255,255));

	scene->addChild(layer);

	return scene;
}

bool LoadingScene::init()
{
	// Call super init first
	if(!Scene::init())
	{
		return false;
	}

	return true;
}
