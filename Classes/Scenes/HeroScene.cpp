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

    auto backDrop = MenuItemImage::create("space.jpg",
											   "space.jpg",
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
											   "exit_button.png",
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
													   "right_arrow.png",
													   CC_CALLBACK_1(HeroScene::secondBatchOfSoldiers, this));    // position the label on the center of the screen

	rightArrow->setPosition((Point(visibleSize.width - (visibleSize.width / 10) , visibleSize.height / 2)));

	auto rightArrowMenu = Menu::create(rightArrow, NULL);
	rightArrowMenu->setPosition(Vec2::ZERO);
	rightArrowMenu->setTag(20);
	uiLayer->addChild(rightArrowMenu);

	if (boughtWarrior == false)
	{
		auto firstSoldier = MenuItemImage::create("first_soldier.jpg",
												   "first_soldier.jpg",
												   CC_CALLBACK_1(HeroScene::buyFirstSoldier, this));    // position the label on the center of the screen

		firstSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));

		auto firstMenu = Menu::create(firstSoldier, NULL);
		firstMenu->setPosition(Vec2::ZERO);
		firstMenu->setTag(1);

		uiLayer->addChild(firstMenu);
	}
	else
	{
		auto purchasedFirstSoldier = Sprite::create("bought_soldier.jpg");
		purchasedFirstSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));
		purchasedFirstSoldier->setTag(1);
		hudLayer->addChild(purchasedFirstSoldier);
	}

	if (boughtSpaceRanger == false)
	{
		auto secondSoldier = MenuItemImage::create("second_soldier.jpg",
												   "second_soldier.jpg",
												   CC_CALLBACK_1(HeroScene::buySecondSoldier, this));    // position the label on the center of the screen

		secondSoldier->setPosition((Point(visibleSize.width / 1.98 , visibleSize.height / 2)));

		auto secondMenu = Menu::create(secondSoldier, NULL);
		secondMenu->setPosition(Vec2::ZERO);
		secondMenu->setTag(2);
		uiLayer->addChild(secondMenu);
	}
	else
	{
		auto purchasedSecondSoldier = Sprite::create("bought_soldier.jpg");
		purchasedSecondSoldier->setPosition((Point(visibleSize.width / 1.98 , visibleSize.height / 2)));
		purchasedSecondSoldier->setTag(2);
		hudLayer->addChild(purchasedSecondSoldier);
	}

	if (boughtScout == false)
	{
		auto thirdSoldier = MenuItemImage::create("third_soldier.jpg",
													   "third_soldier.jpg",
													   CC_CALLBACK_1(HeroScene::buyThirdSoldier, this));    // position the label on the center of the screen

		thirdSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 2)));

		auto thirdMenu = Menu::create(thirdSoldier, NULL);
		thirdMenu->setPosition(Vec2::ZERO);
		thirdMenu->setTag(3);
		uiLayer->addChild(thirdMenu);
	}
	else
	{
		auto purchasedThirdSoldier = Sprite::create("bought_soldier.jpg");
		purchasedThirdSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 2)));
		purchasedThirdSoldier->setTag(3);
		hudLayer->addChild(purchasedThirdSoldier);
	}

	this->addChild(baseLayer, 0);
	this->addChild(animationLayer, 1);
	this->addChild(hudLayer, 2);
	this->addChild(uiLayer, 3);

	return true;
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
		auto firstSoldier = MenuItemImage::create("first_soldier.jpg",
												   "first_soldier.jpg",
												   CC_CALLBACK_1(HeroScene::buyFirstSoldier, this));    // position the label on the center of the screen

		firstSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));

		auto firstMenu = Menu::create(firstSoldier, NULL);
		firstMenu->setPosition(Vec2::ZERO);
		firstMenu->setTag(1);

		uiLayer->addChild(firstMenu);
	}
	else
	{
		auto purchasedFirstSoldier = Sprite::create("bought_soldier.jpg");
		purchasedFirstSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));
		purchasedFirstSoldier->setTag(1);
		hudLayer->addChild(purchasedFirstSoldier);
	}

	if (boughtSpaceRanger == false)
	{
		auto secondSoldier = MenuItemImage::create("second_soldier.jpg",
												   "second_soldier.jpg",
												   CC_CALLBACK_1(HeroScene::buySecondSoldier, this));    // position the label on the center of the screen

		secondSoldier->setPosition((Point(visibleSize.width / 1.98, visibleSize.height / 2)));

		auto secondMenu = Menu::create(secondSoldier, NULL);
		secondMenu->setPosition(Vec2::ZERO);
		secondMenu->setTag(2);
		uiLayer->addChild(secondMenu);
	}
	else
	{
		auto purchasedSecondSoldier = Sprite::create("bought_soldier.jpg");
		purchasedSecondSoldier->setPosition((Point(visibleSize.width / 1.98, visibleSize.height / 2)));
		purchasedSecondSoldier->setTag(2);
		hudLayer->addChild(purchasedSecondSoldier);
	}

	if (boughtScout == false)
	{
		auto thirdSoldier = MenuItemImage::create("third_soldier.jpg",
													   "third_soldier.jpg",
													   CC_CALLBACK_1(HeroScene::buyThirdSoldier, this));    // position the label on the center of the screen

		thirdSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 2)));

		auto thirdMenu = Menu::create(thirdSoldier, NULL);
		thirdMenu->setPosition(Vec2::ZERO);
		thirdMenu->setTag(3);
		uiLayer->addChild(thirdMenu);
	}
	else
	{
		auto purchasedThirdSoldier = Sprite::create("bought_soldier.jpg");
		purchasedThirdSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 2)));
		purchasedThirdSoldier->setTag(3);
		hudLayer->addChild(purchasedThirdSoldier);
	}
}

