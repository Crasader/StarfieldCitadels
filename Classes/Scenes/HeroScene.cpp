/*
 * HeroScene.cpp
 *
 *  Created on: March 29, 2015
 *      Author: Kristen Ernst
 */

#include "HeroScene.h"

Scene * HeroScene::createScene()
{
    auto scene = HeroScene::create();

    return scene;
}


bool HeroScene::init()
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

    auto backDrop = MenuItemImage::create("recruitBackground.png",
											   "recruitBackground.png",
											   CC_CALLBACK_1(HeroScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(89);
	baseLayer->addChild(backDropLayer);

	auto label = Label::createWithTTF("Recruit Soldiers", "fonts/Marker Felt.ttf", 40);
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
								origin.y + visibleSize.height - (visibleSize.height / 7)));
	hudLayer->addChild(label);

	auto exitButton = MenuItemImage::create("exit_button.png",
											   "exit_buttonClicked.png",
											   CC_CALLBACK_1(HeroScene::loadMainView, this));

	exitButton->setPosition((Point(visibleSize.width - (visibleSize.width / 10), visibleSize.height - (visibleSize.height/10))));
	auto exitMenu = Menu::create(exitButton, NULL);
	exitMenu->setPosition(Vec2::ZERO);
	uiLayer->addChild(exitMenu);

	auto leftArrow = Sprite::create("left_arrow.png");
	leftArrow->setPosition((Point(visibleSize.width / 10, visibleSize.height / 2)));
	leftArrow->setTag(10);
	uiLayer->addChild(leftArrow);
	auto rightArrow = MenuItemImage::create("right_arrow.png",
													   "right_arrowClicked.png",
													   CC_CALLBACK_1(HeroScene::secondBatchOfSoldiers, this));    // position the label on the center of the screen

	rightArrow->setPosition((Point(visibleSize.width - (visibleSize.width / 10) , visibleSize.height / 2)));

	auto rightArrowMenu = Menu::create(rightArrow, NULL);
	rightArrowMenu->setPosition(Vec2::ZERO);
	rightArrowMenu->setTag(20);
	uiLayer->addChild(rightArrowMenu);

	if (boughtWarrior == false)
	{
		auto firstSoldier = MenuItemImage::create("first_soldier.png",
												   "first_soldier.png",
												   CC_CALLBACK_1(HeroScene::buyFirstSoldier, this));    // position the label on the center of the screen

		firstSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));

		auto firstMenu = Menu::create(firstSoldier, NULL);
		firstMenu->setPosition(Vec2::ZERO);
		firstMenu->setTag(1);

		uiLayer->addChild(firstMenu);
	}
	else
	{
		auto purchasedFirstSoldier = Sprite::create("firstSoldierBought.png");
		purchasedFirstSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));
		purchasedFirstSoldier->setTag(1);
		hudLayer->addChild(purchasedFirstSoldier);
	}

	if (boughtSpaceRanger == false)
	{
		auto secondSoldier = MenuItemImage::create("second_soldier.png",
												   "second_soldier.png",
												   CC_CALLBACK_1(HeroScene::buySecondSoldier, this));    // position the label on the center of the screen

		secondSoldier->setPosition((Point(visibleSize.width / 1.98 , visibleSize.height / 2)));

		auto secondMenu = Menu::create(secondSoldier, NULL);
		secondMenu->setPosition(Vec2::ZERO);
		secondMenu->setTag(2);
		uiLayer->addChild(secondMenu);
	}
	else
	{
		auto purchasedSecondSoldier = Sprite::create("secondSoldierBought.png");
		purchasedSecondSoldier->setPosition((Point(visibleSize.width / 1.98 , visibleSize.height / 2)));
		purchasedSecondSoldier->setTag(2);
		hudLayer->addChild(purchasedSecondSoldier);
	}

	if (boughtScout == false)
	{
		auto thirdSoldier = MenuItemImage::create("third_soldier.png",
													   "third_soldier.png",
													   CC_CALLBACK_1(HeroScene::buyThirdSoldier, this));    // position the label on the center of the screen

		thirdSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 1.95)));

		auto thirdMenu = Menu::create(thirdSoldier, NULL);
		thirdMenu->setPosition(Vec2::ZERO);
		thirdMenu->setTag(3);
		uiLayer->addChild(thirdMenu);
	}
	else
	{
		auto purchasedThirdSoldier = Sprite::create("thirdSoldierBought.png");
		purchasedThirdSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 1.95)));
		purchasedThirdSoldier->setTag(3);
		hudLayer->addChild(purchasedThirdSoldier);
	}

	auto firstName = Sprite::create("warriorPlate.png");
	firstName->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38) , visibleSize.height / 7)));
	firstName->setTag(71);
	hudLayer->addChild(firstName);

	auto secondName = Sprite::create("spaceRangerPlate.png");
	secondName->setPosition((Point(visibleSize.width / 1.98 , visibleSize.height / 7)));
	secondName->setTag(72);
	hudLayer->addChild(secondName);

	auto thirdName = Sprite::create("scoutPlate.png");
	thirdName->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 7)));
	thirdName->setTag(73);
	hudLayer->addChild(thirdName);

	this->addChild(baseLayer, 0);
	this->addChild(animationLayer, 1);
	this->addChild(hudLayer, 2);
	this->addChild(uiLayer, 3);

	return true;
}

