/*
 * MainScene.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 *
 *  Sound Effects were obtained from soundBible.com, a site
 *  that allows the free use of it's wav files commercially.
 *
 *  Citation for Background Music:
 *  Used the song Parametaphoriquement by gmz. The link to the song is at: http://dig.ccmixter.org/files/gmz/19367
 *  The credit for this song goes to gmz. The only changes we made to the song were that we removed the lyrics
 *  which played for about 30 seconds, cut off the last 2 seconds of the song, made the song fade in at the
 *  beginning, and made it fade out at the end. This song has an Attribution 3.0 license, making it free for
 *  commercial use. This is our disclaimer notice to give credit to where it is due. The song is also DRM free
 *  approved and has no restrictions on the different technology it can be implemented in. We thank the site
 *  and gmz for putting this song up for free use.
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
    
    // The background music, see the citation at the top of this page in the header.
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("spaceMusic.mp3", true);

    moneyTotal = 40000;

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
    baseLayer = BaseLayer::create();
    baseLayer->setName("BaseLayer");
    
    animationLayer = AnimationLayer::create();
    animationLayer->setName("AnimationLayer");
    
    hudLayer = HUDLayer::create();
    hudLayer->setName("HUDLayer");
    
    uiLayer = UILayer::create();
    uiLayer->setName("UILayer");
    

    auto recruitButton = MenuItemImage::create("recruit_button.png",
											   "recruit_buttonClicked.png",
											   CC_CALLBACK_1(MainScene::toRecruitMenu, this));
	recruitButton->setPosition((Point(visibleSize.width - (visibleSize.width / 10), visibleSize.height - (visibleSize.height/10))));
	auto recruitMenu = Menu::create(recruitButton, NULL);
	recruitMenu->setPosition(Vec2::ZERO);
	uiLayer->addChild(recruitMenu);


	auto sprite = Sprite::create("tileMap.png");
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	baseLayer->addChild(sprite);

	auto buildButton = MenuItemImage::create("build_button.png",
										   "build_buttonClicked.png",
										   CC_CALLBACK_1(MainScene::toBuildMenu, this));
	buildButton->setPosition((Point(visibleSize.width - (visibleSize.width / 10), visibleSize.height - (visibleSize.height/3.5))));
	auto buildMenu = Menu::create(buildButton, NULL);
	buildMenu->setPosition(Vec2::ZERO);
	uiLayer->addChild(buildMenu);

	auto upgradeButton = MenuItemImage::create("upgrade_button.png",
											   "upgrade_buttonClicked.png",
											   CC_CALLBACK_1(MainScene::toUpgradeMenu, this));
	upgradeButton->setPosition((Point(visibleSize.width - (visibleSize.width / 10), visibleSize.height/8.5)));
	auto upgradeMenu = Menu::create(upgradeButton, NULL);
	upgradeMenu->setPosition(Vec2::ZERO);
	uiLayer->addChild(upgradeMenu);

	auto fightButton = MenuItemImage::create("fight_button.png",
											   "fight_buttonClicked.png",
											   CC_CALLBACK_1(MainScene::toFightMenu, this));
	fightButton->setPosition((Point(visibleSize.width / 10 , visibleSize.height / 9)));
	auto fightMenu = Menu::create(fightButton, NULL);
	fightMenu->setPosition(Vec2::ZERO);
	uiLayer->addChild(fightMenu);

	auto moneyHolder = Sprite::create("moneyTotal.png");
	moneyHolder->setPosition((Point(visibleSize.width / 6.5 , visibleSize.height - (visibleSize.height/11.5))));
	uiLayer->addChild(moneyHolder);

	char theTesttext[256];
	sprintf(theTesttext,"%d", moneyTotal);

	auto overallMoney = Label::createWithTTF(theTesttext, "fonts/Marker Felt.ttf", 16);
	overallMoney->setPosition((Point(visibleSize.width / 5.5 , visibleSize.height - (visibleSize.height/10))));
	overallMoney->setColor(ccc3(0,0,0));
	overallMoney->setTag(100);
	uiLayer->addChild(overallMoney);

	this->addChild(baseLayer, 0);
	this->addChild(animationLayer, 1);
	this->addChild(hudLayer, 2);
	this->addChild(uiLayer, 3);

	startTheTutorial();
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
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("mainMenusClicked.wav");
	auto buildScene = StoreScene::create();
	buildScene->setMainScene(this);
	buildScene->setUpBuiltItemNums(builtItemNumbers);
	buildScene->setUpBuiltLocations(builtItemLocations);
	buildScene->setUpPreviousBuiltItems();
	buildScene->setMoneyTotal(moneyTotal);
	this->addChild(buildScene, 5);
}

void MainScene::toFightMenu(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("mainMenusClicked.wav");
	auto combatScene = CombatScene::create();
	this->addChild(combatScene, 5);
}
void MainScene::toRecruitMenu(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("mainMenusClicked.wav");
	auto recruitScene = HeroScene::create();
	recruitScene->setMainScene(this);
	recruitScene->setMoneyTotal(moneyTotal);
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
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("mainMenusClicked.wav");
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

	upgradeScene->setMoneyTotal(moneyTotal);
	upgradeScene->loadInitialSoldiers();
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

void MainScene::setMoneyTotal(int money)
{
	moneyTotal = money;
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

void MainScene::doNothing(Ref* pSender)
{
}

void MainScene::moneyTreeClicked(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("money.wav");
	moneyTotal = moneyTotal + 4;
	repostMoneyTotal();
}

void MainScene::exitMoneyStone(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	uiLayer->removeChildByTag(29,1);
	uiLayer->removeChildByTag(30,1);
	uiLayer->removeChildByTag(31,1);
	uiLayer->removeChildByTag(32,1);
	uiLayer->removeChildByTag(33,1);
	uiLayer->removeChildByTag(34,1);

	uiLayer->removeChildByTag(35,1);
	uiLayer->removeChildByTag(36,1);
	uiLayer->removeChildByTag(37,1);
	uiLayer->removeChildByTag(38,1);
	uiLayer->removeChildByTag(39,1);

	repostMoneyTotal();
}

void MainScene::stoneWasTouched(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int randomNum = rand() % 9 + 1;

	if (randomNum == 9)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("lostMoney.wav");
		moneyTotal = moneyTotal - 700;
		if (moneyTotal < 0)
		{
			moneyTotal = 0;
		}

		auto backDrop = MenuItemImage::create("blockOut_Content5.png",
												   "blockOut_Content5.png",
												   CC_CALLBACK_1(MainScene::doNothing, this));

		backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		auto backDropLayer = Menu::create(backDrop, NULL);
		backDropLayer->setPosition(Vec2::ZERO);
		backDropLayer->setTag(35);
		uiLayer->addChild(backDropLayer);

		auto popup = Sprite::create("popup_upgrade_menu.png");
		popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
		popup->setTag(36);
		uiLayer->addChild(popup);

		auto label = Label::createWithTTF("You incurred the wrath", "fonts/Marker Felt.ttf", 15);
		label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
		label->setTag(37);
		uiLayer->addChild(label);

		auto labelTwo = Label::createWithTTF("of the space cats.", "fonts/Marker Felt.ttf", 15);
		labelTwo->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.95)));
		labelTwo->setTag(38);
		uiLayer->addChild(labelTwo);

		auto okButton = MenuItemImage::create("cancel-button.png",
												   "cancel-buttonClicked.png",
												   CC_CALLBACK_1(MainScene::exitMoneyStone, this));

		okButton->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2.4)));
		auto okButtonMenu = Menu::create(okButton, NULL);
		okButtonMenu->setPosition(Vec2::ZERO);
		okButtonMenu->setTag(39);
		uiLayer->addChild(okButtonMenu);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("money.wav");
		moneyTotal = moneyTotal + 100;
		uiLayer->removeChildByTag(29,1);
		uiLayer->removeChildByTag(30,1);
		uiLayer->removeChildByTag(31,1);
		uiLayer->removeChildByTag(32,1);
		uiLayer->removeChildByTag(33,1);
		uiLayer->removeChildByTag(34,1);
		repostMoneyTotal();
	}
}

void MainScene::moneyStoneClicked(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backDrop = MenuItemImage::create("blockOut_Content5.png",
											   "blockOut_Content5.png",
											   CC_CALLBACK_1(MainScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(29);
	uiLayer->addChild(backDropLayer);

	auto popup = Sprite::create("popup_menu.png");
	popup->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	popup->setTag(30);
	uiLayer->addChild(popup);

	auto noButton = MenuItemImage::create("noButton.png",
											   "noButtonClicked.png",
											   CC_CALLBACK_1(MainScene::exitMoneyStone, this));

	noButton->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 2.45)));
	auto noButtonMenu = Menu::create(noButton, NULL);
	noButtonMenu->setPosition(Vec2::ZERO);
	noButtonMenu->setTag(31);
	uiLayer->addChild(noButtonMenu);

	auto yesButton = MenuItemImage::create("yesButton.png",
											   "yesButtonClicked.png",
											   CC_CALLBACK_1(MainScene::stoneWasTouched, this));

	yesButton->setPosition((Point(visibleSize.width / 2.3, visibleSize.height / 2.45)));
	auto yesButtonMenu = Menu::create(yesButton, NULL);
	yesButtonMenu->setPosition(Vec2::ZERO);
	yesButtonMenu->setTag(32);
	uiLayer->addChild(yesButtonMenu);

	auto label = Label::createWithTTF("The stone gives off an ominous", "fonts/Marker Felt.ttf", 17);
	label->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.7)));
	label->setTag(33);
	uiLayer->addChild(label);

	auto labelTwo = Label::createWithTTF("red glow. Touch the stone?", "fonts/Marker Felt.ttf", 17);
	labelTwo->setPosition((Point(visibleSize.width / 2, visibleSize.height / 1.95)));
	labelTwo->setTag(34);
	uiLayer->addChild(labelTwo);
}

void MainScene::repostMoneyTotal()
{
	uiLayer->removeChildByTag(100, 1);
	Size visibleSize = Director::getInstance()->getVisibleSize();

	char theTesttext[256];
	sprintf(theTesttext,"%d", moneyTotal);

	auto overallMoney = Label::createWithTTF(theTesttext, "fonts/Marker Felt.ttf", 16);
	overallMoney->setPosition((Point(visibleSize.width / 5.5 , visibleSize.height - (visibleSize.height/10))));
	overallMoney->setColor(ccc3(0,0,0));
	overallMoney->setTag(100);
	uiLayer->addChild(overallMoney);
}

void MainScene::buildTheItems()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	for(int i = 0; i < builtItemNumbers.size(); i++)
	{
		if(builtItemNumbers.at(i) == 1)
		{
			auto firstItem = Sprite::create("firstItemTile.png");
			firstItem->setPosition(builtItemLocations.at(i));
			hudLayer->addChild(firstItem, 1);
		}
		else if(builtItemNumbers.at(i) == 2)
		{
			auto secondItem = Sprite::create("secondItemTile.png");
			secondItem->setPosition(builtItemLocations.at(i));
			hudLayer->addChild(secondItem, 1);
		}
		else if(builtItemNumbers.at(i) == 3)
		{
			auto thirdItem = Sprite::create("thirdItemTile.png");
			thirdItem->setPosition(builtItemLocations.at(i));
			hudLayer->addChild(thirdItem, 1);
		}
		else if(builtItemNumbers.at(i) == 4)
		{
			auto fourthItem = Sprite::create("fourthItemTile.png");
			fourthItem->setPosition(builtItemLocations.at(i));
			hudLayer->addChild(fourthItem, 1);
		}
		else if(builtItemNumbers.at(i) == 5)
		{
			auto fifthItem = MenuItemImage::create("fifthItemTile.png",
												   "fifthItemTile.png",
												   CC_CALLBACK_1(MainScene::moneyTreeClicked, this));
			fifthItem->setPosition(builtItemLocations.at(i));
			auto fifthItemHolder = Menu::create(fifthItem, NULL);
			fifthItemHolder->setPosition(Vec2::ZERO);
			hudLayer->addChild(fifthItemHolder, 1);
		}
		else if(builtItemNumbers.at(i) == 6)
		{
			auto sixthItem = MenuItemImage::create("sixthItemTile.png",
												   "sixthItemTile.png",
												   CC_CALLBACK_1(MainScene::moneyStoneClicked, this));
			sixthItem->setPosition(builtItemLocations.at(i));
			auto sixthItemHolder = Menu::create(sixthItem, NULL);
			sixthItemHolder->setPosition(Vec2::ZERO);
			hudLayer->addChild(sixthItemHolder, 1);
		}
	}

}

void MainScene::startTheTutorial()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto backDrop = MenuItemImage::create("space.png",
											   "space.png",
											   CC_CALLBACK_1(MainScene::doNothing, this));

	backDrop->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto backDropLayer = Menu::create(backDrop, NULL);
	backDropLayer->setPosition(Vec2::ZERO);
	backDropLayer->setTag(9);
	uiLayer->addChild(backDropLayer);

	auto theTextBox = Sprite::create("textBox.png");
	theTextBox->setPosition((Point(visibleSize.width / 1.72, visibleSize.height / 4.5)));
	theTextBox->setTag(13);
	uiLayer->addChild(theTextBox);

	auto sprite = Sprite::create("tutorialGuide.png");
	sprite->setPosition(Vec2(visibleSize.width / 9, visibleSize.height / 4.5));
	sprite->setTag(10);
	uiLayer->addChild(sprite);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("The days before The Cataclysm were rampant with machinery and technology. There was a", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText2, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);

	auto skip = MenuItemImage::create("skipButton.png",
											   "skipButtonClicked.png",
											   CC_CALLBACK_1(MainScene::exitTutorial, this));

	skip->setPosition((Point(visibleSize.width - (visibleSize.width / 10), visibleSize.height - (visibleSize.height/10))));
	auto skipButton = Menu::create(skip, NULL);
	skipButton->setPosition(Vec2::ZERO);
	skipButton->setTag(14);
	uiLayer->addChild(skipButton, 2);

}

void MainScene::tutorialText2(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("new machine, a new technological thingamajig being developed every day. I think deep", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText3, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText3(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("down we all knew, The Machine Age, that's what they called it, would never last but we", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText4, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText4(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("never thought it would end in our lifetime. We were so wrong...", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText5, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText5(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("No one knows what caused The Cataclysm. Some say it was mankind's desire to change", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText6, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText6(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("everything into machines, something we could control, tame. Creation was not something to", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText7, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText7(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("be tamed or controlled in my opinion. As soon as you control everything, you are now", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText8, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText8(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("responsible to provide power to everything and what happens when you run out?", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText9, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText9(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("One day, everything went dark. The mechanical oceans stopped running, the winds stopped", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText10, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText10(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("blowing. That's when it happened. The Cataclysm. Darkness. Being tossed to and fro.", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText11, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText11(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("Confusion. Was my family alive? Where was I?", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText12, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText12(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("When I finally woke up I was stranded on a small lump of rock in the sky, asteroids I think", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText13, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText13(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("they were called. The first few years were tough. About the only nice thing about the", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText14, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText14(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("mechanization of everything was that I could reprogram and control the rock I landed on. It", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText15, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText15(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("was a lot of trial and error but eventually I was able to begin changing the composition of the", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText16, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText16(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("rock I was on. First there was a little dirt, then there was something green. Like a row of", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText17, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText17(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("dominoes falling down everything began to come together. Before I knew it the asteroid I", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText18, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText18(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("was on had come to life. Green everywhere, it was like life had been born again from the", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText19, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText19(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("ashes of the old world.", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText20, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText20(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("Before long, with the resources that I'd collected I was able to explore further into the", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText21, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText21(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("nearby asteroids branching out. Always hoping to find someone else, anyone else who had", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText22, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText22(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("been able to tame the rock like I had...", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText23, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText23(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("That's when I found you. Today. I had almost given up hope of finding anyone else alive but", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText24, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText24(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("there you were, lying with your back on the rock. You said you had no memory of getting", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText25, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText25(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("there. Neither had I. You had no idea how long you'd been there. Maybe everything didn't", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText26, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText26(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("fail at once, just certain areas... Who knows?", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText27, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText27(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("I told you about what I'd been doing and taught you everything I knew. We are the future.", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText28, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText28(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("We must begin the recolonization of these small islands in the vastness of space and do our", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText29, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText29(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("part in making it all green again. There will be complications of course, always there will be", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText30, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText30(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("people that oppose us, but we will always press forward, taking what we can here and there", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText31, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText31(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("to accomplish our goal of making our asteroids a better place. Some might call it barbaric, the", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText32, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText32(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("stealing of resources and goods from each other, the other survivors, but the world's just not", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText33, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText33(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("what it used to be. Plus, who doesn't like a little plundering and pillaging from time to time.", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText34, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText34(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("Build your citadel, recruit a vast array of soldiers, and upgrade your soldiers and walls to", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText35, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText35(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("protect yourself from others. Remember, your two most important sources of income are", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText36, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText36(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("the star-dust trees and the galactic stones. Click the trees and stones after you've built", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText37, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText37(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("them to earn money. Be careful though, the crimson glow of galactic stones attracts wild", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText38, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText38(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("space cats. They can be vicious little buggers, and tend to steal your money. Now get out", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::tutorialText39, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::tutorialText39(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);

	CCTextAlignment hAlignment = CCTextAlignment::LEFT;
	CCVerticalTextAlignment vAlignment = CCVerticalTextAlignment::TOP;
	CCLabelTTF* text = CCLabelTTF::create("there and start building my friend.", "Helvetica", 20, CCSizeMake(visibleSize.width / 1.4, visibleSize.height / 3), hAlignment, vAlignment);
	text->setPosition((Point(visibleSize.width / 1.7, visibleSize.height / 5)));
	text->setTag(11);
	uiLayer->addChild(text);

	auto clicker = MenuItemImage::create("clearButton.png",
											   "clearButton.png",
											   CC_CALLBACK_1(MainScene::exitTutorial, this));

	clicker->setPosition((Point(visibleSize.width / 2, visibleSize.height / 2)));
	auto clickerLayer = Menu::create(clicker, NULL);
	clickerLayer->setPosition(Vec2::ZERO);
	clickerLayer->setTag(12);
	uiLayer->addChild(clickerLayer);
}

void MainScene::exitTutorial(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normalClick.wav");
	uiLayer->removeChildByTag(9,1);
	uiLayer->removeChildByTag(10,1);
	uiLayer->removeChildByTag(11,1);
	uiLayer->removeChildByTag(12,1);
	uiLayer->removeChildByTag(13,1);
	uiLayer->removeChildByTag(14,1);
}