void HeroScene::doNothing(Ref* pSender)
{
}

void HeroScene::loadMainView(Ref* pSender)
{
	this->removeAllChildren();
}

void HeroScene::buyFirstSoldier(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(HeroScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(29);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(30);
	uiLayer->addChild(popup);

	auto exitButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(HeroScene::exitPopup, this));

	exitButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.3)));
	auto exitMenu = Menu::create(exitButton, NULL);
	exitMenu->setPosition(Vec2::ZERO);
	exitMenu->setTag(31);
	uiLayer->addChild(exitMenu);
	auto buyButton = MenuItemImage::create("hire_button.png",
											   "hire_button.png",
											   CC_CALLBACK_1(HeroScene::exitFirstPurchase, this));

	buyButton->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.3)));
	auto buyButtonMenu = Menu::create(buyButton, NULL);
	buyButtonMenu->setPosition(Vec2::ZERO);
	buyButtonMenu->setTag(32);
	uiLayer->addChild(buyButtonMenu);

	auto label = Label::createWithTTF("Recruit a warrior?", "fonts/Marker Felt.ttf", 20);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(33);
	uiLayer->addChild(label);

}

void HeroScene::buySecondSoldier(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(HeroScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(29);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(30);
	uiLayer->addChild(popup);

	auto exitButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(HeroScene::exitPopup, this));

	exitButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.3)));
	auto exitMenu = Menu::create(exitButton, NULL);
	exitMenu->setPosition(Vec2::ZERO);
	exitMenu->setTag(31);
	uiLayer->addChild(exitMenu);
	auto buyButton = MenuItemImage::create("hire_button.png",
											   "hire_button.png",
											   CC_CALLBACK_1(HeroScene::exitSecondPurchase, this));

	buyButton->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.3)));
	auto buyButtonMenu = Menu::create(buyButton, NULL);
	buyButtonMenu->setPosition(Vec2::ZERO);
	buyButtonMenu->setTag(32);
	uiLayer->addChild(buyButtonMenu);

	auto label = Label::createWithTTF("Recruit a space ranger?", "fonts/Marker Felt.ttf", 20);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(33);
	uiLayer->addChild(label);

}

