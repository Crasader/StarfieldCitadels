/*
 * UpgradeScene.cpp
 *
 *  Created on: March 31, 2015
 *      Author: Kristen Ernst
 */

#include "UpgradeScene.h"

Scene * UpgradeScene::createScene()
{
    auto scene = UpgradeScene::create();

    return scene;
}


bool UpgradeScene::init()
{
    // Call super init first
    if(!Scene::init())
    {
        return false;
    }

    boughtWarrior = false;
	boughtSpaceRanger = false;
	boughtScout = false;
	boughtCleric = false;
	boughtAssassin = false;
	boughtMage = false;

	boughtHoriWall = false;
	boughtVerWall = false;
	boughtHoriPlasma = false;
	boughtVerPlasma = false;
	boughtStarDustTree = false;
	boughtGalacticStone = false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Generate Scene layers
    baseLayer = BaseLayer::create();
    baseLayer->setName("BaseLayer");

    animationLayer = AnimationLayer::create();
    animationLayer->setName("AnimationLayer");

    hudLayer = HUDLayer::create();
    hudLayer->setName("HUDLayer");

    uiLayer = UILayer::create();
    uiLayer->setName("UILayer");

    auto backDrop = MenuItemImage::create("space.jpg",
											   "space.jpg",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(89);
	baseLayer->addChild(backDropLayer);

	auto exitButton = MenuItemImage::create("exit_button.png",
											   "exit_button.png",
											   CC_CALLBACK_1(UpgradeScene::loadMainView, this));

	exitButton->setPosition((Point(visibleSize.width - (visibleSize.width / 10), visibleSize.height - (visibleSize.height/10))));
	auto exitMenu = Menu::create(exitButton, NULL);
	exitMenu->setPosition(Vec2::ZERO);
	uiLayer->addChild(exitMenu);

	auto label = Label::createWithTTF("Upgrade", "fonts/Marker Felt.ttf", 40);
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
								origin.y + visibleSize.height - (visibleSize.height / 7)));
	hudLayer->addChild(label);

	auto soldiersTab = MenuItemImage::create("upgrade_soldiers_tab.png",
													   "upgrade_soldiers_tab.png",
													   CC_CALLBACK_1(UpgradeScene::doNothing, this));    // position the label on the center of the screen

	soldiersTab->setPosition((Point(visibleSize.width / 4 , visibleSize.height / 1.4)));

	auto soldiersTabMenu = Menu::create(soldiersTab, NULL);
	soldiersTabMenu->setPosition(Vec2::ZERO);
	soldiersTabMenu->setTag(64);
	uiLayer->addChild(soldiersTabMenu);

	auto citadelTab = MenuItemImage::create("upgrade_soldiers_tab.png",
													   "upgrade_soldiers_tab.png",
													   CC_CALLBACK_1(UpgradeScene::toUpgradeCitadel, this));    // position the label on the center of the screen

	citadelTab->setPosition((Point((visibleSize.width / 4) * 3 , visibleSize.height / 1.4)));

	auto citadelTabMenu = Menu::create(citadelTab, NULL);
	citadelTabMenu->setPosition(Vec2::ZERO);
	citadelTabMenu->setTag(65);
	uiLayer->addChild(citadelTabMenu);

	auto soldierTitle = Label::createWithTTF("Soldiers", "fonts/Marker Felt.ttf", 18);
	soldierTitle->setPosition((Point(visibleSize.width / 4 , visibleSize.height / 1.4)));
	soldierTitle->setTag(94);
	uiLayer->addChild(soldierTitle);

	auto citadelTitle = Label::createWithTTF("Citadel", "fonts/Marker Felt.ttf", 18);
	citadelTitle->setPosition((Point((visibleSize.width / 4) * 3 , visibleSize.height / 1.4)));
	citadelTitle->setTag(95);
	uiLayer->addChild(citadelTitle);

	auto firstUpgrade = MenuItemImage::create("upgrade_the_soldier.png",
													   "upgrade_the_soldier.png",
													   CC_CALLBACK_1(UpgradeScene::upgradeFirstSoldier, this));    // position the label on the center of the screen

	firstUpgrade->setPosition((Point(visibleSize.width / 4.3, visibleSize.height / 2)));

	auto firstUpgradeMenu = Menu::create(firstUpgrade, NULL);
	firstUpgradeMenu->setPosition(Vec2::ZERO);
	firstUpgradeMenu->setTag(66);
	uiLayer->addChild(firstUpgradeMenu);

	auto secondUpgrade = MenuItemImage::create("upgrade_the_soldier.png",
													   "upgrade_the_soldier.png",
													   CC_CALLBACK_1(UpgradeScene::upgradeSecondSoldier, this));    // position the label on the center of the screen

	secondUpgrade->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));

	auto secondUpgradeMenu = Menu::create(secondUpgrade, NULL);
	secondUpgradeMenu->setPosition(Vec2::ZERO);
	secondUpgradeMenu->setTag(67);
	uiLayer->addChild(secondUpgradeMenu);

	auto thirdUpgrade = MenuItemImage::create("upgrade_the_soldier.png",
													   "upgrade_the_soldier.png",
													   CC_CALLBACK_1(UpgradeScene::upgradeThirdSoldier, this));    // position the label on the center of the screen

	thirdUpgrade->setPosition((Point((visibleSize.width / 4) * 3.1, visibleSize.height / 2)));

	auto thirdUpgradeMenu = Menu::create(thirdUpgrade, NULL);
	thirdUpgradeMenu->setPosition(Vec2::ZERO);
	thirdUpgradeMenu->setTag(68);
	uiLayer->addChild(thirdUpgradeMenu);

	auto fourthUpgrade = MenuItemImage::create("upgrade_the_soldier.png",
													   "upgrade_the_soldier.png",
													   CC_CALLBACK_1(UpgradeScene::upgradeFourthSoldier, this));    // position the label on the center of the screen

	fourthUpgrade->setPosition((Point(visibleSize.width / 4.3, visibleSize.height / 4)));

	auto fourthUpgradeMenu = Menu::create(fourthUpgrade, NULL);
	fourthUpgradeMenu->setPosition(Vec2::ZERO);
	fourthUpgradeMenu->setTag(69);
	uiLayer->addChild(fourthUpgradeMenu);

	auto fifthUpgrade = MenuItemImage::create("upgrade_the_soldier.png",
													   "upgrade_the_soldier.png",
													   CC_CALLBACK_1(UpgradeScene::upgradeFifthSoldier, this));    // position the label on the center of the screen

	fifthUpgrade->setPosition((Point(visibleSize.width / 2, visibleSize.height / 4)));

	auto fifthUpgradeMenu = Menu::create(fifthUpgrade, NULL);
	fifthUpgradeMenu->setPosition(Vec2::ZERO);
	fifthUpgradeMenu->setTag(70);
	uiLayer->addChild(fifthUpgradeMenu);

	auto sixthUpgrade = MenuItemImage::create("upgrade_the_soldier.png",
													   "upgrade_the_soldier.png",
													   CC_CALLBACK_1(UpgradeScene::upgradeSixthSoldier, this));    // position the label on the center of the screen

	sixthUpgrade->setPosition((Point((visibleSize.width / 4) * 3.1, visibleSize.height / 4)));

	auto sixthUpgradeMenu = Menu::create(sixthUpgrade, NULL);
	sixthUpgradeMenu->setPosition(Vec2::ZERO);
	sixthUpgradeMenu->setTag(71);
	uiLayer->addChild(sixthUpgradeMenu);

	this->addChild(baseLayer, 0);
	this->addChild(animationLayer, 1);
	this->addChild(hudLayer, 2);
	this->addChild(uiLayer, 3);

	return true;
}

void UpgradeScene::cancelFromUpgrade(Ref* pSender)
{
	uiLayer->removeChildByTag(50,1);
	uiLayer->removeChildByTag(51,1);
	uiLayer->removeChildByTag(52,1);
	uiLayer->removeChildByTag(53,1);
	uiLayer->removeChildByTag(54,1);
	uiLayer->removeChildByTag(55,1);
	uiLayer->removeChildByTag(56,1);
	uiLayer->removeChildByTag(57,1);
	uiLayer->removeChildByTag(58,1);
}

void UpgradeScene::cancelFromPurchase(Ref* pSender)
{
	uiLayer->removeChildByTag(36,1);
	uiLayer->removeChildByTag(37,1);
	uiLayer->removeChildByTag(38,1);
	uiLayer->removeChildByTag(39,1);
}

void UpgradeScene::toUpgradeMenu(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	uiLayer->removeChildByTag(64,1);
	uiLayer->removeChildByTag(65,1);
	uiLayer->removeChildByTag(66,1);
	uiLayer->removeChildByTag(67,1);
	uiLayer->removeChildByTag(68,1);
	uiLayer->removeChildByTag(69,1);
	uiLayer->removeChildByTag(70,1);
	uiLayer->removeChildByTag(71,1);
	uiLayer->removeChildByTag(94,1);
	uiLayer->removeChildByTag(95,1);

	auto soldiersTab = MenuItemImage::create("upgrade_soldiers_tab.png",
													   "upgrade_soldiers_tab.png",
													   CC_CALLBACK_1(UpgradeScene::doNothing, this));    // position the label on the center of the screen

	soldiersTab->setPosition((Point(visibleSize.width / 4 , visibleSize.height / 1.4)));

	auto soldiersTabMenu = Menu::create(soldiersTab, NULL);
	soldiersTabMenu->setPosition(Vec2::ZERO);
	soldiersTabMenu->setTag(64);
	uiLayer->addChild(soldiersTabMenu);

	auto citadelTab = MenuItemImage::create("upgrade_soldiers_tab.png",
													   "upgrade_soldiers_tab.png",
													   CC_CALLBACK_1(UpgradeScene::toUpgradeCitadel, this));    // position the label on the center of the screen

	citadelTab->setPosition((Point((visibleSize.width / 4) * 3 , visibleSize.height / 1.4)));

	auto citadelTabMenu = Menu::create(citadelTab, NULL);
	citadelTabMenu->setPosition(Vec2::ZERO);
	citadelTabMenu->setTag(65);
	uiLayer->addChild(citadelTabMenu);

	auto soldierTitle = Label::createWithTTF("Soldiers", "fonts/Marker Felt.ttf", 18);
	soldierTitle->setPosition((Point(visibleSize.width / 4 , visibleSize.height / 1.4)));
	soldierTitle->setTag(94);
	uiLayer->addChild(soldierTitle);

	auto citadelTitle = Label::createWithTTF("Citadel", "fonts/Marker Felt.ttf", 18);
	citadelTitle->setPosition((Point((visibleSize.width / 4) * 3 , visibleSize.height / 1.4)));
	citadelTitle->setTag(95);
	uiLayer->addChild(citadelTitle);

	auto firstUpgrade = MenuItemImage::create("upgrade_the_soldier.png",
													   "upgrade_the_soldier.png",
													   CC_CALLBACK_1(UpgradeScene::upgradeFirstSoldier, this));    // position the label on the center of the screen

	firstUpgrade->setPosition((Point(visibleSize.width / 4.3, visibleSize.height / 2)));

	auto firstUpgradeMenu = Menu::create(firstUpgrade, NULL);
	firstUpgradeMenu->setPosition(Vec2::ZERO);
	firstUpgradeMenu->setTag(66);
	uiLayer->addChild(firstUpgradeMenu);

	auto secondUpgrade = MenuItemImage::create("upgrade_the_soldier.png",
													   "upgrade_the_soldier.png",
													   CC_CALLBACK_1(UpgradeScene::upgradeSecondSoldier, this));    // position the label on the center of the screen

	secondUpgrade->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));

	auto secondUpgradeMenu = Menu::create(secondUpgrade, NULL);
	secondUpgradeMenu->setPosition(Vec2::ZERO);
	secondUpgradeMenu->setTag(67);
	uiLayer->addChild(secondUpgradeMenu);

	auto thirdUpgrade = MenuItemImage::create("upgrade_the_soldier.png",
													   "upgrade_the_soldier.png",
													   CC_CALLBACK_1(UpgradeScene::upgradeThirdSoldier, this));    // position the label on the center of the screen

	thirdUpgrade->setPosition((Point((visibleSize.width / 4) * 3.1, visibleSize.height / 2)));

	auto thirdUpgradeMenu = Menu::create(thirdUpgrade, NULL);
	thirdUpgradeMenu->setPosition(Vec2::ZERO);
	thirdUpgradeMenu->setTag(68);
	uiLayer->addChild(thirdUpgradeMenu);

	auto fourthUpgrade = MenuItemImage::create("upgrade_the_soldier.png",
													   "upgrade_the_soldier.png",
													   CC_CALLBACK_1(UpgradeScene::upgradeFourthSoldier, this));    // position the label on the center of the screen

	fourthUpgrade->setPosition((Point(visibleSize.width / 4.3, visibleSize.height / 4)));

	auto fourthUpgradeMenu = Menu::create(fourthUpgrade, NULL);
	fourthUpgradeMenu->setPosition(Vec2::ZERO);
	fourthUpgradeMenu->setTag(69);
	uiLayer->addChild(fourthUpgradeMenu);

	auto fifthUpgrade = MenuItemImage::create("upgrade_the_soldier.png",
													   "upgrade_the_soldier.png",
													   CC_CALLBACK_1(UpgradeScene::upgradeFifthSoldier, this));    // position the label on the center of the screen

	fifthUpgrade->setPosition((Point(visibleSize.width / 2, visibleSize.height / 4)));

	auto fifthUpgradeMenu = Menu::create(fifthUpgrade, NULL);
	fifthUpgradeMenu->setPosition(Vec2::ZERO);
	fifthUpgradeMenu->setTag(70);
	uiLayer->addChild(fifthUpgradeMenu);

	auto sixthUpgrade = MenuItemImage::create("upgrade_the_soldier.png",
													   "upgrade_the_soldier.png",
													   CC_CALLBACK_1(UpgradeScene::upgradeSixthSoldier, this));    // position the label on the center of the screen

	sixthUpgrade->setPosition((Point((visibleSize.width / 4) * 3.1, visibleSize.height / 4)));

	auto sixthUpgradeMenu = Menu::create(sixthUpgrade, NULL);
	sixthUpgradeMenu->setPosition(Vec2::ZERO);
	sixthUpgradeMenu->setTag(71);
	uiLayer->addChild(sixthUpgradeMenu);
}

