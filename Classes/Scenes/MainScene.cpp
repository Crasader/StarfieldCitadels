/*
 * MainScene.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#include "MainScene.h"

#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include <string>
#include <iostream>
#include <utility>
#include <list>
#include <vector>
using namespace std;

USING_NS_CC_EXT;

USING_NS_CC;

Scene * MainScene::createScene()
{
    auto scene = MainScene::create();
    
    return scene;
}
MainScene::~MainScene()
{
}

bool MainScene::init()
{
    // Call super init first
    if(!Scene::init())
    {
        return false;
    }
    

    // The first six items in the shop
    boughtHoriWall = false;
	boughtVerWall = false;
	boughtHoriPlasma = false;
	boughtVerPlasma = false;
	boughtStarDustTree = false;
	boughtGalacticStone = false;

	boughtHeroOne = false;
	boughtHeroTwo = false;
	boughtHeroThree = false;
	boughtHeroFour = false;
	boughtHeroFive = false;
	boughtHeroSix = false;

	warriorRank = 0;
	warriorHealth = "200";
	warriorAttack = "15";
	spaceRangerRank = 0;
	spaceRangerHealth = "180";
	spaceRangerAttack = "16";
	scoutRank = 0;
	scoutHealth = "150";
	scoutAttack = "10";
	clericRank = 0;
	clericHealth = "170";
	clericAttack = "9";
	assassinRank = 0;
	assassinHealth = "230";
	assassinAttack = "19";
	mageRank = 0;
	mageHealth = "160";
	mageAttack = "14";

	horiWallRank = 0;
	horiWallHealth = "300";
	verWallRank = 0;
	verWallHealth = "300";
	horiPlasmaRank = 0;
	horiPlasmaHealth = "450";
	verPlasmaRank = 0;
	verPlasmaHealth = "450";
	starDustTreeRank = 0;
	starDustTreeHealth = "210";
	galacticStoneRank = 0;
	galacticStoneHealth = "420";

    Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Generate Scene layers
    auto baseLayer = BaseLayer::create();
    baseLayer->setName("BaseLayer");
    
    auto animationLayer = AnimationLayer::create();
    animationLayer->setName("AnimationLayer");
    
    auto hudLayer = HUDLayer::create();
    hudLayer->setName("HUDLayer");
    
    auto uiLayer = UILayer::create();
    uiLayer->setName("UILayer");
    

    auto recruitButton = MenuItemImage::create("recruit_button.jpg",
											   "recruit_button.jpg",
											   CC_CALLBACK_1(MainScene::toRecruitMenu, this));    // position the label on the center of the screen
	recruitButton->setPosition((Point(visibleSize.width - (visibleSize.width / 10), visibleSize.height - (visibleSize.height/10))));
	auto recruitMenu = Menu::create(recruitButton, NULL);
	recruitMenu->setPosition(Vec2::ZERO);
	uiLayer->addChild(recruitMenu, 1);


	auto sprite = Sprite::create("space.jpg");
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	baseLayer->addChild(sprite, 0);

	auto buildButton = MenuItemImage::create("build_button.png",
										   "build_button.png",
										   CC_CALLBACK_1(MainScene::toBuildMenu, this));
	buildButton->setPosition((Point(visibleSize.width - (visibleSize.width / 10), visibleSize.height - (visibleSize.height/3.5))));
	auto buildMenu = Menu::create(buildButton, NULL);
	buildMenu->setPosition(Vec2::ZERO);
	uiLayer->addChild(buildMenu, 1);

	auto upgradeButton = MenuItemImage::create("upgrade_button.jpg",
											   "upgrade_button.jpg",
											   CC_CALLBACK_1(MainScene::toUpgradeMenu, this));
	upgradeButton->setPosition((Point(visibleSize.width - (visibleSize.width / 10), visibleSize.height/8.5)));
	auto upgradeMenu = Menu::create(upgradeButton, NULL);
	upgradeMenu->setPosition(Vec2::ZERO);
	uiLayer->addChild(upgradeMenu, 1);

	auto fightButton = MenuItemImage::create("fight_button.jpg",
											   "fight_button.jpg",
											   CC_CALLBACK_1(MainScene::toFightMenu, this));
	fightButton->setPosition((Point(visibleSize.width / 10 , visibleSize.height / 9)));
	auto fightMenu = Menu::create(fightButton, NULL);
	fightMenu->setPosition(Vec2::ZERO);
	uiLayer->addChild(fightMenu, 1);

	this->addChild(baseLayer, 0);
	this->addChild(animationLayer, 1);
	this->addChild(hudLayer, 2);
	this->addChild(uiLayer, 3);

	return true;
}

void MainScene::update(float delta) {
    world.loopStart();
    world.setDelta(delta);
    movementSys->process();
    renderSys->process();
    
    //CCLOG("X: %f", comp->posX);
    //CCLOG("Y: %f", comp->posY);
}

void MainScene::toBuildMenu(Ref* pSender)
{
	//buildScene->setMainScene(this);
	auto buildScene2 = StoreScene::create();
	buildScene2->setMainScene(this);
	buildScene2->setUpBuiltItemNums(builtItemNumbers);
	buildScene2->setUpBuiltLocations(builtItemLocations);
	buildScene2->setUpPreviousBuiltItems();
	this->addChild(buildScene2, 5);
	//Director::getInstance()->replaceScene(buildScene2);
}

void MainScene::toFightMenu(Ref* pSender)
{
	auto combatScene = CombatScene::create();
	this->addChild(combatScene, 5);
}
void MainScene::toRecruitMenu(Ref* pSender)
{
	auto recruitScene = HeroScene::create();
	recruitScene->setMainScene(this);
	recruitScene->setBoughtHeroOne(boughtHeroOne);
	recruitScene->setBoughtHeroTwo(boughtHeroTwo);
	recruitScene->setBoughtHeroThree(boughtHeroThree);
	recruitScene->setBoughtHeroFour(boughtHeroFour);
	recruitScene->setBoughtHeroFive(boughtHeroFive);
	recruitScene->setBoughtHeroSix(boughtHeroSix);
	recruitScene->setUpPreviousBoughtItems();
	this->addChild(recruitScene, 5);
}

void MainScene::toUpgradeMenu(Ref* pSender)
{
	auto upgradeScene = UpgradeScene::create();
	upgradeScene->setMainScene(this);
	upgradeScene->setBoughtHeroOne(boughtHeroOne);
	upgradeScene->setBoughtHeroTwo(boughtHeroTwo);
	upgradeScene->setBoughtHeroThree(boughtHeroThree);
	upgradeScene->setBoughtHeroFour(boughtHeroFour);
	upgradeScene->setBoughtHeroFive(boughtHeroFive);
	upgradeScene->setBoughtHeroSix(boughtHeroSix);

	upgradeScene->setBoughtItemOne(boughtHoriWall);
	upgradeScene->setBoughtItemTwo(boughtVerWall);
	upgradeScene->setBoughtItemThree(boughtHoriPlasma);
	upgradeScene->setBoughtItemFour(boughtVerPlasma);
	upgradeScene->setBoughtItemFive(boughtStarDustTree);
	upgradeScene->setBoughtItemSix(boughtGalacticStone);

	upgradeScene->setHeroOneRank(warriorRank);
	upgradeScene->setHeroTwoRank(spaceRangerRank);
	upgradeScene->setHeroThreeRank(scoutRank);
	upgradeScene->setHeroFourRank(clericRank);
	upgradeScene->setHeroFiveRank(assassinRank);
	upgradeScene->setHeroSixRank(mageRank);

	upgradeScene->setHeroOneHealth(warriorHealth);
	upgradeScene->setHeroTwoHealth(spaceRangerHealth);
	upgradeScene->setHeroThreeHealth(scoutHealth);
	upgradeScene->setHeroFourHealth(clericHealth);
	upgradeScene->setHeroFiveHealth(assassinHealth);
	upgradeScene->setHeroSixHealth(mageHealth);

	upgradeScene->setHeroOneAttack(warriorAttack);
	upgradeScene->setHeroTwoAttack(spaceRangerAttack);
	upgradeScene->setHeroThreeAttack(scoutAttack);
	upgradeScene->setHeroFourAttack(clericAttack);
	upgradeScene->setHeroFiveAttack(assassinAttack);
	upgradeScene->setHeroSixAttack(mageAttack);

	upgradeScene->setItemOneRank(horiWallRank);
	upgradeScene->setItemTwoRank(verWallRank);
	upgradeScene->setItemThreeRank(horiPlasmaRank);
	upgradeScene->setItemFourRank(verPlasmaRank);
	upgradeScene->setItemFiveRank(starDustTreeRank);
	upgradeScene->setItemSixRank(galacticStoneRank);

	upgradeScene->setItemOneHealth(horiWallHealth);
	upgradeScene->setItemTwoHealth(verWallHealth);
	upgradeScene->setItemThreeHealth(horiPlasmaHealth);
	upgradeScene->setItemFourHealth(verPlasmaHealth);
	upgradeScene->setItemFiveHealth(starDustTreeHealth);
	upgradeScene->setItemSixHealth(galacticStoneHealth);

	this->addChild(upgradeScene, 5);
}

vector<int> MainScene::getItemNumbers()
{
	return builtItemNumbers;
}

vector<Vec2> MainScene::getLocations()
{
	return builtItemLocations;
}

void MainScene::setItemNumbers(vector<int> itemNums)
{
	builtItemNumbers = itemNums;
}

void MainScene::setLocations(vector<Vec2> locations)
{
	builtItemLocations = locations;
}

void MainScene::setBoughtItemOne(bool item)
{
	boughtHoriWall = item;
}

void MainScene::setBoughtItemTwo(bool item)
{
	boughtVerWall = item;
}

void MainScene::setBoughtItemThree(bool item)
{
	boughtHoriPlasma = item;
}

void MainScene::setBoughtItemFour(bool item)
{
	boughtVerPlasma = item;
}

void MainScene::setBoughtItemFive(bool item)
{
	boughtStarDustTree = item;
}

void MainScene::setBoughtItemSix(bool item)
{
	boughtGalacticStone = item;
}

void MainScene::setBoughtHeroOne(bool hero)
{
	boughtHeroOne = hero;
}

void MainScene::setBoughtHeroTwo(bool hero)
{
	boughtHeroTwo = hero;
}

void MainScene::setBoughtHeroThree(bool hero)
{
	boughtHeroThree = hero;
}

void MainScene::setBoughtHeroFour(bool hero)
{
	boughtHeroFour = hero;
}

void MainScene::setBoughtHeroFive(bool hero)
{
	boughtHeroFive = hero;
}

void MainScene::setBoughtHeroSix(bool hero)
{
	boughtHeroSix = hero;
}

void MainScene::setHeroOneRank(int rank)
{
	warriorRank = rank;
}
void MainScene::setHeroTwoRank(int rank)
{
	spaceRangerRank = rank;
}
void MainScene::setHeroThreeRank(int rank)
{
	scoutRank = rank;
}
void MainScene::setHeroFourRank(int rank)
{
	clericRank = rank;
}
void MainScene::setHeroFiveRank(int rank)
{
	assassinRank = rank;
}
void MainScene::setHeroSixRank(int rank)
{
	mageRank = rank;
}

void MainScene::setHeroOneAttack(string attack)
{
	warriorAttack = attack;
}
void MainScene::setHeroTwoAttack(string attack)
{
	spaceRangerAttack = attack;
}
void MainScene::setHeroThreeAttack(string attack)
{
	scoutAttack = attack;
}
void MainScene::setHeroFourAttack(string attack)
{
	clericAttack = attack;
}
void MainScene::setHeroFiveAttack(string attack)
{
	assassinAttack = attack;
}
void MainScene::setHeroSixAttack(string attack)
{
	mageAttack = attack;
}

void MainScene::setHeroOneHealth(string health)
{
	warriorHealth = health;
}
void MainScene::setHeroTwoHealth(string health)
{
	spaceRangerHealth = health;
}
void MainScene::setHeroThreeHealth(string health)
{
	scoutHealth = health;
}
void MainScene::setHeroFourHealth(string health)
{
	clericHealth = health;
}
void MainScene::setHeroFiveHealth(string health)
{
	assassinHealth = health;
}
void MainScene::setHeroSixHealth(string health)
{
	mageHealth = health;
}

void MainScene::setItemOneRank(int rank)
{
	horiWallRank = rank;
}
void MainScene::setItemTwoRank(int rank)
{
	verWallRank = rank;
}
void MainScene::setItemThreeRank(int rank)
{
	horiPlasmaRank = rank;
}
void MainScene::setItemFourRank(int rank)
{
	verPlasmaRank = rank;
}
void MainScene::setItemFiveRank(int rank)
{
	starDustTreeRank = rank;
}
void MainScene::setItemSixRank(int rank)
{
	galacticStoneRank = rank;
}

void MainScene::setItemOneHealth(string health)
{
	horiWallHealth = health;
}
void MainScene::setItemTwoHealth(string health)
{
	verWallHealth = health;
}
void MainScene::setItemThreeHealth(string health)
{
	horiPlasmaHealth = health;
}
void MainScene::setItemFourHealth(string health)
{
	verPlasmaHealth = health;
}
void MainScene::setItemFiveHealth(string health)
{
	starDustTreeHealth = health;
}
void MainScene::setItemSixHealth(string health)
{
	galacticStoneHealth = health;
}

void MainScene::buildTheItems()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	for(int i = 0; i < builtItemNumbers.size(); i++)
	{
		if(builtItemNumbers.at(i) == 1)
		{
			auto firstItem = Sprite::create("star.png");
			firstItem->setPosition(builtItemLocations.at(i));
			this->addChild(firstItem, 1);
		}
		else if(builtItemNumbers.at(i) == 2)
		{
			auto secondItem = Sprite::create("star.png");
			secondItem->setPosition(builtItemLocations.at(i));
			this->addChild(secondItem, 1);
		}
		else if(builtItemNumbers.at(i) == 3)
		{
			auto thirdItem = Sprite::create("star.png");
			thirdItem->setPosition(builtItemLocations.at(i));
			this->addChild(thirdItem, 1);
		}
		else if(builtItemNumbers.at(i) == 4)
		{
			auto fourthItem = Sprite::create("star.png");
			fourthItem->setPosition(builtItemLocations.at(i));
			this->addChild(fourthItem, 1);
		}
		else if(builtItemNumbers.at(i) == 5)
		{
			auto fifthItem = Sprite::create("star.png");
			fifthItem->setPosition(builtItemLocations.at(i));
			this->addChild(fifthItem, 1);
		}
		else if(builtItemNumbers.at(i) == 6)
		{
			auto sixthItem = Sprite::create("star.png");
			sixthItem->setPosition(builtItemLocations.at(i));
			this->addChild(sixthItem, 1);
		}
	}

}