void HeroScene::buyThirdSoldier(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(HeroScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(29);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(30);
	uiLayer->addChild(popup);

	auto exitButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(HeroScene::exitPopup, this));

	exitButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.3)));
	auto exitMenu = Menu::create(exitButton, NULL);
	exitMenu->setPosition(Vec2::ZERO);
	exitMenu->setTag(31);
	uiLayer->addChild(exitMenu);
	auto buyButton = MenuItemImage::create("hire_button.png",
											   "hire_button.png",
											   CC_CALLBACK_1(HeroScene::exitThirdPurchase, this));

	buyButton->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.3)));
	auto buyButtonMenu = Menu::create(buyButton, NULL);
	buyButtonMenu->setPosition(Vec2::ZERO);
	buyButtonMenu->setTag(32);
	uiLayer->addChild(buyButtonMenu);

	auto label = Label::createWithTTF("Recruit a scout?", "fonts/Marker Felt.ttf", 20);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(33);
	uiLayer->addChild(label);

}

void HeroScene::buyFourthSoldier(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(HeroScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(29);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(30);
	uiLayer->addChild(popup);

	auto exitButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(HeroScene::exitPopup, this));

	exitButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.3)));
	auto exitMenu = Menu::create(exitButton, NULL);
	exitMenu->setPosition(Vec2::ZERO);
	exitMenu->setTag(31);
	uiLayer->addChild(exitMenu);
	auto buyButton = MenuItemImage::create("hire_button.png",
											   "hire_button.png",
											   CC_CALLBACK_1(HeroScene::exitFourthPurchase, this));

	buyButton->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.3)));
	auto buyButtonMenu = Menu::create(buyButton, NULL);
	buyButtonMenu->setPosition(Vec2::ZERO);
	buyButtonMenu->setTag(32);
	uiLayer->addChild(buyButtonMenu);

	auto label = Label::createWithTTF("Recruit a cleric?", "fonts/Marker Felt.ttf", 20);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(33);
	uiLayer->addChild(label);

}

void HeroScene::buyFifthSoldier(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(HeroScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(29);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(30);
	uiLayer->addChild(popup);

	auto exitButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(HeroScene::exitPopup, this));

	exitButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.3)));
	auto exitMenu = Menu::create(exitButton, NULL);
	exitMenu->setPosition(Vec2::ZERO);
	exitMenu->setTag(31);
	uiLayer->addChild(exitMenu);
	auto buyButton = MenuItemImage::create("hire_button.png",
											   "hire_button.png",
											   CC_CALLBACK_1(HeroScene::exitFifthPurchase, this));

	buyButton->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.3)));
	auto buyButtonMenu = Menu::create(buyButton, NULL);
	buyButtonMenu->setPosition(Vec2::ZERO);
	buyButtonMenu->setTag(32);
	uiLayer->addChild(buyButtonMenu);

	auto label = Label::createWithTTF("Recruit an assassin?", "fonts/Marker Felt.ttf", 20);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(33);
	uiLayer->addChild(label);

}

void HeroScene::buySixthSoldier(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content.png",
											   "blockOut_Content.png",
											   CC_CALLBACK_1(HeroScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(29);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.jpg");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(30);
	uiLayer->addChild(popup);

	auto exitButton = MenuItemImage::create("cancel-button.jpg",
											   "cancel-button.jpg",
											   CC_CALLBACK_1(HeroScene::exitPopup, this));

	exitButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.3)));
	auto exitMenu = Menu::create(exitButton, NULL);
	exitMenu->setPosition(Vec2::ZERO);
	exitMenu->setTag(31);
	uiLayer->addChild(exitMenu);
	auto buyButton = MenuItemImage::create("hire_button.png",
											   "hire_button.png",
											   CC_CALLBACK_1(HeroScene::exitSixthPurchase, this));

	buyButton->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.3)));
	auto buyButtonMenu = Menu::create(buyButton, NULL);
	buyButtonMenu->setPosition(Vec2::ZERO);
	buyButtonMenu->setTag(32);
	uiLayer->addChild(buyButtonMenu);

	auto label = Label::createWithTTF("Recruit a mage?", "fonts/Marker Felt.ttf", 20);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(33);
	uiLayer->addChild(label);
}