void UpgradeScene::toUpgradeCitadel(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	uiLayer->removeChildByTag(64,1);
	uiLayer->removeChildByTag(65,1);
	uiLayer->removeChildByTag(66,1);
	uiLayer->removeChildByTag(67,1);
	uiLayer->removeChildByTag(68,1);
	uiLayer->removeChildByTag(69,1);
	uiLayer->removeChildByTag(70,1);
	uiLayer->removeChildByTag(71,1);
	uiLayer->removeChildByTag(94,1);
	uiLayer->removeChildByTag(95,1);


	auto soldiersTab = MenuItemImage::create("upgrade_soldiers_tab.png",
														   "upgrade_soldiers_tab.png",
														   CC_CALLBACK_1(UpgradeScene::toUpgradeMenu, this));    // position the label on the center of the screen

	soldiersTab->setPosition((Point(visibleSize.width / 4 , visibleSize.height / 1.4)));

	auto soldiersTabMenu = Menu::create(soldiersTab, NULL);
	soldiersTabMenu->setPosition(Vec2::ZERO);
	soldiersTabMenu->setTag(64);
	uiLayer->addChild(soldiersTabMenu);

	auto citadelTab = MenuItemImage::create("upgrade_soldiers_tab.png",
													   "upgrade_soldiers_tab.png",
													   CC_CALLBACK_1(UpgradeScene::doNothing, this));    // position the label on the center of the screen

	citadelTab->setPosition((Point((visibleSize.width / 4) * 3 , visibleSize.height / 1.4)));

	auto citadelTabMenu = Menu::create(citadelTab, NULL);
	citadelTabMenu->setPosition(Vec2::ZERO);
	citadelTabMenu->setTag(65);
	uiLayer->addChild(citadelTabMenu);

	auto soldierTitle = Label::createWithTTF("Soldiers", "fonts/Marker Felt.ttf", 18);
	soldierTitle->setPosition((Point(visibleSize.width / 4 , visibleSize.height / 1.4)));
	soldierTitle->setTag(94);
	uiLayer->addChild(soldierTitle);

	auto citadelTitle = Label::createWithTTF("Citadel", "fonts/Marker Felt.ttf", 18);
	citadelTitle->setPosition((Point((visibleSize.width / 4) * 3 , visibleSize.height / 1.4)));
	citadelTitle->setTag(95);
	uiLayer->addChild(citadelTitle);

	auto firstUpgrade = MenuItemImage::create("upgrade_the_soldier.png",
													   "upgrade_the_soldier.png",
													   CC_CALLBACK_1(UpgradeScene::upgradeFirstBuiltItem, this));    // position the label on the center of the screen

	firstUpgrade->setPosition((Point(visibleSize.width / 4.3, visibleSize.height / 2)));

	auto firstUpgradeMenu = Menu::create(firstUpgrade, NULL);
	firstUpgradeMenu->setPosition(Vec2::ZERO);
	firstUpgradeMenu->setTag(66);
	uiLayer->addChild(firstUpgradeMenu);

	auto secondUpgrade = MenuItemImage::create("upgrade_the_soldier.png",
													   "upgrade_the_soldier.png",
													   CC_CALLBACK_1(UpgradeScene::upgradeSecondBuiltItem, this));    // position the label on the center of the screen

	secondUpgrade->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));

	auto secondUpgradeMenu = Menu::create(secondUpgrade, NULL);
	secondUpgradeMenu->setPosition(Vec2::ZERO);
	secondUpgradeMenu->setTag(67);
	uiLayer->addChild(secondUpgradeMenu);

	auto thirdUpgrade = MenuItemImage::create("upgrade_the_soldier.png",
													   "upgrade_the_soldier.png",
													   CC_CALLBACK_1(UpgradeScene::upgradeThirdBuiltItem, this));    // position the label on the center of the screen

	thirdUpgrade->setPosition((Point((visibleSize.width / 4) * 3.1, visibleSize.height / 2)));

	auto thirdUpgradeMenu = Menu::create(thirdUpgrade, NULL);
	thirdUpgradeMenu->setPosition(Vec2::ZERO);
	thirdUpgradeMenu->setTag(68);
	uiLayer->addChild(thirdUpgradeMenu);

	auto fourthUpgrade = MenuItemImage::create("upgrade_the_soldier.png",
													   "upgrade_the_soldier.png",
													   CC_CALLBACK_1(UpgradeScene::upgradeFourthBuiltItem, this));    // position the label on the center of the screen

	fourthUpgrade->setPosition((Point(visibleSize.width / 4.3, visibleSize.height / 4)));

	auto fourthUpgradeMenu = Menu::create(fourthUpgrade, NULL);
	fourthUpgradeMenu->setPosition(Vec2::ZERO);
	fourthUpgradeMenu->setTag(69);
	uiLayer->addChild(fourthUpgradeMenu);

	auto fifthUpgrade = MenuItemImage::create("upgrade_the_soldier.png",
													   "upgrade_the_soldier.png",
													   CC_CALLBACK_1(UpgradeScene::upgradeFifthBuiltItem, this));    // position the label on the center of the screen

	fifthUpgrade->setPosition((Point(visibleSize.width / 2, visibleSize.height / 4)));

	auto fifthUpgradeMenu = Menu::create(fifthUpgrade, NULL);
	fifthUpgradeMenu->setPosition(Vec2::ZERO);
	fifthUpgradeMenu->setTag(70);
	uiLayer->addChild(fifthUpgradeMenu);

	auto sixthUpgrade = MenuItemImage::create("upgrade_the_soldier.png",
													   "upgrade_the_soldier.png",
													   CC_CALLBACK_1(UpgradeScene::upgradeSixthBuiltItem, this));    // position the label on the center of the screen

	sixthUpgrade->setPosition((Point((visibleSize.width / 4) * 3.1, visibleSize.height / 4)));

	auto sixthUpgradeMenu = Menu::create(sixthUpgrade, NULL);
	sixthUpgradeMenu->setPosition(Vec2::ZERO);
	sixthUpgradeMenu->setTag(71);
	uiLayer->addChild(sixthUpgradeMenu);
}

void UpgradeScene::cancelFromConfirmUpgrade(Ref* pSender)
{
	uiLayer->removeChildByTag(59,1);
	uiLayer->removeChildByTag(60,1);
	uiLayer->removeChildByTag(61,1);
	uiLayer->removeChildByTag(62,1);
	uiLayer->removeChildByTag(63,1);
	uiLayer->removeChildByTag(34,1);
	uiLayer->removeChildByTag(35,1);
}

int UpgradeScene::getCostForSoldierRank(int rank)
{
	if(rank == 0)
	{
		return 1000;
	}
	else if(rank == 1)
	{
		return 2000;
	}
	else if(rank == 2)
	{
		return 3000;
	}
	else
	{
		return 5000;
	}
}

int UpgradeScene::getCostForItemRank(int rank)
{
	if(rank == 0)
	{
		return 700;
	}
	else if(rank == 1)
	{
		return 1600;
	}
	else if(rank == 2)
	{
		return 2400;
	}
	else
	{
		return 4100;
	}
}

void UpgradeScene::setMoneyTotal(int money)
{
	moneyTotal = money;
}

void UpgradeScene::setBoughtHeroOne(bool hero)
{
	boughtWarrior = hero;
}

void UpgradeScene::setBoughtHeroTwo(bool hero)
{
	boughtSpaceRanger = hero;
}

void UpgradeScene::setBoughtHeroThree(bool hero)
{
	boughtScout = hero;
}

void UpgradeScene::setBoughtHeroFour(bool hero)
{
	boughtCleric = hero;
}

void UpgradeScene::setBoughtHeroFive(bool hero)
{
	boughtAssassin = hero;
}

void UpgradeScene::setBoughtHeroSix(bool hero)
{
	boughtMage = hero;
}

void UpgradeScene::setBoughtItemOne(bool item)
{
	boughtHoriWall = item;
}

void UpgradeScene::setBoughtItemTwo(bool item)
{
	boughtVerWall = item;
}

void UpgradeScene::setBoughtItemThree(bool item)
{
	boughtHoriPlasma = item;
}

void UpgradeScene::setBoughtItemFour(bool item)
{
	boughtVerPlasma = item;
}

void UpgradeScene::setBoughtItemFive(bool item)
{
	boughtStarDustTree = item;
}

void UpgradeScene::setBoughtItemSix(bool item)
{
	boughtGalacticStone = item;
}

void UpgradeScene::setHeroOneRank(int rank)
{
	warriorRank = rank;
}
void UpgradeScene::setHeroTwoRank(int rank)
{
	spaceRangerRank = rank;
}
void UpgradeScene::setHeroThreeRank(int rank)
{
	scoutRank = rank;
}
void UpgradeScene::setHeroFourRank(int rank)
{
	clericRank = rank;
}
void UpgradeScene::setHeroFiveRank(int rank)
{
	assassinRank = rank;
}
void UpgradeScene::setHeroSixRank(int rank)
{
	mageRank = rank;
}

