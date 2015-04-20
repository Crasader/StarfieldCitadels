/*
 * CombatScene.h
 *
 *  Created on: March 27, 2015
 *      Author: Kristen Ernst
 */

#ifndef __COMBAT_SCENE_H__
#define __COMBAT_SCENE_H__

#include "../Evolve/evolve2d.h"
using namespace evolve2d;

#include "../Components/Components.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;


class CombatScene : public Scene {
private:
	BaseLayer* baseLayer;
	AnimationLayer* animationLayer;
	HUDLayer* hudLayer;
	UILayer* uiLayer;

public:
	static Scene * createScene();
	// Override Scene::init() with our own init method for our combatscene
	virtual bool init();

	void doNothing(cocos2d::Ref* pSender);
	void loadMainView(cocos2d::Ref* pSender);
	void toFirstFightMenu(cocos2d::Ref* pSender);
	void toSecondFightMenu(cocos2d::Ref* pSender);
	void toThirdFightMenu(cocos2d::Ref* pSender);

	void updateMessage(cocos2d::Ref* pSender);
	void exitUpdateMessage(cocos2d::Ref* pSender);

	// Create the create method for "CombatScene" and make the call to the init method using this macro
	CREATE_FUNC(CombatScene);
};

#endif /* __COMBAT_SCENE_H__ */
