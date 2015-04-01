/*
 * HeroScene.h
 *
 *  Created on: March 29, 2015
 *      Author: Kristen Ernst
 */

#ifndef __HERO_SCENE_H__
#define __HERO_SCENE_H__

#include "../Evolve/evolve2d.h"
using namespace evolve2d;

#include "../Components/Components.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"

#include "MainScene.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

class MainScene;

class HeroScene : public Scene {
private:
	BaseLayer* baseLayer;
	AnimationLayer* animationLayer;
	HUDLayer* hudLayer;
	UILayer* uiLayer;
	MainScene* mainScene;

	bool boughtWarrior;
	bool boughtSpaceRanger;
	bool boughtScout;
	bool boughtCleric;
	bool boughtAssassin;
	bool boughtMage;
public:
	static Scene * createScene();

	// Override Scene::init() with our own init method for our heroscene
	virtual bool init();

	void doNothing(cocos2d::Ref* pSender);
	void loadMainView(cocos2d::Ref* pSender);
	void setMainScene(MainScene* scene);
	void setUpPreviousBoughtItems();

	void setBoughtHeroOne (bool hero);
	void setBoughtHeroTwo (bool hero);
	void setBoughtHeroThree (bool hero);
	void setBoughtHeroFour (bool hero);
	void setBoughtHeroFive (bool hero);
	void setBoughtHeroSix (bool hero);

	void buyFirstSoldier(cocos2d::Ref* pSender);
	void buySecondSoldier(cocos2d::Ref* pSender);
	void buyThirdSoldier(cocos2d::Ref* pSender);
	void buyFourthSoldier(cocos2d::Ref* pSender);
	void buyFifthSoldier(cocos2d::Ref* pSender);
	void buySixthSoldier(cocos2d::Ref* pSender);

	void exitPopup(cocos2d::Ref* pSender);
	void exitFirstPurchase(cocos2d::Ref* pSender);
	void exitSecondPurchase(cocos2d::Ref* pSender);
	void exitThirdPurchase(cocos2d::Ref* pSender);
	void exitFourthPurchase(cocos2d::Ref* pSender);
	void exitFifthPurchase(cocos2d::Ref* pSender);
	void exitSixthPurchase(cocos2d::Ref* pSender);

	void firstBatchOfSoldiers(cocos2d::Ref* pSender);
	void secondBatchOfSoldiers(cocos2d::Ref* pSender);

	// Create the create method for "HeroScene" and make the call to the init method using this macro
	CREATE_FUNC(HeroScene);
};

#endif /* __HERO_SCENE_H__ */