void UpgradeScene::setHeroOneAttack(string attack)
{
	warriorAttack = attack;
}
void UpgradeScene::setHeroTwoAttack(string attack)
{
	spaceRangerAttack = attack;
}
void UpgradeScene::setHeroThreeAttack(string attack)
{
	scoutAttack = attack;
}
void UpgradeScene::setHeroFourAttack(string attack)
{
	clericAttack = attack;
}
void UpgradeScene::setHeroFiveAttack(string attack)
{
	assassinAttack = attack;
}
void UpgradeScene::setHeroSixAttack(string attack)
{
	mageAttack = attack;
}

void UpgradeScene::setHeroOneHealth(string health)
{
	warriorHealth = health;
}
void UpgradeScene::setHeroTwoHealth(string health)
{
	spaceRangerHealth = health;
}
void UpgradeScene::setHeroThreeHealth(string health)
{
	scoutHealth = health;
}
void UpgradeScene::setHeroFourHealth(string health)
{
	clericHealth = health;
}
void UpgradeScene::setHeroFiveHealth(string health)
{
	assassinHealth = health;
}
void UpgradeScene::setHeroSixHealth(string health)
{
	mageHealth = health;
}

void UpgradeScene::setItemOneRank(int rank)
{
	horiWallRank = rank;
}
void UpgradeScene::setItemTwoRank(int rank)
{
	verWallRank = rank;
}
void UpgradeScene::setItemThreeRank(int rank)
{
	horiPlasmaRank = rank;
}
void UpgradeScene::setItemFourRank(int rank)
{
	verPlasmaRank = rank;
}
void UpgradeScene::setItemFiveRank(int rank)
{
	starDustTreeRank = rank;
}
void UpgradeScene::setItemSixRank(int rank)
{
	galacticStoneRank = rank;
}

void UpgradeScene::setItemOneHealth(string health)
{
	horiWallHealth = health;
}
void UpgradeScene::setItemTwoHealth(string health)
{
	verWallHealth = health;
}
void UpgradeScene::setItemThreeHealth(string health)
{
	horiPlasmaHealth = health;
}
void UpgradeScene::setItemFourHealth(string health)
{
	verPlasmaHealth = health;
}
void UpgradeScene::setItemFiveHealth(string health)
{
	starDustTreeHealth = health;
}
void UpgradeScene::setItemSixHealth(string health)
{
	galacticStoneHealth = health;
}

void UpgradeScene::setMainScene(MainScene* scene)
{
	mainScene = scene;
}

void UpgradeScene::doNothing(Ref* pSender)
{
}

void UpgradeScene::loadMainView(Ref* pSender)
{
	mainScene->setHeroOneRank(warriorRank);
	mainScene->setHeroTwoRank(spaceRangerRank);
	mainScene->setHeroThreeRank(scoutRank);
	mainScene->setHeroFourRank(clericRank);
	mainScene->setHeroFiveRank(assassinRank);
	mainScene->setHeroSixRank(mageRank);

	mainScene->setHeroOneHealth(warriorHealth);
	mainScene->setHeroTwoHealth(spaceRangerHealth);
	mainScene->setHeroThreeHealth(scoutHealth);
	mainScene->setHeroFourHealth(clericHealth);
	mainScene->setHeroFiveHealth(assassinHealth);
	mainScene->setHeroSixHealth(mageHealth);

	mainScene->setHeroOneAttack(warriorAttack);
	mainScene->setHeroTwoAttack(spaceRangerAttack);
	mainScene->setHeroThreeAttack(scoutAttack);
	mainScene->setHeroFourAttack(clericAttack);
	mainScene->setHeroFiveAttack(assassinAttack);
	mainScene->setHeroSixAttack(mageAttack);

	mainScene->setItemOneRank(horiWallRank);
	mainScene->setItemTwoRank(verWallRank);
	mainScene->setItemThreeRank(horiPlasmaRank);
	mainScene->setItemFourRank(verPlasmaRank);
	mainScene->setItemFiveRank(starDustTreeRank);
	mainScene->setItemSixRank(galacticStoneRank);

	mainScene->setItemOneHealth(horiWallHealth);
	mainScene->setItemTwoHealth(verWallHealth);
	mainScene->setItemThreeHealth(horiPlasmaHealth);
	mainScene->setItemFourHealth(verPlasmaHealth);
	mainScene->setItemFiveHealth(starDustTreeHealth);
	mainScene->setItemSixHealth(galacticStoneHealth);

	mainScene->setMoneyTotal(moneyTotal);
	mainScene->repostMoneyTotal();
	this->removeAllChildren();
}

