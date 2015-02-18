/*
 * LoadingScene.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#include "LoadingScene.h"

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
    
	/*FileUtils::getInstance()->addSearchPath("./");
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename("manifest.json");
	CCLOG("Test: %s",fullPath.c_str());*/

	std::string manifestPath = "Manifests/project.manifest", storagePath = FileUtils::getInstance()->getWritablePath() + "AssetStorage/";
    CCLOG("Storage path for this test : %s", storagePath.c_str());
    
	AssetsManagerEx * _am = AssetsManagerEx::create(manifestPath, storagePath);

	_am->retain();
	if(_am != nullptr)
		CCLOG("Is not null.");

	if (!_am->getLocalManifest()->isLoaded())
	{
		CCLOG("Fail to update assets, step skipped.");
	}
	else
	{
		CCLOG("Made it 1");
		EventListenerAssetsManagerEx * _amListener = EventListenerAssetsManagerEx::create(_am, [this](EventAssetsManagerEx* event){
			CCLOG("Made it 2");
			switch(event->getEventCode())
			{
				case EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST:
					{
						CCLOG("No local manifest file found, skip assets update.");
					}
					break;
				case EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION:
					{
						std::string assetId = event->getAssetId();
						float percent = event->getPercent();

						if(assetId == AssetsManagerEx::VERSION_ID)
						{

						}
						else if(assetId == AssetsManagerEx::MANIFEST_ID)
						{

						}
						else
						{

						}
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
	}

    //this->scheduleUpdate();

	return true;
}

void LoadingScene::update(float delta) {
	world.loopStart();
	world.setDelta(delta);

	//CCLOG("X: %f", comp->posX);
	//CCLOG("Y: %f", comp->posY);
}
