/*
 * CombatScene.cpp
 *
 *  Created on: March 27, 2015
 *      Author: Kristen Ernst
 */

#include "CombatScene.h"

Scene * CombatScene::createScene()
{
    auto scene = CombatScene::create();

    return scene;
}


bool CombatScene::init()
{
    // Call super init first
    if(!Scene::init())
    {
        return false;
    }

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
											   CC_CALLBACK_1(CombatScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(89);
	baseLayer->addChild(backDropLayer);

	auto leftArrow = MenuItemImage::create("left_arrow.png",
												   "left_arrow.png",
												   CC_CALLBACK_1(CombatScene::toThirdFightMenu, this));    // position the label on the center of the screen

	leftArrow->setPosition((Point(visibleSize.width / 10, visibleSize.height / 2)));
	auto leftArrowMenu = Menu::create(leftArrow, NULL);
	leftArrowMenu->setPosition(Vec2::ZERO);
	leftArrowMenu->setTag(40);
	uiLayer->addChild(leftArrowMenu);

	auto rightArrow = MenuItemImage::create("right_arrow.png",
												   "right_arrow.png",
												   CC_CALLBACK_1(CombatScene::toSecondFightMenu, this));    // position the label on the center of the screen

	rightArrow->setPosition((Point(visibleSize.width - (visibleSize.width / 8) , visibleSize.height / 2)));

	auto rightArrowMenu = Menu::create(rightArrow, NULL);
	rightArrowMenu->setPosition(Vec2::ZERO);
	rightArrowMenu->setTag(41);
	uiLayer->addChild(rightArrowMenu);

	auto label = Label::createWithTTF("Battle #1", "fonts/Marker Felt.ttf", 35);
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
								origin.y + visibleSize.height - (visibleSize.height / 7)));
	label->setTag(42);
	hudLayer->addChild(label);

	auto firstAsteroid = Sprite::create("firstBattle.png");
	firstAsteroid->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	firstAsteroid->setTag(43);
	hudLayer->addChild(firstAsteroid);

	auto exitButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(CombatScene::loadMainView, this));

	exitButton->setPosition((Point(visibleSize.width / 1.6, visibleSize.height / 6)));
	auto exitMenu = Menu::create(exitButton, NULL);
	exitMenu->setPosition(Vec2::ZERO);
	uiLayer->addChild(exitMenu);

	auto fightButton = MenuItemImage::create("fight.jpg",
											   "fight.jpg",
											   CC_CALLBACK_1(CombatScene::loadMainView, this));

	fightButton->setPosition((Point(visibleSize.width / 2.4, visibleSize.height / 6)));
	auto fightButtonMenu = Menu::create(fightButton, NULL);
	fightButtonMenu->setPosition(Vec2::ZERO);
	fightButtonMenu->setTag(44);
	uiLayer->addChild(fightButtonMenu);


	this->addChild(baseLayer, 0);
	this->addChild(animationLayer, 1);
	this->addChild(hudLayer, 2);
	this->addChild(uiLayer, 3);

	return true;
}

void CombatScene::toFirstFightMenu(Ref* pSender)
{
	uiLayer->removeChildByTag(40,1);
	uiLayer->removeChildByTag(41,1);
	hudLayer->removeChildByTag(42,1);
	hudLayer->removeChildByTag(43,1);
	uiLayer->removeChildByTag(44,1);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto leftArrow = MenuItemImage::create("left_arrow.png",
												   "left_arrow.png",
												   CC_CALLBACK_1(CombatScene::toThirdFightMenu, this));    // position the label on the center of the screen

	leftArrow->setPosition((Point(visibleSize.width / 10, visibleSize.height / 2)));
	auto leftArrowMenu = Menu::create(leftArrow, NULL);
	leftArrowMenu->setPosition(Vec2::ZERO);
	leftArrowMenu->setTag(40);
	uiLayer->addChild(leftArrowMenu);

	auto rightArrow = MenuItemImage::create("right_arrow.png",
												   "right_arrow.png",
												   CC_CALLBACK_1(CombatScene::toSecondFightMenu, this));    // position the label on the center of the screen

	rightArrow->setPosition((Point(visibleSize.width - (visibleSize.width / 8) , visibleSize.height / 2)));

	auto rightArrowMenu = Menu::create(rightArrow, NULL);
	rightArrowMenu->setPosition(Vec2::ZERO);
	rightArrowMenu->setTag(41);
	uiLayer->addChild(rightArrowMenu);

	auto label = Label::createWithTTF("Battle #1", "fonts/Marker Felt.ttf", 35);
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
								origin.y + visibleSize.height - (visibleSize.height / 7)));
	label->setTag(42);
	hudLayer->addChild(label);

	auto firstAsteroid = Sprite::create("firstBattle.png");
	firstAsteroid->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	firstAsteroid->setTag(43);
	hudLayer->addChild(firstAsteroid);

	auto fightButton = MenuItemImage::create("fight.jpg",
											   "fight.jpg",
											   CC_CALLBACK_1(CombatScene::loadMainView, this));

	fightButton->setPosition((Point(visibleSize.width / 2.4, visibleSize.height / 6)));
	auto fightButtonMenu = Menu::create(fightButton, NULL);
	fightButtonMenu->setPosition(Vec2::ZERO);
	fightButtonMenu->setTag(44);
	uiLayer->addChild(fightButtonMenu);
}

