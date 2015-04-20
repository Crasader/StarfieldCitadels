/*
 * MainScene.h
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__
#define COCOS2D_DEBUG 1

#include "../Evolve/evolve2d.h"
using namespace evolve2d;

#include "../Components/Components.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"

#include "StoreScene.h"
#include "CombatScene.h"
#include "HeroScene.h"
#include "UpgradeScene.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include <string>
#include <iostream>
#include <utility>
#include <list>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "SimpleAudioEngine.h"
using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

class StoreScene;
class HeroScene;
class UpgradeScene;

class MainScene : public Scene {
private:
    World world;
    SystemManager * sm;
    EntityManager * em;
    
    // System declaration
    MovementSystem * movementSys;
    RenderSystem * renderSys;
    
    // Entity declaration
    
    // Component declaration
    PositionComponent * comp;

    // Layers
    BaseLayer* baseLayer;
	AnimationLayer* animationLayer;
	HUDLayer* hudLayer;
	UILayer* uiLayer;


    int moneyTotal;

    bool boughtHoriWall;
	bool boughtVerWall;
	bool boughtHoriPlasma;
	bool boughtVerPlasma;
	bool boughtStarDustTree;
	bool boughtGalacticStone;

    vector<int> builtItemNumbers;
	vector<Vec2> builtItemLocations;

	bool boughtHeroOne;
	bool boughtHeroTwo;
	bool boughtHeroThree;
	bool boughtHeroFour;
	bool boughtHeroFive;
	bool boughtHeroSix;

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

	// Override Scene::init() with our own init method for our main scene
	virtual bool init();
	virtual ~MainScene();

    virtual void update(float delta);

    void toBuildMenu(cocos2d::Ref* pSender);
	void toFightMenu(cocos2d::Ref* pSender);
	void toRecruitMenu(cocos2d::Ref* pSender);
	void toUpgradeMenu(cocos2d::Ref* pSender);

	vector<Vec2> getLocations();
	vector<int> getItemNumbers();
	void setLocations(vector<Vec2> locations);
	void setItemNumbers(vector<int> itemNums);
	void buildTheItems();

	void startTheTutorial();
	void tutorialText2(cocos2d::Ref* pSender);
	void tutorialText3(cocos2d::Ref* pSender);
	void tutorialText4(cocos2d::Ref* pSender);
	void tutorialText5(cocos2d::Ref* pSender);
	void tutorialText6(cocos2d::Ref* pSender);
	void tutorialText7(cocos2d::Ref* pSender);
	void tutorialText8(cocos2d::Ref* pSender);
	void tutorialText9(cocos2d::Ref* pSender);
	void tutorialText10(cocos2d::Ref* pSender);
	void tutorialText11(cocos2d::Ref* pSender);
	void tutorialText12(cocos2d::Ref* pSender);
	void tutorialText13(cocos2d::Ref* pSender);
	void tutorialText14(cocos2d::Ref* pSender);
	void tutorialText15(cocos2d::Ref* pSender);
	void tutorialText16(cocos2d::Ref* pSender);
	void tutorialText17(cocos2d::Ref* pSender);
	void tutorialText18(cocos2d::Ref* pSender);
	void tutorialText19(cocos2d::Ref* pSender);
	void tutorialText20(cocos2d::Ref* pSender);
	void tutorialText21(cocos2d::Ref* pSender);
	void tutorialText22(cocos2d::Ref* pSender);
	void tutorialText23(cocos2d::Ref* pSender);
	void tutorialText24(cocos2d::Ref* pSender);
	void tutorialText25(cocos2d::Ref* pSender);
	void tutorialText26(cocos2d::Ref* pSender);
	void tutorialText27(cocos2d::Ref* pSender);
	void tutorialText28(cocos2d::Ref* pSender);
	void tutorialText29(cocos2d::Ref* pSender);
	void tutorialText30(cocos2d::Ref* pSender);
	void tutorialText31(cocos2d::Ref* pSender);
	void tutorialText32(cocos2d::Ref* pSender);
	void tutorialText33(cocos2d::Ref* pSender);
	void tutorialText34(cocos2d::Ref* pSender);
	void tutorialText35(cocos2d::Ref* pSender);
	void tutorialText36(cocos2d::Ref* pSender);
	void tutorialText37(cocos2d::Ref* pSender);
	void tutorialText38(cocos2d::Ref* pSender);
	void tutorialText39(cocos2d::Ref* pSender);

	void exitTutorial(cocos2d::Ref* pSender);

	void doNothing(cocos2d::Ref* pSender);
	void setMoneyTotal(int money);
	void repostMoneyTotal();
	void moneyTreeClicked(cocos2d::Ref* pSender);
	void moneyStoneClicked(cocos2d::Ref* pSender);
	void exitMoneyStone(cocos2d::Ref* pSender);
	void stoneWasTouched(cocos2d::Ref* pSender);

	void setBoughtItemOne (bool item);
	void setBoughtItemTwo (bool item);
	void setBoughtItemThree (bool item);
	void setBoughtItemFour (bool item);
	void setBoughtItemFive (bool item);
	void setBoughtItemSix (bool item);

	void setBoughtHeroOne (bool hero);
	void setBoughtHeroTwo (bool hero);
	void setBoughtHeroThree (bool hero);
	void setBoughtHeroFour (bool hero);
	void setBoughtHeroFive (bool hero);
	void setBoughtHeroSix (bool hero);

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
	// Create the create method for "MainScene" and make the call to the init method using this macro
	CREATE_FUNC(MainScene);
};

#endif /* __MAIN_SCENE_H__ */
