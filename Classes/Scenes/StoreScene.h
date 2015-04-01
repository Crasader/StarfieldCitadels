/*
 * StoreScene.h
 *
 *  Created on: March 28, 2015
 *      Author: Kristen Ernst
 */

#ifndef __STORE_SCENE_H__
#define __STORE_SCENE_H__

#include "../Evolve/evolve2d.h"
using namespace evolve2d;

#include "../Components/Components.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"

#include "MainScene.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include <string>
#include <iostream>
#include <utility>
#include <list>
#include <vector>
using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

class MainScene;

class StoreScene : public Scene {
private:

	bool boughtHoriWall;
	bool boughtVerWall;
	bool boughtHoriPlasma;
	bool boughtVerPlasma;
	bool boughtStarDustTree;
	bool boughtGalacticStone;

	Vec2 currentTouchedPoint;
	vector<int> builtItemNumbers;
	vector<Vec2> builtItemLocations;

	BaseLayer* baseLayer;
	AnimationLayer* animationLayer;
	HUDLayer* hudLayer;
	UILayer* uiLayer;
	MainScene* mainScene;


public:
	static Scene * createScene();

	// Override Scene::init() with our own init method for our storescene
	virtual bool init();
	StoreScene();
	virtual ~StoreScene();

	void doNothing(cocos2d::Ref* pSender);
	void loadMainView(cocos2d::Ref* pSender);
	bool touchChecker(cocos2d::Touch* touch, cocos2d::Event* event);
	void cancelFromConfirmBuild(cocos2d::Ref* pSender);
	void toBuildMenuStep(cocos2d::Ref* pSender);
	void createFirstItem(cocos2d::Touch* touch, cocos2d::Event* event);
	void buildFirstItem(cocos2d::Ref* pSender);
	void buildTheFirstItem(cocos2d::Ref* pSender);
	void createSecondItem(cocos2d::Touch* touch, cocos2d::Event* event);
	void buildSecondItem(cocos2d::Ref* pSender);
	void buildTheSecondItem(cocos2d::Ref* pSender);
	void createThirdItem(cocos2d::Touch* touch, cocos2d::Event* event);
	void buildThirdItem(cocos2d::Ref* pSender);
	void buildTheThirdItem(cocos2d::Ref* pSender);
	void createFourthItem(cocos2d::Touch* touch, cocos2d::Event* event);
	void buildFourthItem(cocos2d::Ref* pSender);
	void buildTheFourthItem(cocos2d::Ref* pSender);
	void createFifthItem(cocos2d::Touch* touch, cocos2d::Event* event);
	void buildFifthItem(cocos2d::Ref* pSender);
	void buildTheFifthItem(cocos2d::Ref* pSender);
	void createSixthItem(cocos2d::Touch* touch, cocos2d::Event* event);
	void buildSixthItem(cocos2d::Ref* pSender);
	void buildTheSixthItem(cocos2d::Ref* pSender);

	void setMainScene(MainScene* scene);
	void setUpPreviousBuiltItems();
	void setUpBuiltLocations(vector<Vec2> locations);
	void setUpBuiltItemNums(vector<int> itemNums);
	// Create the create method for "StoreScene" and make the call to the init method using this macro
	CREATE_FUNC(StoreScene);
};

#endif /* __STORE_SCENE_H__ */
