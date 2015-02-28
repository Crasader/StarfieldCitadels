/*
 * LoadingScene.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#include "LoadingScene.h"
#include "../Constants.h"
#include "../GameManager.h"

#include "assets-manager/AssetsManagerEx.h"
#include "assets-manager/CCEventAssetsManagerEx.h"
#include "assets-manager/CCEventListenerAssetsManagerEx.h"
using cocos2d::extension::AssetsManagerEx;
using cocos2d::extension::EventListenerAssetsManagerEx;
using cocos2d::extension::EventAssetsManagerEx;

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

	GameManager::Instance()->SetUpScaleFactors();

	CCLOG("visibleSize:%.1f,%.1f", visibleSize.width, visibleSize.height);
	CCLOG("origin:%.1f,%.1f", origin.x, origin.y);

	// Generate Scene layers
	auto baseLayer = BaseLayer::create();
	baseLayer->setName("BaseLayer");

	auto animationLayer = AnimationLayer::create();
	animationLayer->setName("AnimationLayer");

	this->addChild(baseLayer, 0);
	this->addChild(animationLayer, 1);

	sm = world.getSystemManager();
	em = world.getEntityManager();
    
	renderSys = new RenderSystem();
	sm->setSystem(renderSys);
	sm->initializeAll(); // Calls the initialize method in each system

	Entity &background = em->create();
	background.addComponent(new PositionComponent(visibleSize.width/2, visibleSize.height/2));
	background.addComponent(new GraphicsComponent("BG.png", kZindexBG));
	background.addComponent(new RenderComponent(this->getChildByName("BaseLayer")));
	background.addComponent(new AnchorPointComponent(0.5, 0.5));
	background.refresh();
    
    Entity &floor = em->create();
    floor.addComponent(new PositionComponent(visibleSize.width/2, 0.0));
    floor.addComponent(new GraphicsComponent("Floor.png", kZindexFloor));
    floor.addComponent(new RenderComponent(this->getChildByName("BaseLayer")));
    floor.addComponent(new VelocityComponent(2,4));
    floor.addComponent(new AnchorPointComponent(0.5, 0.0));
    floor.refresh();

	/*GETFILENAME(FileName, 32, "BG.png");
	auto bgSprite = Sprite::create(FileName);
	SCALENODE_XY(bgSprite);
	bgSprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	bgSprite->setAnchorPoint(Vec2(0.5,0.5));
	baseLayer->addChild(bgSprite, kZindexBG);*/

	/*GETFILENAME(FileName, 32, "Floor.png");
	auto floorSprite = Sprite::create(FileName);
	SCALENODE_XY(floorSprite);
	floorSprite->setPosition(Vec2(visibleSize.width/2, 0.0));
	floorSprite->setAnchorPoint(Vec2(0.5, 0.0));
	baseLayer->addChild(floorSprite, kZindexFloor);*/
    
	//checkForAssetUpdates();
    this->scheduleUpdate();

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

void LoadingScene::update(float delta) {
	world.loopStart();
	world.setDelta(delta);
    renderSys->process();

	//CCLOG("X: %f", comp->posX);
	//CCLOG("Y: %f", comp->posY);
}
