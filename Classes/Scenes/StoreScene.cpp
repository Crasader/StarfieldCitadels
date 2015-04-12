/*
 * StoreScene.cpp
 *
 *  Created on: March 28, 2015
 *      Author: Kristen Ernst
 */

#include "StoreScene.h"

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

Scene * StoreScene::createScene()
{
    auto scene = StoreScene::create();

    return scene;
}

StoreScene::StoreScene()
{
	init();
}

StoreScene::~StoreScene()
{
}

bool StoreScene::init()
{
    // Call super init first
    if(!Scene::init())
    {
        return false;
    }


    boughtHoriWall = false;
	boughtVerWall = false;
	boughtHoriPlasma = false;
	boughtVerPlasma = false;
	boughtStarDustTree = false;
	boughtGalacticStone = false;


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	currentTouchedPoint = origin;

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
											   CC_CALLBACK_1(StoreScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(89);
	baseLayer->addChild(backDropLayer);

   	auto sideBuildMenu = Sprite::create("buildMenu.jpg");
   	sideBuildMenu->setPosition((Point(visibleSize.width / 1.25, visibleSize.height / 2)));
   	sideBuildMenu->setTag(80);
   	hudLayer->addChild(sideBuildMenu);

   	auto exitButton = MenuItemImage::create("exit_button.png",
   											   "exit_button.png",
   											   CC_CALLBACK_1(StoreScene::loadMainView, this));

   	exitButton->setPosition((Point(visibleSize.width - (visibleSize.width / 10), visibleSize.height - (visibleSize.height/10))));
   	auto exitMenu = Menu::create(exitButton, NULL);
   	exitMenu->setPosition(Vec2::ZERO);
   	uiLayer->addChild(exitMenu);

   	auto label = Label::createWithTTF("Build", "fonts/Marker Felt.ttf", 40);
   	label->setPosition((Point(visibleSize.width - (visibleSize.width / 3.7), visibleSize.height - (visibleSize.height/10))));
   	label->setTag(81);
   	hudLayer->addChild(label);

   	auto firstBuild = MenuItemImage::create("upgrade_the_soldier.png",
   											   "upgrade_the_soldier.png",
   											   CC_CALLBACK_1(StoreScene::buildFirstItem, this));

   	firstBuild->setPosition((Point(visibleSize.width / 1.42, visibleSize.height / 1.54)));
   	auto firstBuildMenu = Menu::create(firstBuild, NULL);
   	firstBuildMenu->setPosition(Vec2::ZERO);
   	firstBuildMenu->setTag(82);
   	uiLayer->addChild(firstBuildMenu);

   	auto secondBuild = MenuItemImage::create("upgrade_the_soldier.png",
   											   "upgrade_the_soldier.png",
   											   CC_CALLBACK_1(StoreScene::buildSecondItem, this));

   	secondBuild->setPosition((Point(visibleSize.width / 1.12, visibleSize.height / 1.54)));
   	auto secondBuildMenu = Menu::create(secondBuild, NULL);
   	secondBuildMenu->setPosition(Vec2::ZERO);
   	secondBuildMenu->setTag(83);
   	uiLayer->addChild(secondBuildMenu);

   	auto thirdBuild = MenuItemImage::create("upgrade_the_soldier.png",
   											   "upgrade_the_soldier.png",
   											   CC_CALLBACK_1(StoreScene::buildThirdItem, this));

   	thirdBuild->setPosition((Point(visibleSize.width / 1.42, visibleSize.height / 2.45)));
   	auto thirdBuildMenu = Menu::create(thirdBuild, NULL);
   	thirdBuildMenu->setPosition(Vec2::ZERO);
   	thirdBuildMenu->setTag(84);
   	uiLayer->addChild(thirdBuildMenu);

   	auto fourthBuild = MenuItemImage::create("upgrade_the_soldier.png",
   											   "upgrade_the_soldier.png",
   											   CC_CALLBACK_1(StoreScene::buildFourthItem, this));

   	fourthBuild->setPosition((Point(visibleSize.width / 1.12, visibleSize.height / 2.45)));
   	auto fourthBuildMenu = Menu::create(fourthBuild, NULL);
   	fourthBuildMenu->setPosition(Vec2::ZERO);
   	fourthBuildMenu->setTag(85);
   	uiLayer->addChild(fourthBuildMenu);

   	auto fifthBuild = MenuItemImage::create("upgrade_the_soldier.png",
   											   "upgrade_the_soldier.png",
   											   CC_CALLBACK_1(StoreScene::buildFifthItem, this));

   	fifthBuild->setPosition((Point(visibleSize.width / 1.42, visibleSize.height / 6)));
   	auto fifthBuildMenu = Menu::create(fifthBuild, NULL);
   	fifthBuildMenu->setPosition(Vec2::ZERO);
   	fifthBuildMenu->setTag(86);
   	uiLayer->addChild(fifthBuildMenu);

   	auto sixthBuild = MenuItemImage::create("upgrade_the_soldier.png",
   											   "upgrade_the_soldier.png",
   											   CC_CALLBACK_1(StoreScene::buildSixthItem, this));

   	sixthBuild->setPosition((Point(visibleSize.width / 1.12, visibleSize.height / 6)));
   	auto sixthBuildMenu = Menu::create(sixthBuild, NULL);
   	sixthBuildMenu->setPosition(Vec2::ZERO);
   	sixthBuildMenu->setTag(87);
   	uiLayer->addChild(sixthBuildMenu);


	this->addChild(baseLayer, 0);
	this->addChild(animationLayer, 1);
	this->addChild(hudLayer, 2);
	this->addChild(uiLayer, 3);

	return true;
}

void StoreScene::setUpPreviousBuiltItems()
{
	for(int i = 0; i < builtItemNumbers.size(); i++)
	{
		if(builtItemNumbers.at(i) == 1)
		{
			auto firstItem = Sprite::create("star.png");
			firstItem->setPosition(builtItemLocations.at(i));
			baseLayer->addChild(firstItem);
		}
		else if(builtItemNumbers.at(i) == 2)
		{
			auto secondItem = Sprite::create("star.png");
			secondItem->setPosition(builtItemLocations.at(i));
			baseLayer->addChild(secondItem);
		}
		else if(builtItemNumbers.at(i) == 3)
		{
			auto thirdItem = Sprite::create("star.png");
			thirdItem->setPosition(builtItemLocations.at(i));
			baseLayer->addChild(thirdItem);
		}
		else if(builtItemNumbers.at(i) == 4)
		{
			auto fourthItem = Sprite::create("star.png");
			fourthItem->setPosition(builtItemLocations.at(i));
			baseLayer->addChild(fourthItem);
		}
		else if(builtItemNumbers.at(i) == 5)
		{
			auto fifthItem = Sprite::create("star.png");
			fifthItem->setPosition(builtItemLocations.at(i));
			baseLayer->addChild(fifthItem);
		}
		else if(builtItemNumbers.at(i) == 6)
		{
			auto sixthItem = Sprite::create("star.png");
			sixthItem->setPosition(builtItemLocations.at(i));
			baseLayer->addChild(sixthItem);
		}
	}
}

void StoreScene::cancelFromPurchase(Ref* pSender)
{
	uiLayer->removeChildByTag(36,1);
	uiLayer->removeChildByTag(37,1);
	uiLayer->removeChildByTag(38,1);
	uiLayer->removeChildByTag(39,1);
}

void StoreScene::setMoneyTotal(int money)
{
	moneyTotal = money;
}

void StoreScene::setMainScene(MainScene* scene)
{
	mainScene = scene;
}

void StoreScene::setUpBuiltItemNums(vector<int> itemNums)
{
	builtItemNumbers = itemNums;
}

void StoreScene::setUpBuiltLocations(vector<Vec2> locations)
{
	builtItemLocations = locations;
}

void StoreScene::loadMainView(Ref* pSender)
{
	//auto mainScene2 = MainScene::create();
	//Director::getInstance()->replaceScene(mainScene2);

	mainScene->setItemNumbers(builtItemNumbers);
	mainScene->setLocations(builtItemLocations);
	mainScene->buildTheItems();
	mainScene->setMoneyTotal(moneyTotal);
	mainScene->repostMoneyTotal();
	this->removeAllChildren();
}


void StoreScene::toBuildMenuStep(Ref* pSender)
{
	//Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	uiLayer->removeChildByTag(94,1);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sideBuildMenu = Sprite::create("buildMenu.jpg");
	sideBuildMenu->setPosition((Point(visibleSize.width / 1.25, visibleSize.height / 2)));
	sideBuildMenu->setTag(80);
	hudLayer->addChild(sideBuildMenu);

	auto label = Label::createWithTTF("Build", "fonts/Marker Felt.ttf", 40);
	label->setPosition((Point(visibleSize.width - (visibleSize.width / 3.7), visibleSize.height - (visibleSize.height/10))));
	label->setTag(81);
	hudLayer->addChild(label);

	auto firstBuild = MenuItemImage::create("upgrade_the_soldier.png",
											   "upgrade_the_soldier.png",
											   CC_CALLBACK_1(StoreScene::buildFirstItem, this));

	firstBuild->setPosition((Point(visibleSize.width / 1.42, visibleSize.height / 1.54)));
	auto firstBuildMenu = Menu::create(firstBuild, NULL);
	firstBuildMenu->setPosition(Vec2::ZERO);
	firstBuildMenu->setTag(82);
	uiLayer->addChild(firstBuildMenu);

	auto secondBuild = MenuItemImage::create("upgrade_the_soldier.png",
											   "upgrade_the_soldier.png",
											   CC_CALLBACK_1(StoreScene::buildSecondItem, this));

	secondBuild->setPosition((Point(visibleSize.width / 1.12, visibleSize.height / 1.54)));
	auto secondBuildMenu = Menu::create(secondBuild, NULL);
	secondBuildMenu->setPosition(Vec2::ZERO);
	secondBuildMenu->setTag(83);
	uiLayer->addChild(secondBuildMenu);

	auto thirdBuild = MenuItemImage::create("upgrade_the_soldier.png",
											   "upgrade_the_soldier.png",
											   CC_CALLBACK_1(StoreScene::buildThirdItem, this));

	thirdBuild->setPosition((Point(visibleSize.width / 1.42, visibleSize.height / 2.45)));
	auto thirdBuildMenu = Menu::create(thirdBuild, NULL);
	thirdBuildMenu->setPosition(Vec2::ZERO);
	thirdBuildMenu->setTag(84);
	uiLayer->addChild(thirdBuildMenu);

	auto fourthBuild = MenuItemImage::create("upgrade_the_soldier.png",
											   "upgrade_the_soldier.png",
											   CC_CALLBACK_1(StoreScene::buildFourthItem, this));

	fourthBuild->setPosition((Point(visibleSize.width / 1.12, visibleSize.height / 2.45)));
	auto fourthBuildMenu = Menu::create(fourthBuild, NULL);
	fourthBuildMenu->setPosition(Vec2::ZERO);
	fourthBuildMenu->setTag(85);
	uiLayer->addChild(fourthBuildMenu);

	auto fifthBuild = MenuItemImage::create("upgrade_the_soldier.png",
											   "upgrade_the_soldier.png",
											   CC_CALLBACK_1(StoreScene::buildFifthItem, this));

	fifthBuild->setPosition((Point(visibleSize.width / 1.42, visibleSize.height / 6)));
	auto fifthBuildMenu = Menu::create(fifthBuild, NULL);
	fifthBuildMenu->setPosition(Vec2::ZERO);
	fifthBuildMenu->setTag(86);
	uiLayer->addChild(fifthBuildMenu);

	auto sixthBuild = MenuItemImage::create("upgrade_the_soldier.png",
											   "upgrade_the_soldier.png",
											   CC_CALLBACK_1(StoreScene::buildSixthItem, this));

	sixthBuild->setPosition((Point(visibleSize.width / 1.12, visibleSize.height / 6)));
	auto sixthBuildMenu = Menu::create(sixthBuild, NULL);
	sixthBuildMenu->setPosition(Vec2::ZERO);
	sixthBuildMenu->setTag(87);
	uiLayer->addChild(sixthBuildMenu);
}


void StoreScene::buildFirstItem(Ref* pSender)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    this->removeChildByName(hudLayer->getName(), 1);
    this->removeChildByName(uiLayer->getName(), 1);

	hudLayer->removeChildByTag(80,1);
	this->removeChildByTag(80,1);
	hudLayer->removeChildByTag(81,1);
	this->removeChildByTag(81,1);
	uiLayer->removeChildByTag(82,1);
	this->removeChildByTag(82,1);
	uiLayer->removeChildByTag(83,1);
	this->removeChildByTag(83,1);
	uiLayer->removeChildByTag(84,1);
	this->removeChildByTag(84,1);
	uiLayer->removeChildByTag(85,1);
	this->removeChildByTag(85,1);
	uiLayer->removeChildByTag(86,1);
	this->removeChildByTag(86,1);
	uiLayer->removeChildByTag(87,1);
	this->removeChildByTag(87,1);
	this->addChild(hudLayer);
	this->addChild(uiLayer);

	auto buildButton = MenuItemImage::create("side_build_button.png",
											   "side_build_button.png",
											   CC_CALLBACK_1(StoreScene::toBuildMenuStep, this));

	buildButton->setPosition((Point(visibleSize.width - (visibleSize.width / 10), visibleSize.height / 11)));
	auto buildButtonMenu = Menu::create(buildButton, NULL);
	buildButtonMenu->setPosition(Vec2::ZERO);
	buildButtonMenu->setTag(94);
	uiLayer->addChild(buildButtonMenu);


	auto listenerForwardButton = EventListenerTouchOneByOne::create();
	listenerForwardButton->setEnabled(true);
	listenerForwardButton->setSwallowTouches(true);

	listenerForwardButton->onTouchBegan = CC_CALLBACK_2(StoreScene::touchChecker, this);
	// trigger when you let up
	listenerForwardButton->onTouchEnded = CC_CALLBACK_2(StoreScene::createFirstItem, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerForwardButton, buildButton);

}