void CombatScene::toSecondFightMenu(Ref* pSender)
{
	uiLayer->removeChildByTag(40,1);
	uiLayer->removeChildByTag(41,1);
	hudLayer->removeChildByTag(42,1);
	hudLayer->removeChildByTag(43,1);
	uiLayer->removeChildByTag(44,1);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto leftArrow = MenuItemImage::create("left_arrow.png",
												   "left_arrow.png",
												   CC_CALLBACK_1(CombatScene::toFirstFightMenu, this));    // position the label on the center of the screen

	leftArrow->setPosition((Point(visibleSize.width / 10, visibleSize.height / 2)));
	auto leftArrowMenu = Menu::create(leftArrow, NULL);
	leftArrowMenu->setPosition(Vec2::ZERO);
	leftArrowMenu->setTag(40);
	uiLayer->addChild(leftArrowMenu);

	auto rightArrow = MenuItemImage::create("right_arrow.png",
												   "right_arrow.png",
												   CC_CALLBACK_1(CombatScene::toThirdFightMenu, this));    // position the label on the center of the screen

	rightArrow->setPosition((Point(visibleSize.width - (visibleSize.width / 8) , visibleSize.height / 2)));

	auto rightArrowMenu = Menu::create(rightArrow, NULL);
	rightArrowMenu->setPosition(Vec2::ZERO);
	rightArrowMenu->setTag(41);
	uiLayer->addChild(rightArrowMenu);

	auto label = Label::createWithTTF("Battle #2", "fonts/Marker Felt.ttf", 35);
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
								origin.y + visibleSize.height - (visibleSize.height / 7)));
	label->setTag(42);
	hudLayer->addChild(label);

	auto firstAsteroid = Sprite::create("secondBattle.png");
	firstAsteroid->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	firstAsteroid->setTag(43);
	hudLayer->addChild(firstAsteroid);

	auto fightButton = MenuItemImage::create("fight.jpg",
											   "fight.jpg",
											   CC_CALLBACK_1(CombatScene::loadMainView, this));

	fightButton->setPosition((Point(visibleSize.width / 2.4, visibleSize.height / 6)));
	auto fightButtonMenu = Menu::create(fightButton, NULL);
	fightButtonMenu->setPosition(Vec2::ZERO);
	fightButtonMenu->setTag(44);
	uiLayer->addChild(fightButtonMenu);
}

void CombatScene::toThirdFightMenu(Ref* pSender)
{
	uiLayer->removeChildByTag(40,1);
	uiLayer->removeChildByTag(41,1);
	hudLayer->removeChildByTag(42,1);
	hudLayer->removeChildByTag(43,1);
	uiLayer->removeChildByTag(44,1);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto leftArrow = MenuItemImage::create("left_arrow.png",
												   "left_arrow.png",
												   CC_CALLBACK_1(CombatScene::toSecondFightMenu, this));    // position the label on the center of the screen

	leftArrow->setPosition((Point(visibleSize.width / 10, visibleSize.height / 2)));
	auto leftArrowMenu = Menu::create(leftArrow, NULL);
	leftArrowMenu->setPosition(Vec2::ZERO);
	leftArrowMenu->setTag(40);
	uiLayer->addChild(leftArrowMenu);

	auto rightArrow = MenuItemImage::create("right_arrow.png",
												   "right_arrow.png",
												   CC_CALLBACK_1(CombatScene::toFirstFightMenu, this));    // position the label on the center of the screen

	rightArrow->setPosition((Point(visibleSize.width - (visibleSize.width / 8) , visibleSize.height / 2)));

	auto rightArrowMenu = Menu::create(rightArrow, NULL);
	rightArrowMenu->setPosition(Vec2::ZERO);
	rightArrowMenu->setTag(41);
	uiLayer->addChild(rightArrowMenu);

	auto label = Label::createWithTTF("Battle #3", "fonts/Marker Felt.ttf", 35);
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
								origin.y + visibleSize.height - (visibleSize.height / 7)));
	label->setTag(42);
	hudLayer->addChild(label);

	auto firstAsteroid = Sprite::create("thirdBattle.png");
	firstAsteroid->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	firstAsteroid->setTag(43);
	hudLayer->addChild(firstAsteroid);

	auto fightButton = MenuItemImage::create("fight.jpg",
											   "fight.jpg",
											   CC_CALLBACK_1(CombatScene::loadMainView, this));

	fightButton->setPosition((Point(visibleSize.width / 2.4, visibleSize.height / 6)));
	auto fightButtonMenu = Menu::create(fightButton, NULL);
	fightButtonMenu->setPosition(Vec2::ZERO);
	fightButtonMenu->setTag(44);
	uiLayer->addChild(fightButtonMenu);
}

void CombatScene::doNothing(Ref* pSender)
{
}

void CombatScene::loadMainView(Ref* pSender)
{
	this->removeAllChildren();
}

