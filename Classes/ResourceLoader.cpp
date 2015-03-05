/*
 * ResourceLoader.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: ihall1
 */

#include "ResourceLoader.h"
#include "EventListenerResourceLoader.h"

ResourceLoader::ResourceLoader()
: _numberOfSprites(2)
, _numberOfLoadedSprites(0)
, _percent(0)
{
	_eventDispatcher = Director::getInstance()->getEventDispatcher();
	std::string pointer = StringUtils::format("%p", this);
	_eventName = EventListenerResourceLoader::LISTENER_ID + pointer;

	GameManager::getInstance()->SetUpScaleFactors();
}

ResourceLoader::~ResourceLoader() {
	// TODO Auto-generated destructor stub
}

void ResourceLoader::startResourceLoad() {
	std::vector<std::string> resDirOrders = FileUtils::getInstance()->getSearchResolutionsOrder();

	CCLOG("# of resDirOrders: %lu", resDirOrders.size());
	for(std::string path : resDirOrders)
	{
		CCLOG("Path: %s", path.c_str());
	}

	std::vector<std::string> searchPaths = FileUtils::getInstance()->getSearchPaths();
	CCLOG("# of searchPaths: %lu", searchPaths.size());
	for(std::string path : searchPaths)
	{
		CCLOG("Path: %s", path.c_str());
	}

	std::string temp = FileUtils::getInstance()->fullPathForFilename("BG.png");
	CCLOG("FilePath: %s", temp.c_str());

	Director::getInstance()->getTextureCache()->addImageAsync("BG.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Floor.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
}

void ResourceLoader::loadingCallBack(Texture2D *texture) {
	++_numberOfLoadedSprites;
	dispatchUpdateEvent(EventResourceLoader::EventCode::RESOURCE_LOADED);
	//char tmp[10];
	//sprintf(tmp,"%%%d", (int)(((float)_numberOfLoadedSprites / _numberOfSprites) * 100));
	_percent = ((float)_numberOfLoadedSprites / _numberOfSprites) * 100;
	//CCLOG("Percent: %f", _percent);

	if(_numberOfLoadedSprites == _numberOfSprites)
		dispatchUpdateEvent(EventResourceLoader::EventCode::LOAD_FINISHED);
	else
		dispatchUpdateEvent(EventResourceLoader::EventCode::LOAD_PROGRESSION);
}

ResourceLoader* ResourceLoader::create()
{
	ResourceLoader* ret = new (std::nothrow) ResourceLoader();
    if (ret)
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

ResourceLoader::State ResourceLoader::getState() const
{
    return _updateState;
}

void ResourceLoader::dispatchUpdateEvent(EventResourceLoader::EventCode code, const std::string &assetId/* = ""*/, const std::string &message/* = ""*/)
{
    EventResourceLoader event(_eventName, this, code, _percent, assetId, message);
    _eventDispatcher->dispatchEvent(&event);
}