bool StoreScene::touchChecker(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 touchPoint = touch->getLocation();
	if(((touchPoint.x > (visibleSize.width / 1.33)) && (touchPoint.y < (visibleSize.height / 5.5))) || ((touchPoint.x > (visibleSize.width / 1.28)) && (touchPoint.y > (visibleSize.height / 1.28))))
	{
		return false;
	}
	else
	{
		return true;
	}
}


void StoreScene::createFirstItem(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Vec2 touchPoint = touch->getLocation();
    Size visibleSize = Director::getInstance()->getVisibleSize();

	currentTouchedPoint = touchPoint;

	auto firstItem = Sprite::create("star.png");
	firstItem->setPosition(touchPoint);
	firstItem->setTag(88);
	uiLayer->addChild(firstItem);

	auto backDrop = MenuItemImage::create("blockOut_Content2.png",
											   "blockOut_Content2.png",
											   CC_CALLBACK_1(StoreScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(89);
	uiLayer->addChild(backDropLayer);


	auto sideBuildMenu = Sprite::create("popup_build_menu.jpg");
	sideBuildMenu->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	sideBuildMenu->setTag(90);
	uiLayer->addChild(sideBuildMenu);


	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(StoreScene::cancelFromConfirmBuild, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(91);
	uiLayer->addChild(cancelButtonMenu);


	auto popUpBuild = MenuItemImage::create("popup_build_button.png",
											   "popup_build_button.png",
											   CC_CALLBACK_1(StoreScene::buildTheFirstItem, this));

	popUpBuild->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto popUpBuildMenu = Menu::create(popUpBuild, NULL);
	popUpBuildMenu->setPosition(Vec2::ZERO);
	popUpBuildMenu->setTag(92);
	uiLayer->addChild(popUpBuildMenu);

	auto label = Label::createWithTTF("Build a horizontal wall?", "fonts/Marker Felt.ttf", 14);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(93);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.jpg");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int itemCost = 350;
	sprintf(money,"%d", itemCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void StoreScene::buildTheFirstItem(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (moneyTotal >= 350)
	{
		moneyTotal = moneyTotal - 350;
		uiLayer->removeChildByTag(88,1);
		uiLayer->removeChildByTag(89,1);
		uiLayer->removeChildByTag(90,1);
		uiLayer->removeChildByTag(91,1);
		uiLayer->removeChildByTag(92,1);
		uiLayer->removeChildByTag(93,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		auto firstItem = Sprite::create("star.png");
		firstItem->setPosition(currentTouchedPoint);
		hudLayer->addChild(firstItem);

		builtItemNumbers.push_back(1);
		builtItemLocations.push_back(currentTouchedPoint);
		boughtHoriWall = true;
		mainScene->setBoughtItemOne(boughtHoriWall);
	}
	else
	{
		auto backDrop = MenuItemImage::create("blockOut_Content2.png",
												   "blockOut_Content2.png",
												   CC_CALLBACK_1(StoreScene::doNothing, this));

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
												   CC_CALLBACK_1(StoreScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void StoreScene::buildSecondItem(Ref* pSender)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    this->removeChildByName(hudLayer->getName(), 1);
	this->removeChildByName(uiLayer->getName(), 1);

	hudLayer->removeChildByTag(80,1);
	this->removeChildByTag(80,1);
	hudLayer->removeChildByTag(81,1);
	this->removeChildByTag(81,1);
	uiLayer->removeChildByTag(82,1);
	this->removeChildByTag(82,1);
	uiLayer->removeChildByTag(83,1);
	this->removeChildByTag(83,1);
	uiLayer->removeChildByTag(84,1);
	this->removeChildByTag(84,1);
	uiLayer->removeChildByTag(85,1);
	this->removeChildByTag(85,1);
	uiLayer->removeChildByTag(86,1);
	this->removeChildByTag(86,1);
	uiLayer->removeChildByTag(87,1);
	this->removeChildByTag(87,1);
	this->addChild(hudLayer);
	this->addChild(uiLayer);


	auto buildButton = MenuItemImage::create("side_build_button.png",
											   "side_build_button.png",
											   CC_CALLBACK_1(StoreScene::toBuildMenuStep, this));

	buildButton->setPosition((Point(visibleSize.width - (visibleSize.width / 10), visibleSize.height / 11)));
	auto buildButtonMenu = Menu::create(buildButton, NULL);
	buildButtonMenu->setPosition(Vec2::ZERO);
	buildButtonMenu->setTag(94);
	uiLayer->addChild(buildButtonMenu);


	auto listenerForwardButton = EventListenerTouchOneByOne::create();
	listenerForwardButton->setEnabled(true);
	listenerForwardButton->setSwallowTouches(true);

	listenerForwardButton->onTouchBegan = CC_CALLBACK_2(StoreScene::touchChecker, this);
	// trigger when you let up
	listenerForwardButton->onTouchEnded = CC_CALLBACK_2(StoreScene::createSecondItem, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerForwardButton, buildButton);
}



void StoreScene::createSecondItem(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Vec2 touchPoint = touch->getLocation();
    Size visibleSize = Director::getInstance()->getVisibleSize();
	currentTouchedPoint = touchPoint;

	auto secondItem = Sprite::create("star.png");
	secondItem->setPosition(touchPoint);
	secondItem->setTag(88);
	uiLayer->addChild(secondItem);

	auto backDrop = MenuItemImage::create("blockOut_Content2.png",
											   "blockOut_Content2.png",
											   CC_CALLBACK_1(StoreScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(89);
	uiLayer->addChild(backDropLayer);


	auto sideBuildMenu = Sprite::create("popup_build_menu.jpg");
	sideBuildMenu->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	sideBuildMenu->setTag(90);
	uiLayer->addChild(sideBuildMenu);


	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(StoreScene::cancelFromConfirmBuild, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(91);
	uiLayer->addChild(cancelButtonMenu);


	auto popUpBuild = MenuItemImage::create("popup_build_button.png",
											   "popup_build_button.png",
											   CC_CALLBACK_1(StoreScene::buildTheSecondItem, this));

	popUpBuild->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto popUpBuildMenu = Menu::create(popUpBuild, NULL);
	popUpBuildMenu->setPosition(Vec2::ZERO);
	popUpBuildMenu->setTag(92);
	uiLayer->addChild(popUpBuildMenu);

	auto label = Label::createWithTTF("Build a vertical wall?", "fonts/Marker Felt.ttf", 14);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(93);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.jpg");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int itemCost = 350;
	sprintf(money,"%d", itemCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void StoreScene::buildTheSecondItem(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (moneyTotal >= 350)
	{
		moneyTotal = moneyTotal - 350;
		uiLayer->removeChildByTag(88,1);
		uiLayer->removeChildByTag(89,1);
		uiLayer->removeChildByTag(90,1);
		uiLayer->removeChildByTag(91,1);
		uiLayer->removeChildByTag(92,1);
		uiLayer->removeChildByTag(93,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		auto secondItem = Sprite::create("star.png");
		secondItem->setPosition(currentTouchedPoint);
		hudLayer->addChild(secondItem);

		builtItemNumbers.push_back(2);
		builtItemLocations.push_back(currentTouchedPoint);
		boughtVerWall = true;
		mainScene->setBoughtItemTwo(boughtVerWall);
	}
	else
	{
		auto backDrop = MenuItemImage::create("blockOut_Content2.png",
												   "blockOut_Content2.png",
												   CC_CALLBACK_1(StoreScene::doNothing, this));

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
												   CC_CALLBACK_1(StoreScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}


void StoreScene::buildThirdItem(Ref* pSender)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    this->removeChildByName(hudLayer->getName(), 1);
	this->removeChildByName(uiLayer->getName(), 1);

	hudLayer->removeChildByTag(80,1);
	this->removeChildByTag(80,1);
	hudLayer->removeChildByTag(81,1);
	this->removeChildByTag(81,1);
	uiLayer->removeChildByTag(82,1);
	this->removeChildByTag(82,1);
	uiLayer->removeChildByTag(83,1);
	this->removeChildByTag(83,1);
	uiLayer->removeChildByTag(84,1);
	this->removeChildByTag(84,1);
	uiLayer->removeChildByTag(85,1);
	this->removeChildByTag(85,1);
	uiLayer->removeChildByTag(86,1);
	this->removeChildByTag(86,1);
	uiLayer->removeChildByTag(87,1);
	this->removeChildByTag(87,1);
	this->addChild(hudLayer);
	this->addChild(uiLayer);

	auto buildButton = MenuItemImage::create("side_build_button.png",
											   "side_build_button.png",
											   CC_CALLBACK_1(StoreScene::toBuildMenuStep, this));

	buildButton->setPosition((Point(visibleSize.width - (visibleSize.width / 10), visibleSize.height / 11)));
	auto buildButtonMenu = Menu::create(buildButton, NULL);
	buildButtonMenu->setPosition(Vec2::ZERO);
	buildButtonMenu->setTag(94);
	uiLayer->addChild(buildButtonMenu);


	auto listenerForwardButton = EventListenerTouchOneByOne::create();
	listenerForwardButton->setEnabled(true);
	listenerForwardButton->setSwallowTouches(true);

	listenerForwardButton->onTouchBegan = CC_CALLBACK_2(StoreScene::touchChecker, this);
	// trigger when you let up
	listenerForwardButton->onTouchEnded = CC_CALLBACK_2(StoreScene::createThirdItem, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerForwardButton, buildButton);
}



void StoreScene::createThirdItem(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Vec2 touchPoint = touch->getLocation();
    Size visibleSize = Director::getInstance()->getVisibleSize();
	currentTouchedPoint = touchPoint;

	auto thirdItem = Sprite::create("star.png");
	thirdItem->setPosition(touchPoint);
	thirdItem->setTag(88);
	uiLayer->addChild(thirdItem);

	auto backDrop = MenuItemImage::create("blockOut_Content2.png",
											   "blockOut_Content2.png",
											   CC_CALLBACK_1(StoreScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(89);
	uiLayer->addChild(backDropLayer);


	auto sideBuildMenu = Sprite::create("popup_build_menu.jpg");
	sideBuildMenu->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	sideBuildMenu->setTag(90);
	uiLayer->addChild(sideBuildMenu);


	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(StoreScene::cancelFromConfirmBuild, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(91);
	uiLayer->addChild(cancelButtonMenu);


	auto popUpBuild = MenuItemImage::create("popup_build_button.png",
											   "popup_build_button.png",
											   CC_CALLBACK_1(StoreScene::buildTheThirdItem, this));

	popUpBuild->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto popUpBuildMenu = Menu::create(popUpBuild, NULL);
	popUpBuildMenu->setPosition(Vec2::ZERO);
	popUpBuildMenu->setTag(92);
	uiLayer->addChild(popUpBuildMenu);

	auto label = Label::createWithTTF("Build a horizontal plasma wall?", "fonts/Marker Felt.ttf", 14);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(93);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.jpg");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int itemCost = 800;
	sprintf(money,"%d", itemCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void StoreScene::buildTheThirdItem(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (moneyTotal >= 800)
	{
		moneyTotal = moneyTotal - 800;
		uiLayer->removeChildByTag(88,1);
		uiLayer->removeChildByTag(89,1);
		uiLayer->removeChildByTag(90,1);
		uiLayer->removeChildByTag(91,1);
		uiLayer->removeChildByTag(92,1);
		uiLayer->removeChildByTag(93,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		auto thirdItem = Sprite::create("star.png");
		thirdItem->setPosition(currentTouchedPoint);
		hudLayer->addChild(thirdItem);

		builtItemNumbers.push_back(3);
		builtItemLocations.push_back(currentTouchedPoint);
		boughtHoriPlasma = true;
		mainScene->setBoughtItemThree(boughtHoriPlasma);
	}
	else
	{
		auto backDrop = MenuItemImage::create("blockOut_Content2.png",
												   "blockOut_Content2.png",
												   CC_CALLBACK_1(StoreScene::doNothing, this));

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
												   CC_CALLBACK_1(StoreScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}


void StoreScene::buildFourthItem(Ref* pSender)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    this->removeChildByName(hudLayer->getName(), 1);
	this->removeChildByName(uiLayer->getName(), 1);

	hudLayer->removeChildByTag(80,1);
	this->removeChildByTag(80,1);
	hudLayer->removeChildByTag(81,1);
	this->removeChildByTag(81,1);
	uiLayer->removeChildByTag(82,1);
	this->removeChildByTag(82,1);
	uiLayer->removeChildByTag(83,1);
	this->removeChildByTag(83,1);
	uiLayer->removeChildByTag(84,1);
	this->removeChildByTag(84,1);
	uiLayer->removeChildByTag(85,1);
	this->removeChildByTag(85,1);
	uiLayer->removeChildByTag(86,1);
	this->removeChildByTag(86,1);
	uiLayer->removeChildByTag(87,1);
	this->removeChildByTag(87,1);
	this->addChild(hudLayer);
	this->addChild(uiLayer);

	auto buildButton = MenuItemImage::create("side_build_button.png",
											   "side_build_button.png",
											   CC_CALLBACK_1(StoreScene::toBuildMenuStep, this));

	buildButton->setPosition((Point(visibleSize.width - (visibleSize.width / 10), visibleSize.height / 11)));
	auto buildButtonMenu = Menu::create(buildButton, NULL);
	buildButtonMenu->setPosition(Vec2::ZERO);
	buildButtonMenu->setTag(94);
	uiLayer->addChild(buildButtonMenu);


	auto listenerForwardButton = EventListenerTouchOneByOne::create();
	listenerForwardButton->setEnabled(true);
	listenerForwardButton->setSwallowTouches(true);

	listenerForwardButton->onTouchBegan = CC_CALLBACK_2(StoreScene::touchChecker, this);
	// trigger when you let up
	listenerForwardButton->onTouchEnded = CC_CALLBACK_2(StoreScene::createFourthItem, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerForwardButton, buildButton);
}



void StoreScene::createFourthItem(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Vec2 touchPoint = touch->getLocation();
    Size visibleSize = Director::getInstance()->getVisibleSize();
	currentTouchedPoint = touchPoint;

	auto fourthItem = Sprite::create("star.png");
	fourthItem->setPosition(touchPoint);
	fourthItem->setTag(88);
	uiLayer->addChild(fourthItem);

	auto backDrop = MenuItemImage::create("blockOut_Content2.png",
											   "blockOut_Content2.png",
											   CC_CALLBACK_1(StoreScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(89);
	uiLayer->addChild(backDropLayer);


	auto sideBuildMenu = Sprite::create("popup_build_menu.jpg");
	sideBuildMenu->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	sideBuildMenu->setTag(90);
	uiLayer->addChild(sideBuildMenu);


	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(StoreScene::cancelFromConfirmBuild, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(91);
	uiLayer->addChild(cancelButtonMenu);


	auto popUpBuild = MenuItemImage::create("popup_build_button.png",
											   "popup_build_button.png",
											   CC_CALLBACK_1(StoreScene::buildTheFourthItem, this));

	popUpBuild->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto popUpBuildMenu = Menu::create(popUpBuild, NULL);
	popUpBuildMenu->setPosition(Vec2::ZERO);
	popUpBuildMenu->setTag(92);
	uiLayer->addChild(popUpBuildMenu);

	auto label = Label::createWithTTF("Build a vertical plasma wall?", "fonts/Marker Felt.ttf", 14);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(93);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.jpg");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int itemCost = 800;
	sprintf(money,"%d", itemCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void StoreScene::buildTheFourthItem(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (moneyTotal >= 800)
	{
		moneyTotal = moneyTotal - 800;
		uiLayer->removeChildByTag(88,1);
		uiLayer->removeChildByTag(89,1);
		uiLayer->removeChildByTag(90,1);
		uiLayer->removeChildByTag(91,1);
		uiLayer->removeChildByTag(92,1);
		uiLayer->removeChildByTag(93,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		auto fourthItem = Sprite::create("star.png");
		fourthItem->setPosition(currentTouchedPoint);
		hudLayer->addChild(fourthItem);

		builtItemNumbers.push_back(4);
		builtItemLocations.push_back(currentTouchedPoint);
		boughtVerPlasma = true;
		mainScene->setBoughtItemFour(boughtVerPlasma);
	}
	else
	{
		auto backDrop = MenuItemImage::create("blockOut_Content2.png",
												   "blockOut_Content2.png",
												   CC_CALLBACK_1(StoreScene::doNothing, this));

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
												   CC_CALLBACK_1(StoreScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void StoreScene::buildFifthItem(Ref* pSender)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    this->removeChildByName(hudLayer->getName(), 1);
	this->removeChildByName(uiLayer->getName(), 1);

	hudLayer->removeChildByTag(80,1);
	this->removeChildByTag(80,1);
	hudLayer->removeChildByTag(81,1);
	this->removeChildByTag(81,1);
	uiLayer->removeChildByTag(82,1);
	this->removeChildByTag(82,1);
	uiLayer->removeChildByTag(83,1);
	this->removeChildByTag(83,1);
	uiLayer->removeChildByTag(84,1);
	this->removeChildByTag(84,1);
	uiLayer->removeChildByTag(85,1);
	this->removeChildByTag(85,1);
	uiLayer->removeChildByTag(86,1);
	this->removeChildByTag(86,1);
	uiLayer->removeChildByTag(87,1);
	this->removeChildByTag(87,1);
	this->addChild(hudLayer);
	this->addChild(uiLayer);

	auto buildButton = MenuItemImage::create("side_build_button.png",
											   "side_build_button.png",
											   CC_CALLBACK_1(StoreScene::toBuildMenuStep, this));

	buildButton->setPosition((Point(visibleSize.width - (visibleSize.width / 10), visibleSize.height / 11)));
	auto buildButtonMenu = Menu::create(buildButton, NULL);
	buildButtonMenu->setPosition(Vec2::ZERO);
	buildButtonMenu->setTag(94);
	uiLayer->addChild(buildButtonMenu);


	auto listenerForwardButton = EventListenerTouchOneByOne::create();
	listenerForwardButton->setEnabled(true);
	listenerForwardButton->setSwallowTouches(true);

	listenerForwardButton->onTouchBegan = CC_CALLBACK_2(StoreScene::touchChecker, this);
	// trigger when you let up
	listenerForwardButton->onTouchEnded = CC_CALLBACK_2(StoreScene::createFifthItem, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerForwardButton, buildButton);
}



void StoreScene::createFifthItem(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Vec2 touchPoint = touch->getLocation();
    Size visibleSize = Director::getInstance()->getVisibleSize();
	currentTouchedPoint = touchPoint;

	auto fifthItem = Sprite::create("star.png");
	fifthItem->setPosition(touchPoint);
	fifthItem->setTag(88);
	uiLayer->addChild(fifthItem);

	auto backDrop = MenuItemImage::create("blockOut_Content2.png",
											   "blockOut_Content2.png",
											   CC_CALLBACK_1(StoreScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(89);
	uiLayer->addChild(backDropLayer);


	auto sideBuildMenu = Sprite::create("popup_build_menu.jpg");
	sideBuildMenu->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	sideBuildMenu->setTag(90);
	uiLayer->addChild(sideBuildMenu);


	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(StoreScene::cancelFromConfirmBuild, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(91);
	uiLayer->addChild(cancelButtonMenu);


	auto popUpBuild = MenuItemImage::create("popup_build_button.png",
											   "popup_build_button.png",
											   CC_CALLBACK_1(StoreScene::buildTheFifthItem, this));

	popUpBuild->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto popUpBuildMenu = Menu::create(popUpBuild, NULL);
	popUpBuildMenu->setPosition(Vec2::ZERO);
	popUpBuildMenu->setTag(92);
	uiLayer->addChild(popUpBuildMenu);

	auto label = Label::createWithTTF("Build a star-dust tree?", "fonts/Marker Felt.ttf", 14);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(93);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.jpg");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int itemCost = 500;
	sprintf(money,"%d", itemCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void StoreScene::buildTheFifthItem(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (moneyTotal >= 500)
	{
		moneyTotal = moneyTotal - 500;
		uiLayer->removeChildByTag(88,1);
		uiLayer->removeChildByTag(89,1);
		uiLayer->removeChildByTag(90,1);
		uiLayer->removeChildByTag(91,1);
		uiLayer->removeChildByTag(92,1);
		uiLayer->removeChildByTag(93,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		auto fifthItem = Sprite::create("star.png");
		fifthItem->setPosition(currentTouchedPoint);
		hudLayer->addChild(fifthItem);

		builtItemNumbers.push_back(5);
		builtItemLocations.push_back(currentTouchedPoint);
		boughtStarDustTree = true;
		mainScene->setBoughtItemFive(boughtStarDustTree);
	}
	else
	{
		auto backDrop = MenuItemImage::create("blockOut_Content2.png",
												   "blockOut_Content2.png",
												   CC_CALLBACK_1(StoreScene::doNothing, this));

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
												   CC_CALLBACK_1(StoreScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void StoreScene::buildSixthItem(Ref* pSender)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    this->removeChildByName(hudLayer->getName(), 1);
	this->removeChildByName(uiLayer->getName(), 1);

	hudLayer->removeChildByTag(80,1);
	this->removeChildByTag(80,1);
	hudLayer->removeChildByTag(81,1);
	this->removeChildByTag(81,1);
	uiLayer->removeChildByTag(82,1);
	this->removeChildByTag(82,1);
	uiLayer->removeChildByTag(83,1);
	this->removeChildByTag(83,1);
	uiLayer->removeChildByTag(84,1);
	this->removeChildByTag(84,1);
	uiLayer->removeChildByTag(85,1);
	this->removeChildByTag(85,1);
	uiLayer->removeChildByTag(86,1);
	this->removeChildByTag(86,1);
	uiLayer->removeChildByTag(87,1);
	this->removeChildByTag(87,1);
	this->addChild(hudLayer);
	this->addChild(uiLayer);

	auto buildButton = MenuItemImage::create("side_build_button.png",
											   "side_build_button.png",
											   CC_CALLBACK_1(StoreScene::toBuildMenuStep, this));

	buildButton->setPosition((Point(visibleSize.width - (visibleSize.width / 10), visibleSize.height / 11)));
	auto buildButtonMenu = Menu::create(buildButton, NULL);
	buildButtonMenu->setPosition(Vec2::ZERO);
	buildButtonMenu->setTag(94);
	uiLayer->addChild(buildButtonMenu);


	auto listenerForwardButton = EventListenerTouchOneByOne::create();
	listenerForwardButton->setEnabled(true);
	listenerForwardButton->setSwallowTouches(true);

	listenerForwardButton->onTouchBegan = CC_CALLBACK_2(StoreScene::touchChecker, this);
	// trigger when you let up
	listenerForwardButton->onTouchEnded = CC_CALLBACK_2(StoreScene::createSixthItem, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerForwardButton, buildButton);
}



void StoreScene::createSixthItem(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Vec2 touchPoint = touch->getLocation();
    Size visibleSize = Director::getInstance()->getVisibleSize();
	currentTouchedPoint = touchPoint;

	auto sixthItem = Sprite::create("star.png");
	sixthItem->setPosition(touchPoint);
	sixthItem->setTag(88);
	uiLayer->addChild(sixthItem);

	auto backDrop = MenuItemImage::create("blockOut_Content2.png",
											   "blockOut_Content2.png",
											   CC_CALLBACK_1(StoreScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(89);
	uiLayer->addChild(backDropLayer);


	auto sideBuildMenu = Sprite::create("popup_build_menu.jpg");
	sideBuildMenu->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	sideBuildMenu->setTag(90);
	uiLayer->addChild(sideBuildMenu);


	auto cancelButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(StoreScene::cancelFromConfirmBuild, this));

	cancelButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto cancelButtonMenu = Menu::create(cancelButton, NULL);
	cancelButtonMenu->setPosition(Vec2::ZERO);
	cancelButtonMenu->setTag(91);
	uiLayer->addChild(cancelButtonMenu);


	auto popUpBuild = MenuItemImage::create("popup_build_button.png",
											   "popup_build_button.png",
											   CC_CALLBACK_1(StoreScene::buildTheSixthItem, this));

	popUpBuild->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto popUpBuildMenu = Menu::create(popUpBuild, NULL);
	popUpBuildMenu->setPosition(Vec2::ZERO);
	popUpBuildMenu->setTag(92);
	uiLayer->addChild(popUpBuildMenu);

	auto label = Label::createWithTTF("Build a galactic stone?", "fonts/Marker Felt.ttf", 14);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(93);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.jpg");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int itemCost = 650;
	sprintf(money,"%d", itemCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void StoreScene::buildTheSixthItem(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (moneyTotal >= 650)
	{
		moneyTotal = moneyTotal - 650;
		uiLayer->removeChildByTag(88,1);
		uiLayer->removeChildByTag(89,1);
		uiLayer->removeChildByTag(90,1);
		uiLayer->removeChildByTag(91,1);
		uiLayer->removeChildByTag(92,1);
		uiLayer->removeChildByTag(93,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		auto sixthItem = Sprite::create("star.png");
		sixthItem->setPosition(currentTouchedPoint);
		hudLayer->addChild(sixthItem);

		builtItemNumbers.push_back(6);
		builtItemLocations.push_back(currentTouchedPoint);
		boughtGalacticStone = true;
		mainScene->setBoughtItemSix(boughtGalacticStone);
	}
	else
	{
		auto backDrop = MenuItemImage::create("blockOut_Content2.png",
												   "blockOut_Content2.png",
												   CC_CALLBACK_1(StoreScene::doNothing, this));

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
												   CC_CALLBACK_1(StoreScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void StoreScene::cancelFromConfirmBuild(Ref* pSender)
{
	uiLayer->removeChildByTag(88,1);
	uiLayer->removeChildByTag(89,1);
	uiLayer->removeChildByTag(90,1);
	uiLayer->removeChildByTag(91,1);
	uiLayer->removeChildByTag(92,1);
	uiLayer->removeChildByTag(93,1);
	uiLayer->removeChildByTag(34,1);
	uiLayer->removeChildByTag(35,1);
}

void StoreScene::doNothing(Ref* pSender)
{
}