void HeroScene::setMoneyTotal(int money)
{
	moneyTotal = money;
}

void HeroScene::setBoughtHeroOne(bool hero)
{
	boughtWarrior = hero;
}

void HeroScene::setBoughtHeroTwo(bool hero)
{
	boughtSpaceRanger = hero;
}

void HeroScene::setBoughtHeroThree(bool hero)
{
	boughtScout = hero;
}

void HeroScene::setBoughtHeroFour(bool hero)
{
	boughtCleric = hero;
}

void HeroScene::setBoughtHeroFive(bool hero)
{
	boughtAssassin = hero;
}

void HeroScene::setBoughtHeroSix(bool hero)
{
	boughtMage = hero;
}

void HeroScene::setMainScene(MainScene* scene)
{
	mainScene = scene;
}

void HeroScene::setUpPreviousBoughtItems()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(1,1);
	uiLayer->removeChildByTag(2,1);
	uiLayer->removeChildByTag(3,1);
	hudLayer->removeChildByTag(1,1);
	hudLayer->removeChildByTag(2,1);
	hudLayer->removeChildByTag(3,1);

	if (boughtWarrior == false)
	{
		auto firstSoldier = MenuItemImage::create("first_soldier.png",
												   "first_soldier.png",
												   CC_CALLBACK_1(HeroScene::buyFirstSoldier, this));    // position the label on the center of the screen

		firstSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));

		auto firstMenu = Menu::create(firstSoldier, NULL);
		firstMenu->setPosition(Vec2::ZERO);
		firstMenu->setTag(1);

		uiLayer->addChild(firstMenu);
	}
	else
	{
		auto purchasedFirstSoldier = Sprite::create("firstSoldierBought.png");
		purchasedFirstSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));
		purchasedFirstSoldier->setTag(1);
		hudLayer->addChild(purchasedFirstSoldier);
	}

	if (boughtSpaceRanger == false)
	{
		auto secondSoldier = MenuItemImage::create("second_soldier.png",
												   "second_soldier.png",
												   CC_CALLBACK_1(HeroScene::buySecondSoldier, this));    // position the label on the center of the screen

		secondSoldier->setPosition((Point(visibleSize.width / 1.98, visibleSize.height / 2)));

		auto secondMenu = Menu::create(secondSoldier, NULL);
		secondMenu->setPosition(Vec2::ZERO);
		secondMenu->setTag(2);
		uiLayer->addChild(secondMenu);
	}
	else
	{
		auto purchasedSecondSoldier = Sprite::create("secondSoldierBought.png");
		purchasedSecondSoldier->setPosition((Point(visibleSize.width / 1.98, visibleSize.height / 2)));
		purchasedSecondSoldier->setTag(2);
		hudLayer->addChild(purchasedSecondSoldier);
	}

	if (boughtScout == false)
	{
		auto thirdSoldier = MenuItemImage::create("third_soldier.png",
													   "third_soldier.png",
													   CC_CALLBACK_1(HeroScene::buyThirdSoldier, this));    // position the label on the center of the screen

		thirdSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 1.95)));

		auto thirdMenu = Menu::create(thirdSoldier, NULL);
		thirdMenu->setPosition(Vec2::ZERO);
		thirdMenu->setTag(3);
		uiLayer->addChild(thirdMenu);
	}
	else
	{
		auto purchasedThirdSoldier = Sprite::create("thirdSoldierBought.png");
		purchasedThirdSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 1.95)));
		purchasedThirdSoldier->setTag(3);
		hudLayer->addChild(purchasedThirdSoldier);
	}
}

