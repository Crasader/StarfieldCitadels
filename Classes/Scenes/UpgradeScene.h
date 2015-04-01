/*
 * UpgradeScene.h
 *
 *  Created on: March 31, 2015
 *      Author: Kristen Ernst
 */

#ifndef __UPGRADE_SCENE_H__
#define __UPGRADE_SCENE_H__

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

class UpgradeScene : public Scene {
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

	bool boughtHoriWall;
	bool boughtVerWall;
	bool boughtHoriPlasma;
	bool boughtVerPlasma;
	bool boughtStarDustTree;
	bool boughtGalacticStone;

	int warriorRank;
	string warriorHealth;
	string warriorAttack;
	int spaceRangerRank;
	string spaceRangerHealth;
	string spaceRangerAttack;
	int scoutRank;
	string scoutHealth;
	string scoutAttack;
	int clericRank;
	string clericHealth;
	string clericAttack;
	int assassinRank;
	string assassinHealth;
	string assassinAttack;
	int mageRank;
	string mageHealth;
	string mageAttack;

	int horiWallRank;
	string horiWallHealth;
	int verWallRank;
	string verWallHealth;
	int horiPlasmaRank;
	string horiPlasmaHealth;
	int verPlasmaRank;
	string verPlasmaHealth;
	int starDustTreeRank;
	string starDustTreeHealth;
	int galacticStoneRank;
	string galacticStoneHealth;

public:
	static Scene * createScene();

	// Override Scene::init() with our own init method for our upgradescene
	virtual bool init();

	void doNothing(cocos2d::Ref* pSender);
	void loadMainView(cocos2d::Ref* pSender);
	void setMainScene(MainScene* scene);
	void cancelFromUpgrade(cocos2d::Ref* pSender);
	void toUpgradeMenu(cocos2d::Ref* pSender);
	void toUpgradeCitadel(cocos2d::Ref* pSender);
	void cancelFromConfirmUpgrade(cocos2d::Ref* pSender);

	void upgradeFirstSoldier(cocos2d::Ref* pSender);
	void confirmFirstUpgrade(cocos2d::Ref* pSender);
	void upgradeFirstStats(cocos2d::Ref* pSender);
	void upgradeSecondSoldier(cocos2d::Ref* pSender);
	void confirmSecondUpgrade(cocos2d::Ref* pSender);
	void upgradeSecondStats(cocos2d::Ref* pSender);
	void upgradeThirdSoldier(cocos2d::Ref* pSender);
	void confirmThirdUpgrade(cocos2d::Ref* pSender);
	void upgradeThirdStats(cocos2d::Ref* pSender);
	void upgradeFourthSoldier(cocos2d::Ref* pSender);
	void confirmFourthUpgrade(cocos2d::Ref* pSender);
	void upgradeFourthStats(cocos2d::Ref* pSender);
	void upgradeFifthSoldier(cocos2d::Ref* pSender);
	void confirmFifthUpgrade(cocos2d::Ref* pSender);
	void upgradeFifthStats(cocos2d::Ref* pSender);
	void upgradeSixthSoldier(cocos2d::Ref* pSender);
	void confirmSixthUpgrade(cocos2d::Ref* pSender);
	void upgradeSixthStats(cocos2d::Ref* pSender);

	void upgradeFirstBuiltItem(cocos2d::Ref* pSender);
	void confirmFirstItemUpgrade(cocos2d::Ref* pSender);
	void upgradeFirstItemStats(cocos2d::Ref* pSender);
	void upgradeSecondBuiltItem(cocos2d::Ref* pSender);
	void confirmSecondItemUpgrade(cocos2d::Ref* pSender);
	void upgradeSecondItemStats(cocos2d::Ref* pSender);
	void upgradeThirdBuiltItem(cocos2d::Ref* pSender);
	void confirmThirdItemUpgrade(cocos2d::Ref* pSender);
	void upgradeThirdItemStats(cocos2d::Ref* pSender);
	void upgradeFourthBuiltItem(cocos2d::Ref* pSender);
	void confirmFourthItemUpgrade(cocos2d::Ref* pSender);
	void upgradeFourthItemStats(cocos2d::Ref* pSender);
	void upgradeFifthBuiltItem(cocos2d::Ref* pSender);
	void confirmFifthItemUpgrade(cocos2d::Ref* pSender);
	void upgradeFifthItemStats(cocos2d::Ref* pSender);
	void upgradeSixthBuiltItem(cocos2d::Ref* pSender);
	void confirmSixthItemUpgrade(cocos2d::Ref* pSender);
	void upgradeSixthItemStats(cocos2d::Ref* pSender);

	void setBoughtHeroOne (bool hero);
	void setBoughtHeroTwo (bool hero);
	void setBoughtHeroThree (bool hero);
	void setBoughtHeroFour (bool hero);
	void setBoughtHeroFive (bool hero);
	void setBoughtHeroSix (bool hero);

	void setBoughtItemOne (bool item);
	void setBoughtItemTwo (bool item);
	void setBoughtItemThree (bool item);
	void setBoughtItemFour (bool item);
	void setBoughtItemFive (bool item);
	void setBoughtItemSix (bool item);

	void setHeroOneRank(int rank);
	void setHeroTwoRank(int rank);
	void setHeroThreeRank(int rank);
	void setHeroFourRank(int rank);
	void setHeroFiveRank(int rank);
	void setHeroSixRank(int rank);

	void setHeroOneAttack(string attack);
	void setHeroTwoAttack(string attack);
	void setHeroThreeAttack(string attack);
	void setHeroFourAttack(string attack);
	void setHeroFiveAttack(string attack);
	void setHeroSixAttack(string attack);

	void setHeroOneHealth(string health);
	void setHeroTwoHealth(string health);
	void setHeroThreeHealth(string health);
	void setHeroFourHealth(string health);
	void setHeroFiveHealth(string health);
	void setHeroSixHealth(string health);

	void setItemOneRank(int rank);
	void setItemTwoRank(int rank);
	void setItemThreeRank(int rank);
	void setItemFourRank(int rank);
	void setItemFiveRank(int rank);
	void setItemSixRank(int rank);

	void setItemOneHealth(string health);
	void setItemTwoHealth(string health);
	void setItemThreeHealth(string health);
	void setItemFourHealth(string health);
	void setItemFiveHealth(string health);
	void setItemSixHealth(string health);

	// Create the create method for "UpgradeScene" and make the call to the init method using this macro
	CREATE_FUNC(UpgradeScene);
};

#endif /* __UPGRADE_SCENE_H__ */
