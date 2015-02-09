#include "LoadingScreenScene.h"

#include <assets-manager/AssetsManager.h>

USING_NS_CC;

Scene* LoadingScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = LoadingScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoadingScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(LoadingScreen::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto fuelBarBorder = CCSprite::create("bt_progressbarborder.png");
    fuelBarBorder->setScale(2.0f);
    fuelBarBorder->setPosition(Vec2(origin.x + visibleSize.width/2,
    								origin.y + visibleSize.height/2));
    this->addChild(fuelBarBorder, 2);

    auto fuelBar = CCProgressTimer::create(CCSprite::create("bt_progressbar.png"));
    fuelBar->setScale(2.0f);
    fuelBar->setType(CCProgressTimerType::BAR);
    fuelBar->setAnchorPoint(Vec2(0,0));
    fuelBar->setBarChangeRate(Vec2(1,0));

    fuelBarBorder->addChild(fuelBar, 50);
    fuelBar->setPercentage(100);

    return true;
}

void LoadingScreen::runThisTest()
{
	//AssetsManager _am = AssetsManager::create();
}


void LoadingScreen::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