void HeroScene::exitPopup(Ref* pSender)
{
	uiLayer->removeChildByTag(29,1);
	uiLayer->removeChildByTag(30,1);
	uiLayer->removeChildByTag(31,1);
	uiLayer->removeChildByTag(32,1);
	uiLayer->removeChildByTag(33,1);
}

void HeroScene::exitFirstPurchase(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	uiLayer->removeChildByTag(29,1);
	uiLayer->removeChildByTag(30,1);
	uiLayer->removeChildByTag(31,1);
	uiLayer->removeChildByTag(32,1);
	uiLayer->removeChildByTag(33,1);

	boughtWarrior = true;
	mainScene->setBoughtHeroOne(boughtWarrior);

	uiLayer->removeChildByTag(1, 1);
	auto purchasedFirstSoldier = Sprite::create("bought_soldier.jpg");
	purchasedFirstSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));
	purchasedFirstSoldier->setTag(1);
	hudLayer->addChild(purchasedFirstSoldier);
}

void HeroScene::exitSecondPurchase(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	uiLayer->removeChildByTag(29,1);
	uiLayer->removeChildByTag(30,1);
	uiLayer->removeChildByTag(31,1);
	uiLayer->removeChildByTag(32,1);
	uiLayer->removeChildByTag(33,1);

	boughtSpaceRanger = true;
	mainScene->setBoughtHeroTwo(boughtSpaceRanger);

	uiLayer->removeChildByTag(2, 1);
	auto purchasedSecondSoldier = Sprite::create("bought_soldier.jpg");
	purchasedSecondSoldier->setPosition((Point(visibleSize.width / 1.98, visibleSize.height / 2)));
	purchasedSecondSoldier->setTag(2);
	hudLayer->addChild(purchasedSecondSoldier);
}

void HeroScene::exitThirdPurchase(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	uiLayer->removeChildByTag(29,1);
	uiLayer->removeChildByTag(30,1);
	uiLayer->removeChildByTag(31,1);
	uiLayer->removeChildByTag(32,1);
	uiLayer->removeChildByTag(33,1);

	boughtScout = true;
	mainScene->setBoughtHeroThree(boughtScout);

	uiLayer->removeChildByTag(3, 1);
	auto purchasedThirdSoldier = Sprite::create("bought_soldier.jpg");
	purchasedThirdSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8), visibleSize.height / 2)));
	purchasedThirdSoldier->setTag(3);
	hudLayer->addChild(purchasedThirdSoldier);
}

void HeroScene::exitFourthPurchase(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	uiLayer->removeChildByTag(29,1);
	uiLayer->removeChildByTag(30,1);
	uiLayer->removeChildByTag(31,1);
	uiLayer->removeChildByTag(32,1);
	uiLayer->removeChildByTag(33,1);

	boughtCleric = true;
	mainScene->setBoughtHeroFour(boughtCleric);

	uiLayer->removeChildByTag(4, 1);
	auto purchasedFourthSoldier = Sprite::create("bought_soldier.jpg");
	purchasedFourthSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));
	purchasedFourthSoldier->setTag(4);
	hudLayer->addChild(purchasedFourthSoldier);
}

void HeroScene::exitFifthPurchase(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	uiLayer->removeChildByTag(29,1);
	uiLayer->removeChildByTag(30,1);
	uiLayer->removeChildByTag(31,1);
	uiLayer->removeChildByTag(32,1);
	uiLayer->removeChildByTag(33,1);

	boughtAssassin = true;
	mainScene->setBoughtHeroFive(boughtAssassin);

	uiLayer->removeChildByTag(5, 1);
	auto purchasedFifthSoldier = Sprite::create("bought_soldier.jpg");
	purchasedFifthSoldier->setPosition((Point(visibleSize.width / 1.98, visibleSize.height / 2)));
	purchasedFifthSoldier->setTag(5);
	hudLayer->addChild(purchasedFifthSoldier);
}

