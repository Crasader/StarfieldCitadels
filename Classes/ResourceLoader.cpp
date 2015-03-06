/*
 * ResourceLoader.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: ihall1
 */

#include "ResourceLoader.h"
#include "EventListenerResourceLoader.h"

ResourceLoader::ResourceLoader()
: _numberOfSprites(19)
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

	/*std::vector<std::string> fileNames = {
		"BG.png",
		"Floor.png",
		"grossini_dance_01.png",
		"grossini_dance_02.png",
		"grossini_dance_03.png",
		"grossini_dance_04.png",
		"grossini_dance_05.png",
		"grossini_dance_06.png",
		"grossini_dance_07.png",
		"grossini_dance_08.png",
		"grossini_dance_09.png",
		"grossini_dance_10.png",
		"grossini_dance_11.png",
		"grossini_dance_12.png",
		"grossini_dance_13.png",
		"grossini_dance_14.png",
		"background1.png",
		"background2.png",
		"background3.png"
	};*/

	std::priority_queue<std::string, std::vector<std::string>, Order> test;
	test.push("BG.png");
	test.push("Floor.png");
	test.push("grossini_dance_01.png");
	test.push("grossini_dance_02.png");
	test.push("grossini_dance_03.png");
	test.push("grossini_dance_04.png");
	test.push("grossini_dance_05.png");
	test.push("grossini_dance_06.png");
	test.push("grossini_dance_07.png");
	test.push("grossini_dance_08.png");
	test.push("grossini_dance_09.png");
	test.push("grossini_dance_10.png");
	test.push("grossini_dance_11.png");
	test.push("grossini_dance_12.png");
	test.push("grossini_dance_13.png");
	test.push("grossini_dance_14.png");
	test.push("background1.png");
	test.push("background2.png");
	test.push("background3.png");

	//CCLOG("%s", test.top().c_str());

	while(!test.empty()) {
		CCLOG("%s", test.top().c_str());
		CCLOG("%l", FileUtils::getInstance()->getFileSize("background1.png"));
		test.pop();
	}

/*	for(int i = 0; i < fileNames.size(); i++) {
		_totalSize += FileUtils::getInstance()->getFileSize(fileNames[i]);
	}*/

	Director::getInstance()->getTextureCache()->addImageAsync("BG.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Floor.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("grossini_dance_01.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("grossini_dance_02.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("grossini_dance_03.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("grossini_dance_04.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("grossini_dance_05.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("grossini_dance_06.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("grossini_dance_07.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("grossini_dance_08.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("grossini_dance_09.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("grossini_dance_10.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("grossini_dance_11.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("grossini_dance_12.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("grossini_dance_13.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("grossini_dance_14.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("background1.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("background2.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("background3.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
}

void ResourceLoader::loadingCallBack(Texture2D *texture) {
	++_numberOfLoadedSprites;
	dispatchLoadEvent(EventResourceLoader::EventCode::RESOURCE_LOADED);
	//char tmp[10];
	//sprintf(tmp,"%%%d", (int)(((float)_numberOfLoadedSprites / _numberOfSprites) * 100));
	_percent = ((float)_numberOfLoadedSprites / _numberOfSprites) * 100;
	//CCLOG("Percent: %f", _percent);

	if(_numberOfLoadedSprites == _numberOfSprites)
	{
		// Dispatch one event for load progression to signal the final graphics completion
		dispatchLoadEvent(EventResourceLoader::EventCode::LOAD_PROGRESSION);

		// When finished preloading graphics dispatch LOAD_FINISHED event
		dispatchLoadEvent(EventResourceLoader::EventCode::LOAD_FINISHED);
	}
	else
	{
		dispatchLoadEvent(EventResourceLoader::EventCode::LOAD_PROGRESSION);
	}
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

void ResourceLoader::dispatchLoadEvent(EventResourceLoader::EventCode code, const std::string &assetId/* = ""*/, const std::string &message/* = ""*/)
{
    EventResourceLoader event(_eventName, this, code, _percent, assetId, message);
    _eventDispatcher->dispatchEvent(&event);
}

