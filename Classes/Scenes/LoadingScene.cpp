/*
 * LoadingScene.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#include "LoadingScene.h"
#include "MainScene.h"
#include "../Constants.h"

#include "assets-manager/AssetsManagerEx.h"
#include "assets-manager/CCEventAssetsManagerEx.h"
#include "assets-manager/CCEventListenerAssetsManagerEx.h"
using cocos2d::extension::AssetsManagerEx;
using cocos2d::extension::EventListenerAssetsManagerEx;
using cocos2d::extension::EventAssetsManagerEx;

#include "../EventResourceLoader.h"
#include "../EventListenerResourceLoader.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC_EXT;
USING_NS_CC;

LoadingScene::~LoadingScene() {
    // Release the resource loader that was used in this scene
    _resLoader->release();
}

Scene * LoadingScene::createScene()
{
	auto scene = LoadingScene::create();
	return scene;
}

bool LoadingScene::init()
{
	// Call super init first
	if(!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    CCLOG("visibleSize:%.1f,%.1f", visibleSize.width, visibleSize.height);
    CCLOG("origin:%.1f,%.1f", origin.x, origin.y);

	_resLoader = ResourceLoader::create();
	_resLoader->retain();

	_resLoader->startResourceLoad();

	// Generate Scene layers
	auto baseLayer = BaseLayer::create();
	baseLayer->setName("BaseLayer");

	auto animationLayer = AnimationLayer::create();
	animationLayer->setName("AnimationLayer");

	this->addChild(baseLayer, 0);
	this->addChild(animationLayer, 1);
    
    auto background = Sprite::create("titleScreen.png");
    background->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    background->setAnchorPoint(Vec2(0.5, 0.5));
    baseLayer->addChild(background);
    
    auto sp_PreloadProgressBorder = Sprite::create("progressbar_border.png");
    sp_PreloadProgressBorder->setPosition(Vec2(visibleSize.width/2, visibleSize.height/4));
	animationLayer->addChild(sp_PreloadProgressBorder);

	auto pt_PreloadProgress = ProgressTimer::create(Sprite::create("progressbar.png"));
	pt_PreloadProgress->setType(ProgressTimerType::BAR);
	pt_PreloadProgress->setAnchorPoint(Vec2(0,0));
	pt_PreloadProgress->setBarChangeRate(Vec2(1,0));
	pt_PreloadProgress->setMidpoint(Vec2(0,0));
	sp_PreloadProgressBorder->addChild(pt_PreloadProgress, 1);
    
	auto lbl_percent = Label::createWithTTF("0", "fonts/arial.ttf", 15);
    lbl_percent->setPosition(Vec2(4*sp_PreloadProgressBorder->getContentSize().width/5, sp_PreloadProgressBorder->getContentSize().height/4));
	sp_PreloadProgressBorder->addChild(lbl_percent, 2);

	EventListenerResourceLoader *resLoaderListener = EventListenerResourceLoader::create(_resLoader, [pt_PreloadProgress, lbl_percent, this](EventResourceLoader *event) {
		switch(event->getEventCode()) {
		case EventResourceLoader::EventCode::RESOURCE_LOADED:
			{
                CCLOG("Resource loaded: %s", event->getAssetId().c_str());
			}
			break;
		case EventResourceLoader::EventCode::LOAD_PROGRESSION:
			{
                //CCLOG("Percent: %f", event->getPercent());
                char tmp[10];
                sprintf(tmp,"%d%%", (int)event->getPercent());
                lbl_percent->setString(tmp);
				pt_PreloadProgress->setPercentage(event->getPercent());
			}
			break;
		case EventResourceLoader::EventCode::LOAD_FAILED:
			{

			}
			break;
		case EventResourceLoader::EventCode::LOAD_FINISHED:
			{
                auto nextScene = MainScene::create();
                Director::getInstance()->replaceScene(nextScene);
			}
			break;
		default:
			{
				CCLOG("Hit Default.");
			}
			break;
		}
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(resLoaderListener, 1);

	return true;
}

void LoadingScene::checkForAssetUpdates() {
	std::string manifestPath = "Manifests/project.manifest", storagePath = FileUtils::getInstance()->getWritablePath() + "Assets/";
	CCLOG("Storage path for this test : %s", storagePath.c_str());

	AssetsManagerEx * _am = AssetsManagerEx::create(manifestPath, storagePath);

	_am->retain();

	if (!_am->getLocalManifest()->isLoaded())
	{
		CCLOG("Fail to update assets, step skipped.");
	}
	else
	{
		EventListenerAssetsManagerEx * _amListener = EventListenerAssetsManagerEx::create(_am, [this](EventAssetsManagerEx* event){
			switch(event->getEventCode())
			{
				case EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND:
					{
						CCLOG("New version found.");
					}
					break;
				case EventAssetsManagerEx::EventCode::ASSET_UPDATED:
					{
						CCLOG("Asset Updated.");
					}
					break;
				case EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST:
					{
						CCLOG("No local manifest file found, skip assets update.");
					}
					break;
				case EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION:
					{
						std::string assetId = event->getAssetId();
						float percent = event->getPercent();
					}
					break;
				case EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST:
					{
						CCLOG("Error download manifest");
					}
					break;
				case EventAssetsManagerEx::EventCode::ERROR_PARSE_MANIFEST:
					{
						CCLOG("Fail to download manifest file, update skipped.");
					}
					break;
				case EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE:
					{
						CCLOG("Already up to date.");
					}
					break;
				case EventAssetsManagerEx::EventCode::UPDATE_FINISHED:
					{
						CCLOG("Update finished. %s", event->getMessage().c_str());
					}
					break;
				case EventAssetsManagerEx::EventCode::UPDATE_FAILED:
					{
						CCLOG("Update failed. %s", event->getMessage().c_str());
					}
					break;
				case EventAssetsManagerEx::EventCode::ERROR_UPDATING:
					{
						CCLOG("Asset %s : %s", event->getAssetId().c_str(), event->getMessage().c_str());
					}
					break;
				case EventAssetsManagerEx::EventCode::ERROR_DECOMPRESS:
					{
						CCLOG("%s", event->getMessage().c_str());
					}
					break;
				default:
					{
						CCLOG("Hit Default");
					}
					break;
			}
		});
		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_amListener, 1);

		_am->update();
	}
}