void HeroScene::exitSixthPurchase(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	uiLayer->removeChildByTag(29,1);
	uiLayer->removeChildByTag(30,1);
	uiLayer->removeChildByTag(31,1);
	uiLayer->removeChildByTag(32,1);
	uiLayer->removeChildByTag(33,1);

	boughtMage = true;
	mainScene->setBoughtHeroSix(boughtMage);

	uiLayer->removeChildByTag(6, 1);
	auto purchasedSixthSoldier = Sprite::create("bought_soldier.jpg");
	purchasedSixthSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8), visibleSize.height / 2)));
	purchasedSixthSoldier->setTag(6);
	hudLayer->addChild(purchasedSixthSoldier);
}

void HeroScene::firstBatchOfSoldiers(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(4,1);
	uiLayer->removeChildByTag(5,1);
	uiLayer->removeChildByTag(6,1);
	hudLayer->removeChildByTag(4,1);
	hudLayer->removeChildByTag(5,1);
	hudLayer->removeChildByTag(6,1);
	uiLayer->removeChildByTag(10,1);
	uiLayer->removeChildByTag(20,1);

	auto leftArrow = Sprite::create("left_arrow.png");
	leftArrow->setPosition((Point(visibleSize.width / 10, visibleSize.height / 2)));
	leftArrow->setTag(10);
	uiLayer->addChild(leftArrow);

	auto rightArrow = MenuItemImage::create("right_arrow.png",
													   "right_arrow.png",
													   CC_CALLBACK_1(HeroScene::secondBatchOfSoldiers, this));    // position the label on the center of the screen

	rightArrow->setPosition((Point(visibleSize.width - (visibleSize.width / 10) , visibleSize.height / 2)));

	auto rightArrowMenu = Menu::create(rightArrow, NULL);
	rightArrowMenu->setPosition(Vec2::ZERO);
	rightArrowMenu->setTag(20);
	uiLayer->addChild(rightArrowMenu);

	if (boughtWarrior == false)
	{
		auto firstSoldier = MenuItemImage::create("first_soldier.jpg",
												   "first_soldier.jpg",
												   CC_CALLBACK_1(HeroScene::buyFirstSoldier, this));    // position the label on the center of the screen

		firstSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));

		auto firstMenu = Menu::create(firstSoldier, NULL);
		firstMenu->setPosition(Vec2::ZERO);
		firstMenu->setTag(1);

		uiLayer->addChild(firstMenu);
	}
	else
	{
		auto purchasedFirstSoldier = Sprite::create("bought_soldier.jpg");
		purchasedFirstSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));
		purchasedFirstSoldier->setTag(1);
		hudLayer->addChild(purchasedFirstSoldier);
	}

	if (boughtSpaceRanger == false)
	{
		auto secondSoldier = MenuItemImage::create("second_soldier.jpg",
												   "second_soldier.jpg",
												   CC_CALLBACK_1(HeroScene::buySecondSoldier, this));    // position the label on the center of the screen

		secondSoldier->setPosition((Point(visibleSize.width / 1.98 , visibleSize.height / 2)));

		auto secondMenu = Menu::create(secondSoldier, NULL);
		secondMenu->setPosition(Vec2::ZERO);
		secondMenu->setTag(2);
		uiLayer->addChild(secondMenu);
	}
	else
	{
		auto purchasedSecondSoldier = Sprite::create("bought_soldier.jpg");
		purchasedSecondSoldier->setPosition((Point(visibleSize.width / 1.98 , visibleSize.height / 2)));
		purchasedSecondSoldier->setTag(2);
		hudLayer->addChild(purchasedSecondSoldier);
	}

	if (boughtScout == false)
	{
		auto thirdSoldier = MenuItemImage::create("third_soldier.jpg",
													   "third_soldier.jpg",
													   CC_CALLBACK_1(HeroScene::buyThirdSoldier, this));    // position the label on the center of the screen

		thirdSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 2)));

		auto thirdMenu = Menu::create(thirdSoldier, NULL);
		thirdMenu->setPosition(Vec2::ZERO);
		thirdMenu->setTag(3);
		uiLayer->addChild(thirdMenu);
	}
	else
	{
		auto purchasedThirdSoldier = Sprite::create("bought_soldier.jpg");
		purchasedThirdSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 2)));
		purchasedThirdSoldier->setTag(3);
		hudLayer->addChild(purchasedThirdSoldier);
	}
}
void HeroScene::secondBatchOfSoldiers(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(1,1);
	uiLayer->removeChildByTag(2,1);
	uiLayer->removeChildByTag(3,1);
	hudLayer->removeChildByTag(1,1);
	hudLayer->removeChildByTag(2,1);
	hudLayer->removeChildByTag(3,1);
	uiLayer->removeChildByTag(10,1);
	uiLayer->removeChildByTag(20,1);

	auto leftArrow = MenuItemImage::create("left_arrow.png",
											   "left_arrow.png",
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

	if (boughtCleric == false)
	{
		auto fourthSoldier = MenuItemImage::create("fourth_soldier.jpg",
												   "fourth_soldier.jpg",
												   CC_CALLBACK_1(HeroScene::buyFourthSoldier, this));    // position the label on the center of the screen

		fourthSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));

		auto fourthSoldierMenu = Menu::create(fourthSoldier, NULL);
		fourthSoldierMenu->setPosition(Vec2::ZERO);
		fourthSoldierMenu->setTag(4);

		uiLayer->addChild(fourthSoldierMenu);
	}
	else
	{
		auto purchasedFourthSoldier = Sprite::create("bought_soldier.jpg");
		purchasedFourthSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 1.38), visibleSize.height / 2)));
		purchasedFourthSoldier->setTag(4);
		hudLayer->addChild(purchasedFourthSoldier);
	}

	if (boughtAssassin == false)
	{
		auto fifthSoldier = MenuItemImage::create("fifth_soldier.jpg",
												   "fifth_soldier.jpg",
												   CC_CALLBACK_1(HeroScene::buyFifthSoldier, this));    // position the label on the center of the screen

		fifthSoldier->setPosition((Point(visibleSize.width / 1.98 , visibleSize.height / 2)));

		auto fifthSoldierMenu = Menu::create(fifthSoldier, NULL);
		fifthSoldierMenu->setPosition(Vec2::ZERO);
		fifthSoldierMenu->setTag(5);
		uiLayer->addChild(fifthSoldierMenu);
	}
	else
	{
		auto purchasedFifthSoldier = Sprite::create("bought_soldier.jpg");
		purchasedFifthSoldier->setPosition((Point(visibleSize.width / 1.98 , visibleSize.height / 2)));
		purchasedFifthSoldier->setTag(5);
		hudLayer->addChild(purchasedFifthSoldier);
	}

	if (boughtMage == false)
	{
		auto sixthSoldier = MenuItemImage::create("sixth_soldier.jpg",
													   "sixth_soldier.jpg",
													   CC_CALLBACK_1(HeroScene::buySixthSoldier, this));    // position the label on the center of the screen

		sixthSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 2)));

		auto sixthSoldierMenu = Menu::create(sixthSoldier, NULL);
		sixthSoldierMenu->setPosition(Vec2::ZERO);
		sixthSoldierMenu->setTag(6);
		uiLayer->addChild(sixthSoldierMenu);
	}
	else
	{
		auto purchasedSixthSoldier = Sprite::create("bought_soldier.jpg");
		purchasedSixthSoldier->setPosition((Point(visibleSize.width - (visibleSize.width / 3.8) , visibleSize.height / 2)));
		purchasedSixthSoldier->setTag(6);
		hudLayer->addChild(purchasedSixthSoldier);
	}
}