void UpgradeScene::upgradeFirstSoldier(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(50);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(51);
	uiLayer->addChild(popup);

	auto soldierPic = Sprite::create("first_soldier_upgrade.jpg");
	soldierPic->setPosition((Point(visibleSize.width / 2.8, visibleSize.height / 2)));
	soldierPic->setTag(52);
	uiLayer->addChild(soldierPic);

	auto label = Label::createWithTTF("Warrior", "fonts/Marker Felt.ttf", 18);
	label->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 1.6)));
	label->setTag(53);
	uiLayer->addChild(label);

	if (warriorRank == 0)
	{
		auto stars = Sprite::create("emptyStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (warriorRank == 1)
	{
		auto stars = Sprite::create("oneStar.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (warriorRank == 2)
	{
		auto stars = Sprite::create("twoStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (warriorRank == 3)
	{
		auto stars = Sprite::create("threeStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (warriorRank == 4)
	{
		auto stars = Sprite::create("fourStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}

	auto health = Label::createWithTTF("HP:  " + warriorHealth, "fonts/Marker Felt.ttf", 14);
	health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	health->setTag(55);
	uiLayer->addChild(health);

	auto attack = Label::createWithTTF("Atk:  " + warriorAttack, "fonts/Marker Felt.ttf", 14);
	attack->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.2)));
	attack->setTag(56);
	uiLayer->addChild(attack);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.55, visibleSize.height / 2.7)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(57);
	uiLayer->addChild(cancelButtonMenu);

	if (warriorRank < 4)
	{
		auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
												   "upgrade_soldier.jpg",
												   CC_CALLBACK_1(UpgradeScene::confirmFirstUpgrade, this));

		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
		upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
		upgradeTheSoldierMenu->setTag(58);
		uiLayer->addChild(upgradeTheSoldierMenu);
	}
	else
	{
		auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		upgradeTheSoldier->setTag(58);
		uiLayer->addChild(upgradeTheSoldier);
	}
}

void UpgradeScene::confirmFirstUpgrade(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto backDrop = MenuItemImage::create("blockOut_Content2.png",
											   "blockOut_Content2.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(59);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_upgrade_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(60);
	uiLayer->addChild(popup);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromConfirmUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(61);
	uiLayer->addChild(cancelButtonMenu);


	auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
											   "upgrade_soldier.jpg",
											   CC_CALLBACK_1(UpgradeScene::upgradeFirstStats, this));

	upgradeTheSoldier->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
	upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
	upgradeTheSoldierMenu->setTag(62);
	uiLayer->addChild(upgradeTheSoldierMenu);

	auto label = Label::createWithTTF("Upgrade the Warrior?", "fonts/Marker Felt.ttf", 12);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(63);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.jpg");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int upgradeCost = getCostForSoldierRank(warriorRank);
	sprintf(money,"%d", upgradeCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void UpgradeScene::upgradeFirstStats(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int costOfUpgrade = getCostForSoldierRank(warriorRank);
	if (moneyTotal >= costOfUpgrade)
	{
		moneyTotal = moneyTotal - costOfUpgrade;
		uiLayer->removeChildByTag(54,1);
		uiLayer->removeChildByTag(55,1);
		uiLayer->removeChildByTag(56,1);
		uiLayer->removeChildByTag(58,1);
		uiLayer->removeChildByTag(59,1);
		uiLayer->removeChildByTag(60,1);
		uiLayer->removeChildByTag(61,1);
		uiLayer->removeChildByTag(62,1);
		uiLayer->removeChildByTag(63,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		warriorRank = warriorRank + 1;

		if (warriorRank == 1)
		{
			warriorHealth = "240";
			warriorAttack = "20";
		}
		else if (warriorRank == 2)
		{
			warriorHealth = "280";
			warriorAttack = "25";
		}
		else if (warriorRank == 3)
		{
			warriorHealth = "350";
			warriorAttack = "27";
		}
		else if (warriorRank == 4)
		{
			warriorHealth = "430";
			warriorAttack = "35";
		}

		if (warriorRank == 0)
		{
			auto stars = Sprite::create("emptyStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (warriorRank == 1)
		{
			auto stars = Sprite::create("oneStar.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (warriorRank == 2)
		{
			auto stars = Sprite::create("twoStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (warriorRank == 3)
		{
			auto stars = Sprite::create("threeStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (warriorRank == 4)
		{
			auto stars = Sprite::create("fourStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}

		auto health = Label::createWithTTF("HP:  " + warriorHealth, "fonts/Marker Felt.ttf", 14);
		health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		health->setTag(55);
		uiLayer->addChild(health);

		auto attack = Label::createWithTTF("Atk:  " + warriorAttack, "fonts/Marker Felt.ttf", 14);
		attack->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.2)));
		attack->setTag(56);
		uiLayer->addChild(attack);

		if (warriorRank < 4)
		{
			auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
													   "upgrade_soldier.jpg",
													   CC_CALLBACK_1(UpgradeScene::confirmFirstUpgrade, this));

			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
			upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
			upgradeTheSoldierMenu->setTag(58);
			uiLayer->addChild(upgradeTheSoldierMenu);
		}
		else
		{
			auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			upgradeTheSoldier->setTag(58);
			uiLayer->addChild(upgradeTheSoldier);
		}
	}
	else
	{
		auto backDrop = MenuItemImage::create("blockOut_Content2.png",
												   "blockOut_Content2.png",
												   CC_CALLBACK_1(UpgradeScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(36);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.jpg");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(37);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("Not enough money.", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		label->setTag(38);
		uiLayer->addChild(label);

		auto okButton = MenuItemImage::create("cancel-button.jpg",
												   "cancel-button.jpg",
												   CC_CALLBACK_1(UpgradeScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void UpgradeScene::upgradeSecondSoldier(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(50);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(51);
	uiLayer->addChild(popup);

	auto soldierPic = Sprite::create("second_soldier_upgrade.jpg");
	soldierPic->setPosition((Point(visibleSize.width / 2.8, visibleSize.height / 2)));
	soldierPic->setTag(52);
	uiLayer->addChild(soldierPic);

	auto label = Label::createWithTTF("Space Ranger", "fonts/Marker Felt.ttf", 18);
	label->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 1.6)));
	label->setTag(53);
	uiLayer->addChild(label);

	if (spaceRangerRank == 0)
	{
		auto stars = Sprite::create("emptyStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (spaceRangerRank == 1)
	{
		auto stars = Sprite::create("oneStar.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (spaceRangerRank == 2)
	{
		auto stars = Sprite::create("twoStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (spaceRangerRank == 3)
	{
		auto stars = Sprite::create("threeStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (spaceRangerRank == 4)
	{
		auto stars = Sprite::create("fourStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}

	auto health = Label::createWithTTF("HP:  " + spaceRangerHealth, "fonts/Marker Felt.ttf", 14);
	health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	health->setTag(55);
	uiLayer->addChild(health);

	auto attack = Label::createWithTTF("Atk:  " + spaceRangerAttack, "fonts/Marker Felt.ttf", 14);
	attack->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.2)));
	attack->setTag(56);
	uiLayer->addChild(attack);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.55, visibleSize.height / 2.7)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(57);
	uiLayer->addChild(cancelButtonMenu);

	if (spaceRangerRank < 4)
	{
		auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
												   "upgrade_soldier.jpg",
												   CC_CALLBACK_1(UpgradeScene::confirmSecondUpgrade, this));

		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
		upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
		upgradeTheSoldierMenu->setTag(58);
		uiLayer->addChild(upgradeTheSoldierMenu);
	}
	else
	{
		auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		upgradeTheSoldier->setTag(58);
		uiLayer->addChild(upgradeTheSoldier);
	}
}

void UpgradeScene::confirmSecondUpgrade(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto backDrop = MenuItemImage::create("blockOut_Content2.png",
											   "blockOut_Content2.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(59);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_upgrade_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(60);
	uiLayer->addChild(popup);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromConfirmUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(61);
	uiLayer->addChild(cancelButtonMenu);


	auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
											   "upgrade_soldier.jpg",
											   CC_CALLBACK_1(UpgradeScene::upgradeSecondStats, this));

	upgradeTheSoldier->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
	upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
	upgradeTheSoldierMenu->setTag(62);
	uiLayer->addChild(upgradeTheSoldierMenu);

	auto label = Label::createWithTTF("Upgrade the Space Ranger?", "fonts/Marker Felt.ttf", 12);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(63);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.jpg");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int upgradeCost = getCostForSoldierRank(spaceRangerRank);
	sprintf(money,"%d", upgradeCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void UpgradeScene::upgradeSecondStats(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int costOfUpgrade = getCostForSoldierRank(spaceRangerRank);
	if (moneyTotal >= costOfUpgrade)
	{
		moneyTotal = moneyTotal - costOfUpgrade;
		uiLayer->removeChildByTag(54,1);
		uiLayer->removeChildByTag(55,1);
		uiLayer->removeChildByTag(56,1);
		uiLayer->removeChildByTag(58,1);
		uiLayer->removeChildByTag(59,1);
		uiLayer->removeChildByTag(60,1);
		uiLayer->removeChildByTag(61,1);
		uiLayer->removeChildByTag(62,1);
		uiLayer->removeChildByTag(63,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);


		spaceRangerRank = spaceRangerRank + 1;

		if (spaceRangerRank == 1)
		{
			spaceRangerHealth = "220";
			spaceRangerAttack = "21";
		}
		else if (spaceRangerRank == 2)
		{
			spaceRangerHealth = "260";
			spaceRangerAttack = "27";
		}
		else if (spaceRangerRank == 3)
		{
			spaceRangerHealth = "300";
			spaceRangerAttack = "33";
		}
		else if (spaceRangerRank == 4)
		{
			spaceRangerHealth = "370";
			spaceRangerAttack = "40";
		}

		if (spaceRangerRank == 0)
		{
			auto stars = Sprite::create("emptyStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (spaceRangerRank == 1)
		{
			auto stars = Sprite::create("oneStar.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (spaceRangerRank == 2)
		{
			auto stars = Sprite::create("twoStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (spaceRangerRank == 3)
		{
			auto stars = Sprite::create("threeStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (spaceRangerRank == 4)
		{
			auto stars = Sprite::create("fourStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}

		auto health = Label::createWithTTF("HP:  " + spaceRangerHealth, "fonts/Marker Felt.ttf", 14);
		health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		health->setTag(55);
		uiLayer->addChild(health);

		auto attack = Label::createWithTTF("Atk:  " + spaceRangerAttack, "fonts/Marker Felt.ttf", 14);
		attack->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.2)));
		attack->setTag(56);
		uiLayer->addChild(attack);

		if (spaceRangerRank < 4)
		{
			auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
													   "upgrade_soldier.jpg",
													   CC_CALLBACK_1(UpgradeScene::confirmSecondUpgrade, this));

			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
			upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
			upgradeTheSoldierMenu->setTag(58);
			uiLayer->addChild(upgradeTheSoldierMenu);
		}
		else
		{
			auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			upgradeTheSoldier->setTag(58);
			uiLayer->addChild(upgradeTheSoldier);
		}
	}
	else
	{
		auto backDrop = MenuItemImage::create("blockOut_Content2.png",
												   "blockOut_Content2.png",
												   CC_CALLBACK_1(UpgradeScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(36);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.jpg");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(37);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("Not enough money.", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		label->setTag(38);
		uiLayer->addChild(label);

		auto okButton = MenuItemImage::create("cancel-button.jpg",
												   "cancel-button.jpg",
												   CC_CALLBACK_1(UpgradeScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void UpgradeScene::upgradeThirdSoldier(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(50);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(51);
	uiLayer->addChild(popup);

	auto soldierPic = Sprite::create("third_soldier_upgrade.jpg");
	soldierPic->setPosition((Point(visibleSize.width / 2.8, visibleSize.height / 2)));
	soldierPic->setTag(52);
	uiLayer->addChild(soldierPic);

	auto label = Label::createWithTTF("Scout", "fonts/Marker Felt.ttf", 18);
	label->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 1.6)));
	label->setTag(53);
	uiLayer->addChild(label);

	if (scoutRank == 0)
	{
		auto stars = Sprite::create("emptyStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (scoutRank == 1)
	{
		auto stars = Sprite::create("oneStar.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (scoutRank == 2)
	{
		auto stars = Sprite::create("twoStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (scoutRank == 3)
	{
		auto stars = Sprite::create("threeStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (scoutRank == 4)
	{
		auto stars = Sprite::create("fourStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}

	auto health = Label::createWithTTF("HP:  " + scoutHealth, "fonts/Marker Felt.ttf", 14);
	health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	health->setTag(55);
	uiLayer->addChild(health);

	auto attack = Label::createWithTTF("Atk:  " + scoutAttack, "fonts/Marker Felt.ttf", 14);
	attack->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.2)));
	attack->setTag(56);
	uiLayer->addChild(attack);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.55, visibleSize.height / 2.7)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(57);
	uiLayer->addChild(cancelButtonMenu);

	if (scoutRank < 4)
	{
		auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
												   "upgrade_soldier.jpg",
												   CC_CALLBACK_1(UpgradeScene::confirmThirdUpgrade, this));

		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
		upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
		upgradeTheSoldierMenu->setTag(58);
		uiLayer->addChild(upgradeTheSoldierMenu);
	}
	else
	{
		auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		upgradeTheSoldier->setTag(58);
		uiLayer->addChild(upgradeTheSoldier);
	}
}

void UpgradeScene::confirmThirdUpgrade(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto backDrop = MenuItemImage::create("blockOut_Content2.png",
											   "blockOut_Content2.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(59);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_upgrade_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(60);
	uiLayer->addChild(popup);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromConfirmUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(61);
	uiLayer->addChild(cancelButtonMenu);


	auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
											   "upgrade_soldier.jpg",
											   CC_CALLBACK_1(UpgradeScene::upgradeThirdStats, this));

	upgradeTheSoldier->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
	upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
	upgradeTheSoldierMenu->setTag(62);
	uiLayer->addChild(upgradeTheSoldierMenu);

	auto label = Label::createWithTTF("Upgrade the Scout?", "fonts/Marker Felt.ttf", 12);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(63);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.jpg");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int upgradeCost = getCostForSoldierRank(scoutRank);
	sprintf(money,"%d", upgradeCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void UpgradeScene::upgradeThirdStats(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int costOfUpgrade = getCostForSoldierRank(scoutRank);
	if (moneyTotal >= costOfUpgrade)
	{
		moneyTotal = moneyTotal - costOfUpgrade;
		uiLayer->removeChildByTag(54,1);
		uiLayer->removeChildByTag(55,1);
		uiLayer->removeChildByTag(56,1);
		uiLayer->removeChildByTag(58,1);
		uiLayer->removeChildByTag(59,1);
		uiLayer->removeChildByTag(60,1);
		uiLayer->removeChildByTag(61,1);
		uiLayer->removeChildByTag(62,1);
		uiLayer->removeChildByTag(63,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		scoutRank = scoutRank + 1;

		if (scoutRank == 1)
		{
			scoutHealth = "180";
			scoutAttack = "12";
		}
		else if (scoutRank == 2)
		{
			scoutHealth = "220";
			scoutAttack = "15";
		}
		else if (scoutRank == 3)
		{
			scoutHealth = "260";
			scoutAttack = "18";
		}
		else if (scoutRank == 4)
		{
			scoutHealth = "330";
			scoutAttack = "25";
		}

		if (scoutRank == 0)
		{
			auto stars = Sprite::create("emptyStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (scoutRank == 1)
		{
			auto stars = Sprite::create("oneStar.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (scoutRank == 2)
		{
			auto stars = Sprite::create("twoStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (scoutRank == 3)
		{
			auto stars = Sprite::create("threeStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (scoutRank == 4)
		{
			auto stars = Sprite::create("fourStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}

		auto health = Label::createWithTTF("HP:  " + scoutHealth, "fonts/Marker Felt.ttf", 14);
		health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		health->setTag(55);
		uiLayer->addChild(health);

		auto attack = Label::createWithTTF("Atk:  " + scoutAttack, "fonts/Marker Felt.ttf", 14);
		attack->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.2)));
		attack->setTag(56);
		uiLayer->addChild(attack);

		if (scoutRank < 4)
		{
			auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
													   "upgrade_soldier.jpg",
													   CC_CALLBACK_1(UpgradeScene::confirmThirdUpgrade, this));

			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
			upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
			upgradeTheSoldierMenu->setTag(58);
			uiLayer->addChild(upgradeTheSoldierMenu);
		}
		else
		{
			auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			upgradeTheSoldier->setTag(58);
			uiLayer->addChild(upgradeTheSoldier);
		}
	}
	else
	{
		auto backDrop = MenuItemImage::create("blockOut_Content2.png",
												   "blockOut_Content2.png",
												   CC_CALLBACK_1(UpgradeScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(36);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.jpg");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(37);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("Not enough money.", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		label->setTag(38);
		uiLayer->addChild(label);

		auto okButton = MenuItemImage::create("cancel-button.jpg",
												   "cancel-button.jpg",
												   CC_CALLBACK_1(UpgradeScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void UpgradeScene::upgradeFourthSoldier(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(50);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(51);
	uiLayer->addChild(popup);

	auto soldierPic = Sprite::create("fourth_soldier_upgrade.jpg");
	soldierPic->setPosition((Point(visibleSize.width / 2.8, visibleSize.height / 2)));
	soldierPic->setTag(52);
	uiLayer->addChild(soldierPic);

	auto label = Label::createWithTTF("Cleric", "fonts/Marker Felt.ttf", 18);
	label->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 1.6)));
	label->setTag(53);
	uiLayer->addChild(label);

	if (clericRank == 0)
	{
		auto stars = Sprite::create("emptyStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (clericRank == 1)
	{
		auto stars = Sprite::create("oneStar.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (clericRank == 2)
	{
		auto stars = Sprite::create("twoStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (clericRank == 3)
	{
		auto stars = Sprite::create("threeStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (clericRank == 4)
	{
		auto stars = Sprite::create("fourStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}

	auto health = Label::createWithTTF("HP:  " + clericHealth, "fonts/Marker Felt.ttf", 14);
	health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	health->setTag(55);
	uiLayer->addChild(health);

	auto attack = Label::createWithTTF("Atk:  " + clericAttack, "fonts/Marker Felt.ttf", 14);
	attack->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.2)));
	attack->setTag(56);
	uiLayer->addChild(attack);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.55, visibleSize.height / 2.7)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(57);
	uiLayer->addChild(cancelButtonMenu);

	if (clericRank < 4)
	{
		auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
												   "upgrade_soldier.jpg",
												   CC_CALLBACK_1(UpgradeScene::confirmFourthUpgrade, this));

		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
		upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
		upgradeTheSoldierMenu->setTag(58);
		uiLayer->addChild(upgradeTheSoldierMenu);
	}
	else
	{
		auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		upgradeTheSoldier->setTag(58);
		uiLayer->addChild(upgradeTheSoldier);
	}
}

void UpgradeScene::confirmFourthUpgrade(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto backDrop = MenuItemImage::create("blockOut_Content2.png",
											   "blockOut_Content2.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(59);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_upgrade_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(60);
	uiLayer->addChild(popup);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromConfirmUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(61);
	uiLayer->addChild(cancelButtonMenu);


	auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
											   "upgrade_soldier.jpg",
											   CC_CALLBACK_1(UpgradeScene::upgradeFourthStats, this));

	upgradeTheSoldier->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
	upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
	upgradeTheSoldierMenu->setTag(62);
	uiLayer->addChild(upgradeTheSoldierMenu);

	auto label = Label::createWithTTF("Upgrade the Cleric?", "fonts/Marker Felt.ttf", 12);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(63);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.jpg");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int upgradeCost = getCostForSoldierRank(clericRank);
	sprintf(money,"%d", upgradeCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void UpgradeScene::upgradeFourthStats(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int costOfUpgrade = getCostForSoldierRank(clericRank);
	if (moneyTotal >= costOfUpgrade)
	{
		moneyTotal = moneyTotal - costOfUpgrade;
		uiLayer->removeChildByTag(54,1);
		uiLayer->removeChildByTag(55,1);
		uiLayer->removeChildByTag(56,1);
		uiLayer->removeChildByTag(58,1);
		uiLayer->removeChildByTag(59,1);
		uiLayer->removeChildByTag(60,1);
		uiLayer->removeChildByTag(61,1);
		uiLayer->removeChildByTag(62,1);
		uiLayer->removeChildByTag(63,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		clericRank = clericRank + 1;

		if (clericRank == 1)
		{
			clericHealth = "200";
			clericAttack = "12";
		}
		else if (clericRank == 2)
		{
			clericHealth = "230";
			clericAttack = "16";
		}
		else if (clericRank == 3)
		{
			clericHealth = "290";
			clericAttack = "20";
		}
		else if (clericRank == 4)
		{
			clericHealth = "370";
			clericAttack = "29";
		}

		if (clericRank == 0)
		{
			auto stars = Sprite::create("emptyStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (clericRank == 1)
		{
			auto stars = Sprite::create("oneStar.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (clericRank == 2)
		{
			auto stars = Sprite::create("twoStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (clericRank == 3)
		{
			auto stars = Sprite::create("threeStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (clericRank == 4)
		{
			auto stars = Sprite::create("fourStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}

		auto health = Label::createWithTTF("HP:  " + clericHealth, "fonts/Marker Felt.ttf", 14);
		health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		health->setTag(55);
		uiLayer->addChild(health);

		auto attack = Label::createWithTTF("Atk:  " + clericAttack, "fonts/Marker Felt.ttf", 14);
		attack->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.2)));
		attack->setTag(56);
		uiLayer->addChild(attack);

		if (clericRank < 4)
		{
			auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
													   "upgrade_soldier.jpg",
													   CC_CALLBACK_1(UpgradeScene::confirmFourthUpgrade, this));

			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
			upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
			upgradeTheSoldierMenu->setTag(58);
			uiLayer->addChild(upgradeTheSoldierMenu);
		}
		else
		{
			auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			upgradeTheSoldier->setTag(58);
			uiLayer->addChild(upgradeTheSoldier);
		}
	}
	else
	{
		auto backDrop = MenuItemImage::create("blockOut_Content2.png",
												   "blockOut_Content2.png",
												   CC_CALLBACK_1(UpgradeScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(36);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.jpg");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(37);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("Not enough money.", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		label->setTag(38);
		uiLayer->addChild(label);

		auto okButton = MenuItemImage::create("cancel-button.jpg",
												   "cancel-button.jpg",
												   CC_CALLBACK_1(UpgradeScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void UpgradeScene::upgradeFifthSoldier(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(50);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(51);
	uiLayer->addChild(popup);

	auto soldierPic = Sprite::create("fifth_soldier_upgrade.jpg");
	soldierPic->setPosition((Point(visibleSize.width / 2.8, visibleSize.height / 2)));
	soldierPic->setTag(52);
	uiLayer->addChild(soldierPic);

	auto label = Label::createWithTTF("Assassin", "fonts/Marker Felt.ttf", 18);
	label->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 1.6)));
	label->setTag(53);
	uiLayer->addChild(label);

	if (assassinRank == 0)
	{
		auto stars = Sprite::create("emptyStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (assassinRank == 1)
	{
		auto stars = Sprite::create("oneStar.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (assassinRank == 2)
	{
		auto stars = Sprite::create("twoStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (assassinRank == 3)
	{
		auto stars = Sprite::create("threeStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (assassinRank == 4)
	{
		auto stars = Sprite::create("fourStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}

	auto health = Label::createWithTTF("HP:  " + assassinHealth, "fonts/Marker Felt.ttf", 14);
	health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	health->setTag(55);
	uiLayer->addChild(health);

	auto attack = Label::createWithTTF("Atk:  " + assassinAttack, "fonts/Marker Felt.ttf", 14);
	attack->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.2)));
	attack->setTag(56);
	uiLayer->addChild(attack);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.55, visibleSize.height / 2.7)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(57);
	uiLayer->addChild(cancelButtonMenu);

	if (assassinRank < 4)
	{
		auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
												   "upgrade_soldier.jpg",
												   CC_CALLBACK_1(UpgradeScene::confirmFifthUpgrade, this));

		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
		upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
		upgradeTheSoldierMenu->setTag(58);
		uiLayer->addChild(upgradeTheSoldierMenu);
	}
	else
	{
		auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		upgradeTheSoldier->setTag(58);
		uiLayer->addChild(upgradeTheSoldier);
	}
}

void UpgradeScene::confirmFifthUpgrade(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto backDrop = MenuItemImage::create("blockOut_Content2.png",
											   "blockOut_Content2.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(59);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_upgrade_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(60);
	uiLayer->addChild(popup);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromConfirmUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(61);
	uiLayer->addChild(cancelButtonMenu);


	auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
											   "upgrade_soldier.jpg",
											   CC_CALLBACK_1(UpgradeScene::upgradeFifthStats, this));

	upgradeTheSoldier->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
	upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
	upgradeTheSoldierMenu->setTag(62);
	uiLayer->addChild(upgradeTheSoldierMenu);

	auto label = Label::createWithTTF("Upgrade the Assassin?", "fonts/Marker Felt.ttf", 12);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(63);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.jpg");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int upgradeCost = getCostForSoldierRank(assassinRank);
	sprintf(money,"%d", upgradeCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void UpgradeScene::upgradeFifthStats(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int costOfUpgrade = getCostForSoldierRank(assassinRank);
	if (moneyTotal >= costOfUpgrade)
	{
		moneyTotal = moneyTotal - costOfUpgrade;
		uiLayer->removeChildByTag(54,1);
		uiLayer->removeChildByTag(55,1);
		uiLayer->removeChildByTag(56,1);
		uiLayer->removeChildByTag(58,1);
		uiLayer->removeChildByTag(59,1);
		uiLayer->removeChildByTag(60,1);
		uiLayer->removeChildByTag(61,1);
		uiLayer->removeChildByTag(62,1);
		uiLayer->removeChildByTag(63,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		assassinRank = assassinRank + 1;

		if (assassinRank == 1)
		{
			assassinHealth = "290";
			assassinAttack = "25";
		}
		else if (assassinRank == 2)
		{
			assassinHealth = "360";
			assassinAttack = "34";
		}
		else if (assassinRank == 3)
		{
			assassinHealth = "460";
			assassinAttack = "40";
		}
		else if (assassinRank == 4)
		{
			assassinHealth = "550";
			assassinAttack = "50";
		}

		if (assassinRank == 0)
		{
			auto stars = Sprite::create("emptyStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (assassinRank == 1)
		{
			auto stars = Sprite::create("oneStar.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (assassinRank == 2)
		{
			auto stars = Sprite::create("twoStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (assassinRank == 3)
		{
			auto stars = Sprite::create("threeStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (assassinRank == 4)
		{
			auto stars = Sprite::create("fourStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}

		auto health = Label::createWithTTF("HP:  " + assassinHealth, "fonts/Marker Felt.ttf", 14);
		health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		health->setTag(55);
		uiLayer->addChild(health);

		auto attack = Label::createWithTTF("Atk:  " + assassinAttack, "fonts/Marker Felt.ttf", 14);
		attack->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.2)));
		attack->setTag(56);
		uiLayer->addChild(attack);

		if (assassinRank < 4)
		{
			auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
													   "upgrade_soldier.jpg",
													   CC_CALLBACK_1(UpgradeScene::confirmFifthUpgrade, this));

			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
			upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
			upgradeTheSoldierMenu->setTag(58);
			uiLayer->addChild(upgradeTheSoldierMenu);
		}
		else
		{
			auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			upgradeTheSoldier->setTag(58);
			uiLayer->addChild(upgradeTheSoldier);
		}
	}
	else
	{
		auto backDrop = MenuItemImage::create("blockOut_Content2.png",
												   "blockOut_Content2.png",
												   CC_CALLBACK_1(UpgradeScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(36);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.jpg");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(37);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("Not enough money.", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		label->setTag(38);
		uiLayer->addChild(label);

		auto okButton = MenuItemImage::create("cancel-button.jpg",
												   "cancel-button.jpg",
												   CC_CALLBACK_1(UpgradeScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void UpgradeScene::upgradeSixthSoldier(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(50);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(51);
	uiLayer->addChild(popup);

	auto soldierPic = Sprite::create("sixth_soldier_upgrade.jpg");
	soldierPic->setPosition((Point(visibleSize.width / 2.8, visibleSize.height / 2)));
	soldierPic->setTag(52);
	uiLayer->addChild(soldierPic);

	auto label = Label::createWithTTF("Mage", "fonts/Marker Felt.ttf", 18);
	label->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 1.6)));
	label->setTag(53);
	uiLayer->addChild(label);

	if (mageRank == 0)
	{
		auto stars = Sprite::create("emptyStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (mageRank == 1)
	{
		auto stars = Sprite::create("oneStar.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (mageRank == 2)
	{
		auto stars = Sprite::create("twoStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (mageRank == 3)
	{
		auto stars = Sprite::create("threeStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (mageRank == 4)
	{
		auto stars = Sprite::create("fourStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}

	auto health = Label::createWithTTF("HP:  " + mageHealth, "fonts/Marker Felt.ttf", 14);
	health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	health->setTag(55);
	uiLayer->addChild(health);

	auto attack = Label::createWithTTF("Atk:  " + mageAttack, "fonts/Marker Felt.ttf", 14);
	attack->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.2)));
	attack->setTag(56);
	uiLayer->addChild(attack);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.55, visibleSize.height / 2.7)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(57);
	uiLayer->addChild(cancelButtonMenu);

	if (mageRank < 4)
	{
		auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
												   "upgrade_soldier.jpg",
												   CC_CALLBACK_1(UpgradeScene::confirmSixthUpgrade, this));

		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
		upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
		upgradeTheSoldierMenu->setTag(58);
		uiLayer->addChild(upgradeTheSoldierMenu);
	}
	else
	{
		auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		upgradeTheSoldier->setTag(58);
		uiLayer->addChild(upgradeTheSoldier);
	}
}

void UpgradeScene::confirmSixthUpgrade(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto backDrop = MenuItemImage::create("blockOut_Content2.png",
											   "blockOut_Content2.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(59);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_upgrade_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(60);
	uiLayer->addChild(popup);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromConfirmUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(61);
	uiLayer->addChild(cancelButtonMenu);


	auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
											   "upgrade_soldier.jpg",
											   CC_CALLBACK_1(UpgradeScene::upgradeSixthStats, this));

	upgradeTheSoldier->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
	upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
	upgradeTheSoldierMenu->setTag(62);
	uiLayer->addChild(upgradeTheSoldierMenu);

	auto label = Label::createWithTTF("Upgrade the Mage?", "fonts/Marker Felt.ttf", 12);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(63);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.jpg");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int upgradeCost = getCostForSoldierRank(mageRank);
	sprintf(money,"%d", upgradeCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void UpgradeScene::upgradeSixthStats(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int costOfUpgrade = getCostForSoldierRank(mageRank);
	if (moneyTotal >= costOfUpgrade)
	{
		moneyTotal = moneyTotal - costOfUpgrade;
		uiLayer->removeChildByTag(54,1);
		uiLayer->removeChildByTag(55,1);
		uiLayer->removeChildByTag(56,1);
		uiLayer->removeChildByTag(58,1);
		uiLayer->removeChildByTag(59,1);
		uiLayer->removeChildByTag(60,1);
		uiLayer->removeChildByTag(61,1);
		uiLayer->removeChildByTag(62,1);
		uiLayer->removeChildByTag(63,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		mageRank = mageRank + 1;

		if (mageRank == 1)
		{
			mageHealth = "180";
			mageAttack = "19";
		}
		else if (mageRank == 2)
		{
			mageHealth = "200";
			mageAttack = "24";
		}
		else if (mageRank == 3)
		{
			mageHealth = "240";
			mageAttack = "30";
		}
		else if (mageRank == 4)
		{
			mageHealth = "310";
			mageAttack = "38";
		}

		if (mageRank == 0)
		{
			auto stars = Sprite::create("emptyStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (mageRank == 1)
		{
			auto stars = Sprite::create("oneStar.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (mageRank == 2)
		{
			auto stars = Sprite::create("twoStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (mageRank == 3)
		{
			auto stars = Sprite::create("threeStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (mageRank == 4)
		{
			auto stars = Sprite::create("fourStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}

		auto health = Label::createWithTTF("HP:  " + mageHealth, "fonts/Marker Felt.ttf", 14);
		health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		health->setTag(55);
		uiLayer->addChild(health);

		auto attack = Label::createWithTTF("Atk:  " + mageAttack, "fonts/Marker Felt.ttf", 14);
		attack->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.2)));
		attack->setTag(56);
		uiLayer->addChild(attack);

		if (mageRank < 4)
		{
			auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
													   "upgrade_soldier.jpg",
													   CC_CALLBACK_1(UpgradeScene::confirmSixthUpgrade, this));

			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
			upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
			upgradeTheSoldierMenu->setTag(58);
			uiLayer->addChild(upgradeTheSoldierMenu);
		}
		else
		{
			auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			upgradeTheSoldier->setTag(58);
			uiLayer->addChild(upgradeTheSoldier);
		}
	}
	else
	{
		auto backDrop = MenuItemImage::create("blockOut_Content2.png",
												   "blockOut_Content2.png",
												   CC_CALLBACK_1(UpgradeScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(36);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.jpg");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(37);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("Not enough money.", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		label->setTag(38);
		uiLayer->addChild(label);

		auto okButton = MenuItemImage::create("cancel-button.jpg",
												   "cancel-button.jpg",
												   CC_CALLBACK_1(UpgradeScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void UpgradeScene::upgradeFirstBuiltItem(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(50);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(51);
	uiLayer->addChild(popup);

	auto soldierPic = Sprite::create("first_soldier_upgrade.jpg");
	soldierPic->setPosition((Point(visibleSize.width / 2.8, visibleSize.height / 2)));
	soldierPic->setTag(52);
	uiLayer->addChild(soldierPic);

	auto label = Label::createWithTTF("Horizontal Wall", "fonts/Marker Felt.ttf", 18);
	label->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 1.6)));
	label->setTag(53);
	uiLayer->addChild(label);

	if (horiWallRank == 0)
	{
		auto stars = Sprite::create("emptyStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (horiWallRank == 1)
	{
		auto stars = Sprite::create("oneStar.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (horiWallRank == 2)
	{
		auto stars = Sprite::create("twoStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (horiWallRank == 3)
	{
		auto stars = Sprite::create("threeStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (horiWallRank == 4)
	{
		auto stars = Sprite::create("fourStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}

	auto health = Label::createWithTTF("HP:  " + horiWallHealth, "fonts/Marker Felt.ttf", 14);
	health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	health->setTag(55);
	uiLayer->addChild(health);


	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.55, visibleSize.height / 2.7)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(57);
	uiLayer->addChild(cancelButtonMenu);

	if (horiWallRank < 4)
	{
		auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
												   "upgrade_soldier.jpg",
												   CC_CALLBACK_1(UpgradeScene::confirmFirstItemUpgrade, this));

		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
		upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
		upgradeTheSoldierMenu->setTag(58);
		uiLayer->addChild(upgradeTheSoldierMenu);
	}
	else
	{
		auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		upgradeTheSoldier->setTag(58);
		uiLayer->addChild(upgradeTheSoldier);
	}
}

void UpgradeScene::confirmFirstItemUpgrade(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto backDrop = MenuItemImage::create("blockOut_Content2.png",
											   "blockOut_Content2.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(59);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_upgrade_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(60);
	uiLayer->addChild(popup);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromConfirmUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(61);
	uiLayer->addChild(cancelButtonMenu);


	auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
											   "upgrade_soldier.jpg",
											   CC_CALLBACK_1(UpgradeScene::upgradeFirstItemStats, this));

	upgradeTheSoldier->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
	upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
	upgradeTheSoldierMenu->setTag(62);
	uiLayer->addChild(upgradeTheSoldierMenu);

	auto label = Label::createWithTTF("Upgrade horizontal walls?", "fonts/Marker Felt.ttf", 12);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(63);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.jpg");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int upgradeCost = getCostForItemRank(horiWallRank);
	sprintf(money,"%d", upgradeCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void UpgradeScene::upgradeFirstItemStats(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int costOfUpgrade = getCostForItemRank(horiWallRank);
	if (moneyTotal >= costOfUpgrade)
	{
		moneyTotal = moneyTotal - costOfUpgrade;
		uiLayer->removeChildByTag(54,1);
		uiLayer->removeChildByTag(55,1);
		uiLayer->removeChildByTag(56,1);
		uiLayer->removeChildByTag(58,1);
		uiLayer->removeChildByTag(59,1);
		uiLayer->removeChildByTag(60,1);
		uiLayer->removeChildByTag(61,1);
		uiLayer->removeChildByTag(62,1);
		uiLayer->removeChildByTag(63,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		horiWallRank = horiWallRank + 1;

		if (horiWallRank == 1)
		{
			horiWallHealth = "380";
		}
		else if (horiWallRank == 2)
		{
			horiWallHealth = "440";
		}
		else if (horiWallRank == 3)
		{
			horiWallHealth = "510";
		}
		else if (horiWallRank == 4)
		{
			horiWallHealth = "600";
		}

		if (horiWallRank == 0)
		{
			auto stars = Sprite::create("emptyStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (horiWallRank == 1)
		{
			auto stars = Sprite::create("oneStar.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (horiWallRank == 2)
		{
			auto stars = Sprite::create("twoStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (horiWallRank == 3)
		{
			auto stars = Sprite::create("threeStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (horiWallRank == 4)
		{
			auto stars = Sprite::create("fourStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}

		auto health = Label::createWithTTF("HP:  " + horiWallHealth, "fonts/Marker Felt.ttf", 14);
		health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		health->setTag(55);
		uiLayer->addChild(health);


		if (horiWallRank < 4)
		{
			auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
													   "upgrade_soldier.jpg",
													   CC_CALLBACK_1(UpgradeScene::confirmFirstItemUpgrade, this));

			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
			upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
			upgradeTheSoldierMenu->setTag(58);
			uiLayer->addChild(upgradeTheSoldierMenu);
		}
		else
		{
			auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			upgradeTheSoldier->setTag(58);
			uiLayer->addChild(upgradeTheSoldier);
		}
	}
	else
	{
		auto backDrop = MenuItemImage::create("blockOut_Content2.png",
												   "blockOut_Content2.png",
												   CC_CALLBACK_1(UpgradeScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(36);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.jpg");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(37);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("Not enough money.", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		label->setTag(38);
		uiLayer->addChild(label);

		auto okButton = MenuItemImage::create("cancel-button.jpg",
												   "cancel-button.jpg",
												   CC_CALLBACK_1(UpgradeScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void UpgradeScene::upgradeSecondBuiltItem(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(50);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(51);
	uiLayer->addChild(popup);

	auto soldierPic = Sprite::create("second_soldier_upgrade.jpg");
	soldierPic->setPosition((Point(visibleSize.width / 2.8, visibleSize.height / 2)));
	soldierPic->setTag(52);
	uiLayer->addChild(soldierPic);

	auto label = Label::createWithTTF("Vertical Wall", "fonts/Marker Felt.ttf", 18);
	label->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 1.6)));
	label->setTag(53);
	uiLayer->addChild(label);

	if (verWallRank == 0)
	{
		auto stars = Sprite::create("emptyStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (verWallRank == 1)
	{
		auto stars = Sprite::create("oneStar.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (verWallRank == 2)
	{
		auto stars = Sprite::create("twoStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (verWallRank == 3)
	{
		auto stars = Sprite::create("threeStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (verWallRank == 4)
	{
		auto stars = Sprite::create("fourStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}

	auto health = Label::createWithTTF("HP:  " + verWallHealth, "fonts/Marker Felt.ttf", 14);
	health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	health->setTag(55);
	uiLayer->addChild(health);


	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.55, visibleSize.height / 2.7)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(57);
	uiLayer->addChild(cancelButtonMenu);

	if (verWallRank < 4)
	{
		auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
												   "upgrade_soldier.jpg",
												   CC_CALLBACK_1(UpgradeScene::confirmSecondItemUpgrade, this));

		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
		upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
		upgradeTheSoldierMenu->setTag(58);
		uiLayer->addChild(upgradeTheSoldierMenu);
	}
	else
	{
		auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		upgradeTheSoldier->setTag(58);
		uiLayer->addChild(upgradeTheSoldier);
	}
}

void UpgradeScene::confirmSecondItemUpgrade(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto backDrop = MenuItemImage::create("blockOut_Content2.png",
											   "blockOut_Content2.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(59);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_upgrade_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(60);
	uiLayer->addChild(popup);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromConfirmUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(61);
	uiLayer->addChild(cancelButtonMenu);


	auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
											   "upgrade_soldier.jpg",
											   CC_CALLBACK_1(UpgradeScene::upgradeSecondItemStats, this));

	upgradeTheSoldier->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
	upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
	upgradeTheSoldierMenu->setTag(62);
	uiLayer->addChild(upgradeTheSoldierMenu);

	auto label = Label::createWithTTF("Upgrade vertical walls?", "fonts/Marker Felt.ttf", 12);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(63);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.jpg");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int upgradeCost = getCostForItemRank(verWallRank);
	sprintf(money,"%d", upgradeCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void UpgradeScene::upgradeSecondItemStats(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int costOfUpgrade = getCostForItemRank(verWallRank);
	if (moneyTotal >= costOfUpgrade)
	{
		moneyTotal = moneyTotal - costOfUpgrade;
		uiLayer->removeChildByTag(54,1);
		uiLayer->removeChildByTag(55,1);
		uiLayer->removeChildByTag(56,1);
		uiLayer->removeChildByTag(58,1);
		uiLayer->removeChildByTag(59,1);
		uiLayer->removeChildByTag(60,1);
		uiLayer->removeChildByTag(61,1);
		uiLayer->removeChildByTag(62,1);
		uiLayer->removeChildByTag(63,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		verWallRank = verWallRank + 1;

		if (verWallRank == 1)
		{
			verWallHealth = "380";
		}
		else if (verWallRank == 2)
		{
			verWallHealth = "440";
		}
		else if (verWallRank == 3)
		{
			verWallHealth = "510";
		}
		else if (verWallRank == 4)
		{
			verWallHealth = "600";
		}

		if (verWallRank == 0)
		{
			auto stars = Sprite::create("emptyStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (verWallRank == 1)
		{
			auto stars = Sprite::create("oneStar.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (verWallRank == 2)
		{
			auto stars = Sprite::create("twoStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (verWallRank == 3)
		{
			auto stars = Sprite::create("threeStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (verWallRank == 4)
		{
			auto stars = Sprite::create("fourStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}

		auto health = Label::createWithTTF("HP:  " + verWallHealth, "fonts/Marker Felt.ttf", 14);
		health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		health->setTag(55);
		uiLayer->addChild(health);

		if (verWallRank < 4)
		{
			auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
													   "upgrade_soldier.jpg",
													   CC_CALLBACK_1(UpgradeScene::confirmSecondItemUpgrade, this));

			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
			upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
			upgradeTheSoldierMenu->setTag(58);
			uiLayer->addChild(upgradeTheSoldierMenu);
		}
		else
		{
			auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			upgradeTheSoldier->setTag(58);
			uiLayer->addChild(upgradeTheSoldier);
		}
	}
	else
	{
		auto backDrop = MenuItemImage::create("blockOut_Content2.png",
												   "blockOut_Content2.png",
												   CC_CALLBACK_1(UpgradeScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(36);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.jpg");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(37);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("Not enough money.", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		label->setTag(38);
		uiLayer->addChild(label);

		auto okButton = MenuItemImage::create("cancel-button.jpg",
												   "cancel-button.jpg",
												   CC_CALLBACK_1(UpgradeScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void UpgradeScene::upgradeThirdBuiltItem(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(50);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(51);
	uiLayer->addChild(popup);

	auto soldierPic = Sprite::create("third_soldier_upgrade.jpg");
	soldierPic->setPosition((Point(visibleSize.width / 2.8, visibleSize.height / 2)));
	soldierPic->setTag(52);
	uiLayer->addChild(soldierPic);

	auto label = Label::createWithTTF("Hori. Plasma Wall", "fonts/Marker Felt.ttf", 18);
	label->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 1.6)));
	label->setTag(53);
	uiLayer->addChild(label);

	if (horiPlasmaRank == 0)
	{
		auto stars = Sprite::create("emptyStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (horiPlasmaRank == 1)
	{
		auto stars = Sprite::create("oneStar.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (horiPlasmaRank == 2)
	{
		auto stars = Sprite::create("twoStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (horiPlasmaRank == 3)
	{
		auto stars = Sprite::create("threeStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (horiPlasmaRank == 4)
	{
		auto stars = Sprite::create("fourStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}

	auto health = Label::createWithTTF("HP:  " + horiPlasmaHealth, "fonts/Marker Felt.ttf", 14);
	health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	health->setTag(55);
	uiLayer->addChild(health);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.55, visibleSize.height / 2.7)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(57);
	uiLayer->addChild(cancelButtonMenu);

	if (horiPlasmaRank < 4)
	{
		auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
												   "upgrade_soldier.jpg",
												   CC_CALLBACK_1(UpgradeScene::confirmThirdItemUpgrade, this));

		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
		upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
		upgradeTheSoldierMenu->setTag(58);
		uiLayer->addChild(upgradeTheSoldierMenu);
	}
	else
	{
		auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		upgradeTheSoldier->setTag(58);
		uiLayer->addChild(upgradeTheSoldier);
	}
}

void UpgradeScene::confirmThirdItemUpgrade(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto backDrop = MenuItemImage::create("blockOut_Content2.png",
											   "blockOut_Content2.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(59);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_upgrade_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(60);
	uiLayer->addChild(popup);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromConfirmUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(61);
	uiLayer->addChild(cancelButtonMenu);


	auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
											   "upgrade_soldier.jpg",
											   CC_CALLBACK_1(UpgradeScene::upgradeThirdItemStats, this));

	upgradeTheSoldier->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
	upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
	upgradeTheSoldierMenu->setTag(62);
	uiLayer->addChild(upgradeTheSoldierMenu);

	auto label = Label::createWithTTF("Upgrade horizontal plasma walls?", "fonts/Marker Felt.ttf", 12);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(63);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.jpg");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int upgradeCost = getCostForItemRank(horiPlasmaRank);
	sprintf(money,"%d", upgradeCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void UpgradeScene::upgradeThirdItemStats(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int costOfUpgrade = getCostForItemRank(horiPlasmaRank);
	if (moneyTotal >= costOfUpgrade)
	{
		moneyTotal = moneyTotal - costOfUpgrade;
		uiLayer->removeChildByTag(54,1);
		uiLayer->removeChildByTag(55,1);
		uiLayer->removeChildByTag(56,1);
		uiLayer->removeChildByTag(58,1);
		uiLayer->removeChildByTag(59,1);
		uiLayer->removeChildByTag(60,1);
		uiLayer->removeChildByTag(61,1);
		uiLayer->removeChildByTag(62,1);
		uiLayer->removeChildByTag(63,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		horiPlasmaRank = horiPlasmaRank + 1;

		if (horiPlasmaRank == 1)
		{
			horiPlasmaHealth = "520";
		}
		else if (horiPlasmaRank == 2)
		{
			horiPlasmaHealth = "590";
		}
		else if (horiPlasmaRank == 3)
		{
			horiPlasmaHealth = "670";
		}
		else if (horiPlasmaRank == 4)
		{
			horiPlasmaHealth = "820";
		}

		if (horiPlasmaRank == 0)
		{
			auto stars = Sprite::create("emptyStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (horiPlasmaRank == 1)
		{
			auto stars = Sprite::create("oneStar.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (horiPlasmaRank == 2)
		{
			auto stars = Sprite::create("twoStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (horiPlasmaRank == 3)
		{
			auto stars = Sprite::create("threeStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (horiPlasmaRank == 4)
		{
			auto stars = Sprite::create("fourStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}

		auto health = Label::createWithTTF("HP:  " + horiPlasmaHealth, "fonts/Marker Felt.ttf", 14);
		health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		health->setTag(55);
		uiLayer->addChild(health);


		if (horiPlasmaRank < 4)
		{
			auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
													   "upgrade_soldier.jpg",
													   CC_CALLBACK_1(UpgradeScene::confirmThirdItemUpgrade, this));

			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
			upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
			upgradeTheSoldierMenu->setTag(58);
			uiLayer->addChild(upgradeTheSoldierMenu);
		}
		else
		{
			auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			upgradeTheSoldier->setTag(58);
			uiLayer->addChild(upgradeTheSoldier);
		}
	}
	else
	{
		auto backDrop = MenuItemImage::create("blockOut_Content2.png",
												   "blockOut_Content2.png",
												   CC_CALLBACK_1(UpgradeScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(36);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.jpg");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(37);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("Not enough money.", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		label->setTag(38);
		uiLayer->addChild(label);

		auto okButton = MenuItemImage::create("cancel-button.jpg",
												   "cancel-button.jpg",
												   CC_CALLBACK_1(UpgradeScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void UpgradeScene::upgradeFourthBuiltItem(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(50);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(51);
	uiLayer->addChild(popup);

	auto soldierPic = Sprite::create("fourth_soldier_upgrade.jpg");
	soldierPic->setPosition((Point(visibleSize.width / 2.8, visibleSize.height / 2)));
	soldierPic->setTag(52);
	uiLayer->addChild(soldierPic);

	auto label = Label::createWithTTF("Vert. Plasma Wall", "fonts/Marker Felt.ttf", 18);
	label->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 1.6)));
	label->setTag(53);
	uiLayer->addChild(label);

	if (verPlasmaRank == 0)
	{
		auto stars = Sprite::create("emptyStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (verPlasmaRank == 1)
	{
		auto stars = Sprite::create("oneStar.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (verPlasmaRank == 2)
	{
		auto stars = Sprite::create("twoStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (verPlasmaRank == 3)
	{
		auto stars = Sprite::create("threeStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (verPlasmaRank == 4)
	{
		auto stars = Sprite::create("fourStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}

	auto health = Label::createWithTTF("HP:  " + verPlasmaHealth, "fonts/Marker Felt.ttf", 14);
	health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	health->setTag(55);
	uiLayer->addChild(health);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.55, visibleSize.height / 2.7)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(57);
	uiLayer->addChild(cancelButtonMenu);

	if (verPlasmaRank < 4)
	{
		auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
												   "upgrade_soldier.jpg",
												   CC_CALLBACK_1(UpgradeScene::confirmFourthItemUpgrade, this));

		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
		upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
		upgradeTheSoldierMenu->setTag(58);
		uiLayer->addChild(upgradeTheSoldierMenu);
	}
	else
	{
		auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		upgradeTheSoldier->setTag(58);
		uiLayer->addChild(upgradeTheSoldier);
	}
}

void UpgradeScene::confirmFourthItemUpgrade(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto backDrop = MenuItemImage::create("blockOut_Content2.png",
											   "blockOut_Content2.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(59);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_upgrade_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(60);
	uiLayer->addChild(popup);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromConfirmUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(61);
	uiLayer->addChild(cancelButtonMenu);


	auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
											   "upgrade_soldier.jpg",
											   CC_CALLBACK_1(UpgradeScene::upgradeFourthItemStats, this));

	upgradeTheSoldier->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
	upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
	upgradeTheSoldierMenu->setTag(62);
	uiLayer->addChild(upgradeTheSoldierMenu);

	auto label = Label::createWithTTF("Upgrade vertical plasma walls?", "fonts/Marker Felt.ttf", 12);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(63);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.jpg");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int upgradeCost = getCostForItemRank(verPlasmaRank);
	sprintf(money,"%d", upgradeCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void UpgradeScene::upgradeFourthItemStats(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int costOfUpgrade = getCostForItemRank(verPlasmaRank);
	if (moneyTotal >= costOfUpgrade)
	{
		moneyTotal = moneyTotal - costOfUpgrade;
		uiLayer->removeChildByTag(54,1);
		uiLayer->removeChildByTag(55,1);
		uiLayer->removeChildByTag(56,1);
		uiLayer->removeChildByTag(58,1);
		uiLayer->removeChildByTag(59,1);
		uiLayer->removeChildByTag(60,1);
		uiLayer->removeChildByTag(61,1);
		uiLayer->removeChildByTag(62,1);
		uiLayer->removeChildByTag(63,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		verPlasmaRank = verPlasmaRank + 1;

		if (verPlasmaRank == 1)
		{
			verPlasmaHealth = "520";
		}
		else if (verPlasmaRank == 2)
		{
			verPlasmaHealth = "590";
		}
		else if (verPlasmaRank == 3)
		{
			verPlasmaHealth = "670";
		}
		else if (verPlasmaRank == 4)
		{
			verPlasmaHealth = "820";
		}

		if (verPlasmaRank == 0)
		{
			auto stars = Sprite::create("emptyStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (verPlasmaRank == 1)
		{
			auto stars = Sprite::create("oneStar.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (verPlasmaRank == 2)
		{
			auto stars = Sprite::create("twoStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (verPlasmaRank == 3)
		{
			auto stars = Sprite::create("threeStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (verPlasmaRank == 4)
		{
			auto stars = Sprite::create("fourStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}

		auto health = Label::createWithTTF("HP:  " + verPlasmaHealth, "fonts/Marker Felt.ttf", 14);
		health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		health->setTag(55);
		uiLayer->addChild(health);

		if (verPlasmaRank < 4)
		{
			auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
													   "upgrade_soldier.jpg",
													   CC_CALLBACK_1(UpgradeScene::confirmFourthItemUpgrade, this));

			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
			upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
			upgradeTheSoldierMenu->setTag(58);
			uiLayer->addChild(upgradeTheSoldierMenu);
		}
		else
		{
			auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			upgradeTheSoldier->setTag(58);
			uiLayer->addChild(upgradeTheSoldier);
		}
	}
	else
	{
		auto backDrop = MenuItemImage::create("blockOut_Content2.png",
												   "blockOut_Content2.png",
												   CC_CALLBACK_1(UpgradeScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(36);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.jpg");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(37);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("Not enough money.", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		label->setTag(38);
		uiLayer->addChild(label);

		auto okButton = MenuItemImage::create("cancel-button.jpg",
												   "cancel-button.jpg",
												   CC_CALLBACK_1(UpgradeScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void UpgradeScene::upgradeFifthBuiltItem(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(50);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(51);
	uiLayer->addChild(popup);

	auto soldierPic = Sprite::create("fifth_soldier_upgrade.jpg");
	soldierPic->setPosition((Point(visibleSize.width / 2.8, visibleSize.height / 2)));
	soldierPic->setTag(52);
	uiLayer->addChild(soldierPic);

	auto label = Label::createWithTTF("Star-Dust Tree", "fonts/Marker Felt.ttf", 18);
	label->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 1.6)));
	label->setTag(53);
	uiLayer->addChild(label);

	if (starDustTreeRank == 0)
	{
		auto stars = Sprite::create("emptyStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (starDustTreeRank == 1)
	{
		auto stars = Sprite::create("oneStar.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (starDustTreeRank == 2)
	{
		auto stars = Sprite::create("twoStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (starDustTreeRank == 3)
	{
		auto stars = Sprite::create("threeStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (starDustTreeRank == 4)
	{
		auto stars = Sprite::create("fourStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}

	auto health = Label::createWithTTF("HP:  " + starDustTreeHealth, "fonts/Marker Felt.ttf", 14);
	health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	health->setTag(55);
	uiLayer->addChild(health);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.55, visibleSize.height / 2.7)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(57);
	uiLayer->addChild(cancelButtonMenu);

	if (starDustTreeRank < 4)
	{
		auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
												   "upgrade_soldier.jpg",
												   CC_CALLBACK_1(UpgradeScene::confirmFifthItemUpgrade, this));

		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
		upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
		upgradeTheSoldierMenu->setTag(58);
		uiLayer->addChild(upgradeTheSoldierMenu);
	}
	else
	{
		auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		upgradeTheSoldier->setTag(58);
		uiLayer->addChild(upgradeTheSoldier);
	}
}

void UpgradeScene::confirmFifthItemUpgrade(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto backDrop = MenuItemImage::create("blockOut_Content2.png",
											   "blockOut_Content2.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(59);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_upgrade_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(60);
	uiLayer->addChild(popup);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromConfirmUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(61);
	uiLayer->addChild(cancelButtonMenu);


	auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
											   "upgrade_soldier.jpg",
											   CC_CALLBACK_1(UpgradeScene::upgradeFifthItemStats, this));

	upgradeTheSoldier->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
	upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
	upgradeTheSoldierMenu->setTag(62);
	uiLayer->addChild(upgradeTheSoldierMenu);

	auto label = Label::createWithTTF("Upgrade star-dust trees?", "fonts/Marker Felt.ttf", 12);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(63);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.jpg");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int upgradeCost = getCostForItemRank(starDustTreeRank);
	sprintf(money,"%d", upgradeCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void UpgradeScene::upgradeFifthItemStats(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int costOfUpgrade = getCostForItemRank(starDustTreeRank);
	if (moneyTotal >= costOfUpgrade)
	{
		moneyTotal = moneyTotal - costOfUpgrade;
		uiLayer->removeChildByTag(54,1);
		uiLayer->removeChildByTag(55,1);
		uiLayer->removeChildByTag(56,1);
		uiLayer->removeChildByTag(58,1);
		uiLayer->removeChildByTag(59,1);
		uiLayer->removeChildByTag(60,1);
		uiLayer->removeChildByTag(61,1);
		uiLayer->removeChildByTag(62,1);
		uiLayer->removeChildByTag(63,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		starDustTreeRank = starDustTreeRank + 1;

		if (starDustTreeRank == 1)
		{
			starDustTreeHealth = "230";
		}
		else if (starDustTreeRank == 2)
		{
			starDustTreeHealth = "260";
		}
		else if (starDustTreeRank == 3)
		{
			starDustTreeHealth = "310";
		}
		else if (starDustTreeRank == 4)
		{
			starDustTreeHealth = "390";
		}

		if (starDustTreeRank == 0)
		{
			auto stars = Sprite::create("emptyStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (starDustTreeRank == 1)
		{
			auto stars = Sprite::create("oneStar.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (starDustTreeRank == 2)
		{
			auto stars = Sprite::create("twoStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (starDustTreeRank == 3)
		{
			auto stars = Sprite::create("threeStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (starDustTreeRank == 4)
		{
			auto stars = Sprite::create("fourStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}

		auto health = Label::createWithTTF("HP:  " + starDustTreeHealth, "fonts/Marker Felt.ttf", 14);
		health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		health->setTag(55);
		uiLayer->addChild(health);


		if (starDustTreeRank < 4)
		{
			auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
													   "upgrade_soldier.jpg",
													   CC_CALLBACK_1(UpgradeScene::confirmFifthItemUpgrade, this));

			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
			upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
			upgradeTheSoldierMenu->setTag(58);
			uiLayer->addChild(upgradeTheSoldierMenu);
		}
		else
		{
			auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			upgradeTheSoldier->setTag(58);
			uiLayer->addChild(upgradeTheSoldier);
		}
	}
	else
	{
		auto backDrop = MenuItemImage::create("blockOut_Content2.png",
												   "blockOut_Content2.png",
												   CC_CALLBACK_1(UpgradeScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(36);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.jpg");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(37);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("Not enough money.", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		label->setTag(38);
		uiLayer->addChild(label);

		auto okButton = MenuItemImage::create("cancel-button.jpg",
												   "cancel-button.jpg",
												   CC_CALLBACK_1(UpgradeScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}


void UpgradeScene::upgradeSixthBuiltItem(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(50);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(51);
	uiLayer->addChild(popup);

	auto soldierPic = Sprite::create("sixth_soldier_upgrade.jpg");
	soldierPic->setPosition((Point(visibleSize.width / 2.8, visibleSize.height / 2)));
	soldierPic->setTag(52);
	uiLayer->addChild(soldierPic);

	auto label = Label::createWithTTF("Galactic Stone", "fonts/Marker Felt.ttf", 18);
	label->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 1.6)));
	label->setTag(53);
	uiLayer->addChild(label);

	if (galacticStoneRank == 0)
	{
		auto stars = Sprite::create("emptyStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (galacticStoneRank == 1)
	{
		auto stars = Sprite::create("oneStar.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (galacticStoneRank == 2)
	{
		auto stars = Sprite::create("twoStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (galacticStoneRank == 3)
	{
		auto stars = Sprite::create("threeStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}
	else if (galacticStoneRank == 4)
	{
		auto stars = Sprite::create("fourStars.png");
		stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		stars->setTag(54);
		uiLayer->addChild(stars);
	}

	auto health = Label::createWithTTF("HP:  " + galacticStoneHealth, "fonts/Marker Felt.ttf", 14);
	health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	health->setTag(55);
	uiLayer->addChild(health);


	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.55, visibleSize.height / 2.7)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(57);
	uiLayer->addChild(cancelButtonMenu);

	if (galacticStoneRank < 4)
	{
		auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
												   "upgrade_soldier.jpg",
												   CC_CALLBACK_1(UpgradeScene::confirmSixthItemUpgrade, this));

		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
		upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
		upgradeTheSoldierMenu->setTag(58);
		uiLayer->addChild(upgradeTheSoldierMenu);
	}
	else
	{
		auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
		upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
		upgradeTheSoldier->setTag(58);
		uiLayer->addChild(upgradeTheSoldier);
	}
}

void UpgradeScene::confirmSixthItemUpgrade(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto backDrop = MenuItemImage::create("blockOut_Content2.png",
											   "blockOut_Content2.png",
											   CC_CALLBACK_1(UpgradeScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(59);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_upgrade_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(60);
	uiLayer->addChild(popup);

	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(UpgradeScene::cancelFromConfirmUpgrade, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(61);
	uiLayer->addChild(cancelButtonMenu);


	auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
											   "upgrade_soldier.jpg",
											   CC_CALLBACK_1(UpgradeScene::upgradeSixthItemStats, this));

	upgradeTheSoldier->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
	upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
	upgradeTheSoldierMenu->setTag(62);
	uiLayer->addChild(upgradeTheSoldierMenu);

	auto label = Label::createWithTTF("Upgrade galactic stones?", "fonts/Marker Felt.ttf", 12);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(63);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.jpg");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int upgradeCost = getCostForItemRank(galacticStoneRank);
	sprintf(money,"%d", upgradeCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void UpgradeScene::upgradeSixthItemStats(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int costOfUpgrade = getCostForItemRank(galacticStoneRank);
	if (moneyTotal >= costOfUpgrade)
	{
		moneyTotal = moneyTotal - costOfUpgrade;
		uiLayer->removeChildByTag(54,1);
		uiLayer->removeChildByTag(55,1);
		uiLayer->removeChildByTag(56,1);
		uiLayer->removeChildByTag(58,1);
		uiLayer->removeChildByTag(59,1);
		uiLayer->removeChildByTag(60,1);
		uiLayer->removeChildByTag(61,1);
		uiLayer->removeChildByTag(62,1);
		uiLayer->removeChildByTag(63,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		galacticStoneRank = galacticStoneRank + 1;

		if (galacticStoneRank == 1)
		{
			galacticStoneHealth = "460";
		}
		else if (galacticStoneRank == 2)
		{
			galacticStoneHealth = "550";
		}
		else if (galacticStoneRank == 3)
		{
			galacticStoneHealth = "610";
		}
		else if (galacticStoneRank == 4)
		{
			galacticStoneHealth = "760";
		}

		if (galacticStoneRank == 0)
		{
			auto stars = Sprite::create("emptyStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (galacticStoneRank == 1)
		{
			auto stars = Sprite::create("oneStar.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (galacticStoneRank == 2)
		{
			auto stars = Sprite::create("twoStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (galacticStoneRank == 3)
		{
			auto stars = Sprite::create("threeStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}
		else if (galacticStoneRank == 4)
		{
			auto stars = Sprite::create("fourStars.png");
			stars->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
			stars->setTag(54);
			uiLayer->addChild(stars);
		}

		auto health = Label::createWithTTF("HP:  " + galacticStoneHealth, "fonts/Marker Felt.ttf", 14);
		health->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		health->setTag(55);
		uiLayer->addChild(health);

		if (galacticStoneRank < 4)
		{
			auto upgradeTheSoldier = MenuItemImage::create("upgrade_soldier.jpg",
													   "upgrade_soldier.jpg",
													   CC_CALLBACK_1(UpgradeScene::confirmSixthItemUpgrade, this));

			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			auto upgradeTheSoldierMenu = Menu::create(upgradeTheSoldier, NULL);
			upgradeTheSoldierMenu->setPosition(Vec2::ZERO);
			upgradeTheSoldierMenu->setTag(58);
			uiLayer->addChild(upgradeTheSoldierMenu);
		}
		else
		{
			auto upgradeTheSoldier = Sprite::create("upgrade_soldier.jpg");
			upgradeTheSoldier->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.7)));
			upgradeTheSoldier->setTag(58);
			uiLayer->addChild(upgradeTheSoldier);
		}
	}
	else
	{
		auto backDrop = MenuItemImage::create("blockOut_Content2.png",
												   "blockOut_Content2.png",
												   CC_CALLBACK_1(UpgradeScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(36);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.jpg");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(37);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("Not enough money.", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		label->setTag(38);
		uiLayer->addChild(label);

		auto okButton = MenuItemImage::create("cancel-button.jpg",
												   "cancel-button.jpg",
												   CC_CALLBACK_1(UpgradeScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}
