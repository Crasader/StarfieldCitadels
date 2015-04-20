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

    auto backDrop = MenuItemImage::create("fightBackground.png",
											   "fightBackground.png",
											   CC_CALLBACK_1(CombatScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(89);
	baseLayer->addChild(backDropLayer);

	auto leftArrow = MenuItemImage::create("left_arrow.png",
												   "left_arrowClicked.png",
												   CC_CALLBACK_1(CombatScene::toThirdFightMenu, this));    // position the label on the center of the screen

	leftArrow->setPosition((Point(visibleSize.width / 10, visibleSize.height / 2)));
	auto leftArrowMenu = Menu::create(leftArrow, NULL);
	leftArrowMenu->setPosition(Vec2::ZERO);
	leftArrowMenu->setTag(40);
	uiLayer->addChild(leftArrowMenu);

	auto rightArrow = MenuItemImage::create("right_arrow.png",
												   "right_arrowClicked.png",
												   CC_CALLBACK_1(CombatScene::toSecondFightMenu, this));    // position the label on the center of the screen

	rightArrow->setPosition((Point(visibleSize.width - (visibleSize.width / 9) , visibleSize.height / 2)));

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

	auto exitButton = MenuItemImage::create("cancel-button.png",
											   "cancel-buttonClicked.png",
											   CC_CALLBACK_1(CombatScene::loadMainView, this));

	exitButton->setPosition((Point(visibleSize.width / 1.6, visibleSize.height / 6)));
	auto exitMenu = Menu::create(exitButton, NULL);
	exitMenu->setPosition(Vec2::ZERO);
	uiLayer->addChild(exitMenu);

	auto fightButton = MenuItemImage::create("fight.png",
											   "fightClicked.png",
											   CC_CALLBACK_1(CombatScene::updateMessage, this));

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
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("toSideMenu.wav");
	uiLayer->removeChildByTag(40,1);
	uiLayer->removeChildByTag(41,1);
	hudLayer->removeChildByTag(42,1);
	hudLayer->removeChildByTag(43,1);
	uiLayer->removeChildByTag(44,1);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto leftArrow = MenuItemImage::create("left_arrow.png",
												   "left_arrowClicked.png",
												   CC_CALLBACK_1(CombatScene::toThirdFightMenu, this));    // position the label on the center of the screen

	leftArrow->setPosition((Point(visibleSize.width / 10, visibleSize.height / 2)));
	auto leftArrowMenu = Menu::create(leftArrow, NULL);
	leftArrowMenu->setPosition(Vec2::ZERO);
	leftArrowMenu->setTag(40);
	uiLayer->addChild(leftArrowMenu);

	auto rightArrow = MenuItemImage::create("right_arrow.png",
												   "right_arrowClicked.png",
												   CC_CALLBACK_1(CombatScene::toSecondFightMenu, this));    // position the label on the center of the screen

	rightArrow->setPosition((Point(visibleSize.width - (visibleSize.width / 9) , visibleSize.height / 2)));

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

	auto fightButton = MenuItemImage::create("fight.png",
											   "fightClicked.png",
											   CC_CALLBACK_1(CombatScene::updateMessage, this));

	fightButton->setPosition((Point(visibleSize.width / 2.4, visibleSize.height / 6)));
	auto fightButtonMenu = Menu::create(fightButton, NULL);
	fightButtonMenu->setPosition(Vec2::ZERO);
	fightButtonMenu->setTag(44);
	uiLayer->addChild(fightButtonMenu);
}

void CombatScene::toSecondFightMenu(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("toSideMenu.wav");
	uiLayer->removeChildByTag(40,1);
	uiLayer->removeChildByTag(41,1);
	hudLayer->removeChildByTag(42,1);
	hudLayer->removeChildByTag(43,1);
	uiLayer->removeChildByTag(44,1);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto leftArrow = MenuItemImage::create("left_arrow.png",
												   "left_arrowClicked.png",
												   CC_CALLBACK_1(CombatScene::toFirstFightMenu, this));    // position the label on the center of the screen

	leftArrow->setPosition((Point(visibleSize.width / 10, visibleSize.height / 2)));
	auto leftArrowMenu = Menu::create(leftArrow, NULL);
	leftArrowMenu->setPosition(Vec2::ZERO);
	leftArrowMenu->setTag(40);
	uiLayer->addChild(leftArrowMenu);

	auto rightArrow = MenuItemImage::create("right_arrow.png",
												   "right_arrowClicked.png",
												   CC_CALLBACK_1(CombatScene::toThirdFightMenu, this));    // position the label on the center of the screen

	rightArrow->setPosition((Point(visibleSize.width - (visibleSize.width / 9) , visibleSize.height / 2)));

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

	auto fightButton = MenuItemImage::create("fight.png",
											   "fightClicked.png",
											   CC_CALLBACK_1(CombatScene::updateMessage, this));

	fightButton->setPosition((Point(visibleSize.width / 2.4, visibleSize.height / 6)));
	auto fightButtonMenu = Menu::create(fightButton, NULL);
	fightButtonMenu->setPosition(Vec2::ZERO);
	fightButtonMenu->setTag(44);
	uiLayer->addChild(fightButtonMenu);
}

void CombatScene::toThirdFightMenu(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("toSideMenu.wav");
	uiLayer->removeChildByTag(40,1);
	uiLayer->removeChildByTag(41,1);
	hudLayer->removeChildByTag(42,1);
	hudLayer->removeChildByTag(43,1);
	uiLayer->removeChildByTag(44,1);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto leftArrow = MenuItemImage::create("left_arrow.png",
												   "left_arrowClicked.png",
												   CC_CALLBACK_1(CombatScene::toSecondFightMenu, this));    // position the label on the center of the screen

	leftArrow->setPosition((Point(visibleSize.width / 10, visibleSize.height / 2)));
	auto leftArrowMenu = Menu::create(leftArrow, NULL);
	leftArrowMenu->setPosition(Vec2::ZERO);
	leftArrowMenu->setTag(40);
	uiLayer->addChild(leftArrowMenu);

	auto rightArrow = MenuItemImage::create("right_arrow.png",
												   "right_arrowClicked.png",
												   CC_CALLBACK_1(CombatScene::toFirstFightMenu, this));    // position the label on the center of the screen

	rightArrow->setPosition((Point(visibleSize.width - (visibleSize.width / 9) , visibleSize.height / 2)));

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

	auto fightButton = MenuItemImage::create("fight.png",
											   "fightClicked.png",
											   CC_CALLBACK_1(CombatScene::updateMessage, this));

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
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("exitButtonClicked.wav");
	this->removeAllChildren();
}

void CombatScene::updateMessage(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto backDrop = MenuItemImage::create("blockOut_Content5.png",
											   "blockOut_Content5.png",
											   CC_CALLBACK_1(CombatScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(50);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.png");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(51);
	uiLayer->addChild(popup);

	auto label = Label::createWithTTF("Fighting will be added", "fonts/Marker Felt.ttf", 20);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(52);
	uiLayer->addChild(label);

	auto label2 = Label::createWithTTF("in the next update.", "fonts/Marker Felt.ttf", 20);
	label2->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.95)));
	label2->setTag(53);
	uiLayer->addChild(label2);

	auto exitButton = MenuItemImage::create("cancel-button.png",
											   "cancel-buttonClicked.png",
											   CC_CALLBACK_1(CombatScene::exitUpdateMessage, this));

	exitButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.5)));
	auto exitMenu = Menu::create(exitButton, NULL);
	exitMenu->setPosition(Vec2::ZERO);
	exitMenu->setTag(54);
	uiLayer->addChild(exitMenu);

}

void CombatScene::exitUpdateMessage(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	uiLayer->removeChildByTag(50,1);
	uiLayer->removeChildByTag(51,1);
	uiLayer->removeChildByTag(52,1);
	uiLayer->removeChildByTag(53,1);
	uiLayer->removeChildByTag(54,1);
}