void HeroScene::doNothing(Ref* pSender)
{
}

void HeroScene::loadMainView(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("exitButtonClicked.wav");
	mainScene->setMoneyTotal(moneyTotal);
	mainScene->repostMoneyTotal();
	this->removeAllChildren();
}

void HeroScene::cancelFromPurchase(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	uiLayer->removeChildByTag(36,1);
	uiLayer->removeChildByTag(37,1);
	uiLayer->removeChildByTag(38,1);
	uiLayer->removeChildByTag(39,1);
}

void HeroScene::buyFirstSoldier(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(HeroScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(29);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.png");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(30);
	uiLayer->addChild(popup);

	auto exitButton = MenuItemImage::create("cancel-button.png",
											   "cancel-buttonClicked.png",
											   CC_CALLBACK_1(HeroScene::exitPopup, this));

	exitButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto exitMenu = Menu::create(exitButton, NULL);
	exitMenu->setPosition(Vec2::ZERO);
	exitMenu->setTag(31);
	uiLayer->addChild(exitMenu);
	auto buyButton = MenuItemImage::create("hire_button.png",
											   "hire_buttonClicked.png",
											   CC_CALLBACK_1(HeroScene::exitFirstPurchase, this));

	buyButton->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto buyButtonMenu = Menu::create(buyButton, NULL);
	buyButtonMenu->setPosition(Vec2::ZERO);
	buyButtonMenu->setTag(32);
	uiLayer->addChild(buyButtonMenu);

	auto label = Label::createWithTTF("Recruit a warrior?", "fonts/Marker Felt.ttf", 20);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(33);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.png");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int heroOneCost = 2000;
	sprintf(money,"%d", heroOneCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void HeroScene::buySecondSoldier(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(HeroScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(29);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.png");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(30);
	uiLayer->addChild(popup);

	auto exitButton = MenuItemImage::create("cancel-button.png",
											   "cancel-buttonClicked.png",
											   CC_CALLBACK_1(HeroScene::exitPopup, this));

	exitButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto exitMenu = Menu::create(exitButton, NULL);
	exitMenu->setPosition(Vec2::ZERO);
	exitMenu->setTag(31);
	uiLayer->addChild(exitMenu);
	auto buyButton = MenuItemImage::create("hire_button.png",
											   "hire_buttonClicked.png",
											   CC_CALLBACK_1(HeroScene::exitSecondPurchase, this));

	buyButton->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto buyButtonMenu = Menu::create(buyButton, NULL);
	buyButtonMenu->setPosition(Vec2::ZERO);
	buyButtonMenu->setTag(32);
	uiLayer->addChild(buyButtonMenu);

	auto label = Label::createWithTTF("Recruit a space ranger?", "fonts/Marker Felt.ttf", 20);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(33);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.png");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int heroOneCost = 4000;
	sprintf(money,"%d", heroOneCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void HeroScene::buyThirdSoldier(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(HeroScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(29);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.png");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(30);
	uiLayer->addChild(popup);

	auto exitButton = MenuItemImage::create("cancel-button.png",
											   "cancel-buttonClicked.png",
											   CC_CALLBACK_1(HeroScene::exitPopup, this));

	exitButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto exitMenu = Menu::create(exitButton, NULL);
	exitMenu->setPosition(Vec2::ZERO);
	exitMenu->setTag(31);
	uiLayer->addChild(exitMenu);
	auto buyButton = MenuItemImage::create("hire_button.png",
											   "hire_buttonClicked.png",
											   CC_CALLBACK_1(HeroScene::exitThirdPurchase, this));

	buyButton->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto buyButtonMenu = Menu::create(buyButton, NULL);
	buyButtonMenu->setPosition(Vec2::ZERO);
	buyButtonMenu->setTag(32);
	uiLayer->addChild(buyButtonMenu);

	auto label = Label::createWithTTF("Recruit a scout?", "fonts/Marker Felt.ttf", 20);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(33);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.png");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int heroOneCost = 2500;
	sprintf(money,"%d", heroOneCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void HeroScene::buyFourthSoldier(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(HeroScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(29);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.png");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(30);
	uiLayer->addChild(popup);

	auto exitButton = MenuItemImage::create("cancel-button.png",
											   "cancel-buttonClicked.png",
											   CC_CALLBACK_1(HeroScene::exitPopup, this));

	exitButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto exitMenu = Menu::create(exitButton, NULL);
	exitMenu->setPosition(Vec2::ZERO);
	exitMenu->setTag(31);
	uiLayer->addChild(exitMenu);
	auto buyButton = MenuItemImage::create("hire_button.png",
											   "hire_buttonClicked.png",
											   CC_CALLBACK_1(HeroScene::exitFourthPurchase, this));

	buyButton->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto buyButtonMenu = Menu::create(buyButton, NULL);
	buyButtonMenu->setPosition(Vec2::ZERO);
	buyButtonMenu->setTag(32);
	uiLayer->addChild(buyButtonMenu);

	auto label = Label::createWithTTF("Recruit a cleric?", "fonts/Marker Felt.ttf", 20);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(33);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.png");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int heroOneCost = 3100;
	sprintf(money,"%d", heroOneCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void HeroScene::buyFifthSoldier(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(HeroScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(29);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.png");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(30);
	uiLayer->addChild(popup);

	auto exitButton = MenuItemImage::create("cancel-button.png",
											   "cancel-buttonClicked.png",
											   CC_CALLBACK_1(HeroScene::exitPopup, this));

	exitButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto exitMenu = Menu::create(exitButton, NULL);
	exitMenu->setPosition(Vec2::ZERO);
	exitMenu->setTag(31);
	uiLayer->addChild(exitMenu);
	auto buyButton = MenuItemImage::create("hire_button.png",
											   "hire_buttonClicked.png",
											   CC_CALLBACK_1(HeroScene::exitFifthPurchase, this));

	buyButton->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto buyButtonMenu = Menu::create(buyButton, NULL);
	buyButtonMenu->setPosition(Vec2::ZERO);
	buyButtonMenu->setTag(32);
	uiLayer->addChild(buyButtonMenu);

	auto label = Label::createWithTTF("Recruit an assassin?", "fonts/Marker Felt.ttf", 20);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(33);
	uiLayer->addChild(label);

	auto moneyHolder = Sprite::create("costObject.png");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int heroOneCost = 6700;
	sprintf(money,"%d", heroOneCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void HeroScene::buySixthSoldier(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(HeroScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(29);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.png");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(30);
	uiLayer->addChild(popup);

	auto exitButton = MenuItemImage::create("cancel-button.png",
											   "cancel-buttonClicked.png",
											   CC_CALLBACK_1(HeroScene::exitPopup, this));

	exitButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.4)));
	auto exitMenu = Menu::create(exitButton, NULL);
	exitMenu->setPosition(Vec2::ZERO);
	exitMenu->setTag(31);
	uiLayer->addChild(exitMenu);
	auto buyButton = MenuItemImage::create("hire_button.png",
											   "hire_buttonClicked.png",
											   CC_CALLBACK_1(HeroScene::exitSixthPurchase, this));

	buyButton->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.4)));
	auto buyButtonMenu = Menu::create(buyButton, NULL);
	buyButtonMenu->setPosition(Vec2::ZERO);
	buyButtonMenu->setTag(32);
	uiLayer->addChild(buyButtonMenu);

	auto label = Label::createWithTTF("Recruit a mage?", "fonts/Marker Felt.ttf", 20);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(33);
	uiLayer->addChild(label);
	auto moneyHolder = Sprite::create("costObject.png");
	moneyHolder->setPosition((Point(visibleSize.width / 2.3 , visibleSize.height / 1.95)));
	moneyHolder->setTag(34);
	uiLayer->addChild(moneyHolder);

	char money[20];
	int heroOneCost = 1800;
	sprintf(money,"%d", heroOneCost);

	auto moneyLabel = Label::createWithTTF(money, "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition((Point(visibleSize.width / 1.9, visibleSize.height / 1.95)));
	moneyLabel->setTag(35);
	uiLayer->addChild(moneyLabel);
}

void HeroScene::exitPopup(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	uiLayer->removeChildByTag(29,1);
	uiLayer->removeChildByTag(30,1);
	uiLayer->removeChildByTag(31,1);
	uiLayer->removeChildByTag(32,1);
	uiLayer->removeChildByTag(33,1);
	uiLayer->removeChildByTag(34,1);
	uiLayer->removeChildByTag(35,1);
}

void HeroScene::exitFirstPurchase(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (moneyTotal >= 2000)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("heroBought.wav");
		moneyTotal = moneyTotal - 2000;

		uiLayer->removeChildByTag(29,1);
		uiLayer->removeChildByTag(30,1);
		uiLayer->removeChildByTag(31,1);
		uiLayer->removeChildByTag(32,1);
		uiLayer->removeChildByTag(33,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		boughtWarrior = true;
		mainScene->setBoughtHeroOne(boughtWarrior);

		uiLayer->removeChildByTag(1, 1);
		auto purchasedFirstSoldier = Sprite::create("firstSoldierBought.png");
		purchasedFirstSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));
		purchasedFirstSoldier->setTag(1);
		hudLayer->addChild(purchasedFirstSoldier);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("exitButtonClicked.wav");
		auto backDrop = MenuItemImage::create("blockOut_Content6.png",
												   "blockOut_Content6.png",
												   CC_CALLBACK_1(HeroScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(36);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.png");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(37);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("Not enough money.", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		label->setTag(38);
		uiLayer->addChild(label);

		auto okButton = MenuItemImage::create("cancel-button.png",
												   "cancel-buttonClicked.png",
												   CC_CALLBACK_1(HeroScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void HeroScene::exitSecondPurchase(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (moneyTotal >= 4000)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("heroBought.wav");
		moneyTotal = moneyTotal - 4000;
		uiLayer->removeChildByTag(29,1);
		uiLayer->removeChildByTag(30,1);
		uiLayer->removeChildByTag(31,1);
		uiLayer->removeChildByTag(32,1);
		uiLayer->removeChildByTag(33,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		boughtSpaceRanger = true;
		mainScene->setBoughtHeroTwo(boughtSpaceRanger);

		uiLayer->removeChildByTag(2, 1);
		auto purchasedSecondSoldier = Sprite::create("secondSoldierBought.png");
		purchasedSecondSoldier->setPosition((Point(visibleSize.width / 1.98, visibleSize.height / 2)));
		purchasedSecondSoldier->setTag(2);
		hudLayer->addChild(purchasedSecondSoldier);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("exitButtonClicked.wav");
		auto backDrop = MenuItemImage::create("blockOut_Content6.png",
												   "blockOut_Content6.png",
												   CC_CALLBACK_1(HeroScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(36);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.png");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(37);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("Not enough money.", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		label->setTag(38);
		uiLayer->addChild(label);

		auto okButton = MenuItemImage::create("cancel-button.png",
												   "cancel-buttonClicked.png",
												   CC_CALLBACK_1(HeroScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void HeroScene::exitThirdPurchase(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (moneyTotal >= 2500)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("heroBought.wav");
		moneyTotal = moneyTotal - 2500;
		uiLayer->removeChildByTag(29,1);
		uiLayer->removeChildByTag(30,1);
		uiLayer->removeChildByTag(31,1);
		uiLayer->removeChildByTag(32,1);
		uiLayer->removeChildByTag(33,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		boughtScout = true;
		mainScene->setBoughtHeroThree(boughtScout);

		uiLayer->removeChildByTag(3, 1);
		auto purchasedThirdSoldier = Sprite::create("thirdSoldierBought.png");
		purchasedThirdSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8), visibleSize.height / 1.95)));
		purchasedThirdSoldier->setTag(3);
		hudLayer->addChild(purchasedThirdSoldier);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("exitButtonClicked.wav");
		auto backDrop = MenuItemImage::create("blockOut_Content6.png",
												   "blockOut_Content6.png",
												   CC_CALLBACK_1(HeroScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(36);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.png");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(37);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("Not enough money.", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		label->setTag(38);
		uiLayer->addChild(label);

		auto okButton = MenuItemImage::create("cancel-button.png",
												   "cancel-buttonClicked.png",
												   CC_CALLBACK_1(HeroScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void HeroScene::exitFourthPurchase(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (moneyTotal >= 3100)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("heroBought.wav");
		moneyTotal = moneyTotal - 3100;
		uiLayer->removeChildByTag(29,1);
		uiLayer->removeChildByTag(30,1);
		uiLayer->removeChildByTag(31,1);
		uiLayer->removeChildByTag(32,1);
		uiLayer->removeChildByTag(33,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		boughtCleric = true;
		mainScene->setBoughtHeroFour(boughtCleric);

		uiLayer->removeChildByTag(4, 1);
		auto purchasedFourthSoldier = Sprite::create("fourthSoldierBought.png");
		purchasedFourthSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));
		purchasedFourthSoldier->setTag(4);
		hudLayer->addChild(purchasedFourthSoldier);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("exitButtonClicked.wav");
		auto backDrop = MenuItemImage::create("blockOut_Content6.png",
												   "blockOut_Content6.png",
												   CC_CALLBACK_1(HeroScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(36);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.png");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(37);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("Not enough money.", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		label->setTag(38);
		uiLayer->addChild(label);

		auto okButton = MenuItemImage::create("cancel-button.png",
												   "cancel-buttonClicked.png",
												   CC_CALLBACK_1(HeroScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void HeroScene::exitFifthPurchase(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (moneyTotal >= 6700)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("heroBought.wav");
		moneyTotal = moneyTotal - 6700;
		uiLayer->removeChildByTag(29,1);
		uiLayer->removeChildByTag(30,1);
		uiLayer->removeChildByTag(31,1);
		uiLayer->removeChildByTag(32,1);
		uiLayer->removeChildByTag(33,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		boughtAssassin = true;
		mainScene->setBoughtHeroFive(boughtAssassin);

		uiLayer->removeChildByTag(5, 1);
		auto purchasedFifthSoldier = Sprite::create("fifthSoldierBought.png");
		purchasedFifthSoldier->setPosition((Point(visibleSize.width / 1.98, visibleSize.height / 2)));
		purchasedFifthSoldier->setTag(5);
		hudLayer->addChild(purchasedFifthSoldier);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("exitButtonClicked.wav");
		auto backDrop = MenuItemImage::create("blockOut_Content6.png",
												   "blockOut_Content6.png",
												   CC_CALLBACK_1(HeroScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(36);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.png");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(37);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("Not enough money.", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		label->setTag(38);
		uiLayer->addChild(label);

		auto okButton = MenuItemImage::create("cancel-button.png",
												   "cancel-buttonClicked.png",
												   CC_CALLBACK_1(HeroScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void HeroScene::exitSixthPurchase(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (moneyTotal >= 1800)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("heroBought.wav");
		moneyTotal = moneyTotal - 1800;
		uiLayer->removeChildByTag(29,1);
		uiLayer->removeChildByTag(30,1);
		uiLayer->removeChildByTag(31,1);
		uiLayer->removeChildByTag(32,1);
		uiLayer->removeChildByTag(33,1);
		uiLayer->removeChildByTag(34,1);
		uiLayer->removeChildByTag(35,1);

		boughtMage = true;
		mainScene->setBoughtHeroSix(boughtMage);

		uiLayer->removeChildByTag(6, 1);
		auto purchasedSixthSoldier = Sprite::create("sixthSoldierBought.png");
		purchasedSixthSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8), visibleSize.height / 2)));
		purchasedSixthSoldier->setTag(6);
		hudLayer->addChild(purchasedSixthSoldier);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("exitButtonClicked.wav");
		auto backDrop = MenuItemImage::create("blockOut_Content6.png",
												   "blockOut_Content6.png",
												   CC_CALLBACK_1(HeroScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(36);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.png");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(37);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("Not enough money.", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.8)));
		label->setTag(38);
		uiLayer->addChild(label);

		auto okButton = MenuItemImage::create("cancel-button.png",
												   "cancel-buttonClicked.png",
												   CC_CALLBACK_1(HeroScene::cancelFromPurchase, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.3)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
}

void HeroScene::firstBatchOfSoldiers(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("toSideMenu.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(4,1);
	uiLayer->removeChildByTag(5,1);
	uiLayer->removeChildByTag(6,1);
	hudLayer->removeChildByTag(4,1);
	hudLayer->removeChildByTag(5,1);
	hudLayer->removeChildByTag(6,1);
	uiLayer->removeChildByTag(10,1);
	uiLayer->removeChildByTag(20,1);
	hudLayer->removeChildByTag(71,1);
	hudLayer->removeChildByTag(72,1);
	hudLayer->removeChildByTag(73,1);

	auto leftArrow = Sprite::create("left_arrow.png");
	leftArrow->setPosition((Point(visibleSize.width / 10, visibleSize.height / 2)));
	leftArrow->setTag(10);
	uiLayer->addChild(leftArrow);

	auto rightArrow = MenuItemImage::create("right_arrow.png",
													   "right_arrowClicked.png",
													   CC_CALLBACK_1(HeroScene::secondBatchOfSoldiers, this));    // position the label on the center of the screen

	rightArrow->setPosition((Point(visibleSize.width - (visibleSize.width / 10) , visibleSize.height / 2)));

	auto rightArrowMenu = Menu::create(rightArrow, NULL);
	rightArrowMenu->setPosition(Vec2::ZERO);
	rightArrowMenu->setTag(20);
	uiLayer->addChild(rightArrowMenu);


	auto firstName = Sprite::create("warriorPlate.png");
	firstName->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38) , visibleSize.height / 7)));
	firstName->setTag(71);
	hudLayer->addChild(firstName);

	auto secondName = Sprite::create("spaceRangerPlate.png");
	secondName->setPosition((Point(visibleSize.width / 1.98 , visibleSize.height / 7)));
	secondName->setTag(72);
	hudLayer->addChild(secondName);

	auto thirdName = Sprite::create("scoutPlate.png");
	thirdName->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 7)));
	thirdName->setTag(73);
	hudLayer->addChild(thirdName);

	if (boughtWarrior == false)
	{
		auto firstSoldier = MenuItemImage::create("first_soldier.png",
												   "first_soldier.png",
												   CC_CALLBACK_1(HeroScene::buyFirstSoldier, this));    // position the label on the center of the screen

		firstSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));

		auto firstMenu = Menu::create(firstSoldier, NULL);
		firstMenu->setPosition(Vec2::ZERO);
		firstMenu->setTag(1);

		uiLayer->addChild(firstMenu);
	}
	else
	{
		auto purchasedFirstSoldier = Sprite::create("firstSoldierBought.png");
		purchasedFirstSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));
		purchasedFirstSoldier->setTag(1);
		hudLayer->addChild(purchasedFirstSoldier);
	}

	if (boughtSpaceRanger == false)
	{
		auto secondSoldier = MenuItemImage::create("second_soldier.png",
												   "second_soldier.png",
												   CC_CALLBACK_1(HeroScene::buySecondSoldier, this));    // position the label on the center of the screen

		secondSoldier->setPosition((Point(visibleSize.width / 1.98 , visibleSize.height / 2)));

		auto secondMenu = Menu::create(secondSoldier, NULL);
		secondMenu->setPosition(Vec2::ZERO);
		secondMenu->setTag(2);
		uiLayer->addChild(secondMenu);
	}
	else
	{
		auto purchasedSecondSoldier = Sprite::create("secondSoldierBought.png");
		purchasedSecondSoldier->setPosition((Point(visibleSize.width / 1.98 , visibleSize.height / 2)));
		purchasedSecondSoldier->setTag(2);
		hudLayer->addChild(purchasedSecondSoldier);
	}

	if (boughtScout == false)
	{
		auto thirdSoldier = MenuItemImage::create("third_soldier.png",
													   "third_soldier.png",
													   CC_CALLBACK_1(HeroScene::buyThirdSoldier, this));    // position the label on the center of the screen

		thirdSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 1.95)));

		auto thirdMenu = Menu::create(thirdSoldier, NULL);
		thirdMenu->setPosition(Vec2::ZERO);
		thirdMenu->setTag(3);
		uiLayer->addChild(thirdMenu);
	}
	else
	{
		auto purchasedThirdSoldier = Sprite::create("thirdSoldierBought.png");
		purchasedThirdSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 1.95)));
		purchasedThirdSoldier->setTag(3);
		hudLayer->addChild(purchasedThirdSoldier);
	}
}
void HeroScene::secondBatchOfSoldiers(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("toSideMenu.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(1,1);
	uiLayer->removeChildByTag(2,1);
	uiLayer->removeChildByTag(3,1);
	hudLayer->removeChildByTag(1,1);
	hudLayer->removeChildByTag(2,1);
	hudLayer->removeChildByTag(3,1);
	uiLayer->removeChildByTag(10,1);
	uiLayer->removeChildByTag(20,1);
	hudLayer->removeChildByTag(71,1);
	hudLayer->removeChildByTag(72,1);
	hudLayer->removeChildByTag(73,1);

	auto leftArrow = MenuItemImage::create("left_arrow.png",
											   "left_arrowClicked.png",
											   CC_CALLBACK_1(HeroScene::firstBatchOfSoldiers, this));    // position the label on the center of the screen

	leftArrow->setPosition((Point(visibleSize.width / 10, visibleSize.height / 2)));

	auto leftArrowMenu = Menu::create(leftArrow, NULL);
	leftArrowMenu->setPosition(Vec2::ZERO);
	leftArrowMenu->setTag(10);
	uiLayer->addChild(leftArrowMenu);
	auto rightArrow = Sprite::create("right_arrow.png");
	rightArrow->setPosition((Point(visibleSize.width - (visibleSize.width / 10) , visibleSize.height / 2)));
	rightArrow->setTag(20);
	uiLayer->addChild(rightArrow);

	auto fourthName = Sprite::create("clericPlate.png");
	fourthName->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38) , visibleSize.height / 7)));
	fourthName->setTag(71);
	hudLayer->addChild(fourthName);

	auto fifthName = Sprite::create("assassinPlate.png");
	fifthName->setPosition((Point(visibleSize.width / 1.98 , visibleSize.height / 7)));
	fifthName->setTag(72);
	hudLayer->addChild(fifthName);

	auto sixthName = Sprite::create("magePlate.png");
	sixthName->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 7)));
	sixthName->setTag(73);
	hudLayer->addChild(sixthName);

	if (boughtCleric == false)
	{
		auto fourthSoldier = MenuItemImage::create("fourth_soldier.png",
												   "fourth_soldier.png",
												   CC_CALLBACK_1(HeroScene::buyFourthSoldier, this));    // position the label on the center of the screen

		fourthSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));

		auto fourthSoldierMenu = Menu::create(fourthSoldier, NULL);
		fourthSoldierMenu->setPosition(Vec2::ZERO);
		fourthSoldierMenu->setTag(4);

		uiLayer->addChild(fourthSoldierMenu);
	}
	else
	{
		auto purchasedFourthSoldier = Sprite::create("fourthSoldierBought.png");
		purchasedFourthSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));
		purchasedFourthSoldier->setTag(4);
		hudLayer->addChild(purchasedFourthSoldier);
	}

	if (boughtAssassin == false)
	{
		auto fifthSoldier = MenuItemImage::create("fifth_soldier.png",
												   "fifth_soldier.png",
												   CC_CALLBACK_1(HeroScene::buyFifthSoldier, this));    // position the label on the center of the screen

		fifthSoldier->setPosition((Point(visibleSize.width / 1.98 , visibleSize.height / 2)));

		auto fifthSoldierMenu = Menu::create(fifthSoldier, NULL);
		fifthSoldierMenu->setPosition(Vec2::ZERO);
		fifthSoldierMenu->setTag(5);
		uiLayer->addChild(fifthSoldierMenu);
	}
	else
	{
		auto purchasedFifthSoldier = Sprite::create("fifthSoldierBought.png");
		purchasedFifthSoldier->setPosition((Point(visibleSize.width / 1.98 , visibleSize.height / 2)));
		purchasedFifthSoldier->setTag(5);
		hudLayer->addChild(purchasedFifthSoldier);
	}

	if (boughtMage == false)
	{
		auto sixthSoldier = MenuItemImage::create("sixth_soldier.png",
													   "sixth_soldier.png",
													   CC_CALLBACK_1(HeroScene::buySixthSoldier, this));    // position the label on the center of the screen

		sixthSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 2)));

		auto sixthSoldierMenu = Menu::create(sixthSoldier, NULL);
		sixthSoldierMenu->setPosition(Vec2::ZERO);
		sixthSoldierMenu->setTag(6);
		uiLayer->addChild(sixthSoldierMenu);
	}
	else
	{
		auto purchasedSixthSoldier = Sprite::create("sixthSoldierBought.png");
		purchasedSixthSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 2)));
		purchasedSixthSoldier->setTag(6);
		hudLayer->addChild(purchasedSixthSoldier);
	}
}

