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
, _totalSize(0)
, _preloadedSize(0)
{
	_eventDispatcher = Director::getInstance()->getEventDispatcher();
	std::string pointer = StringUtils::format("%p", this);
	_eventName = EventListenerResourceLoader::LISTENER_ID + pointer;

    // Set up scale factors for images
	GameManager::getInstance()->SetUpScaleFactors();
}

ResourceLoader::~ResourceLoader() {
	// TODO Auto-generated destructor stub
}

void ResourceLoader::dispatchLoadEvent(EventResourceLoader::EventCode code, const std::string &assetId/* = ""*/, const std::string &message/* = ""*/)
{
    EventResourceLoader event(_eventName, this, code, _percent, assetId, message);
    _eventDispatcher->dispatchEvent(&event);
}

void ResourceLoader::startResourceLoad() {
    // Construct ordered list of all images to be preloaded
    buildPreloadingList();
    
    while(!_orderedFileList.empty()) {
        // Current file stats from largest file to smallest file
        std::string fileName = _orderedFileList.top();
        long fileSize = FileUtils::getInstance()->getFileSize(_orderedFileList.top().c_str());
        
        Director::getInstance()->getTextureCache()->addImageAsync(_orderedFileList.top(), [this, fileName, fileSize](Texture2D *texture)
        {
            ++_numberOfLoadedSprites;
            _preloadedSize += fileSize;
            dispatchLoadEvent(EventResourceLoader::EventCode::RESOURCE_LOADED, fileName);
            _percent = ((float)_preloadedSize / _totalSize) * 100;

            if(_preloadedSize == _totalSize)
            {
                // Dispatch one event for load progression to signal the final graphics completion
                dispatchLoadEvent(EventResourceLoader::EventCode::LOAD_PROGRESSION, fileName);
                
                // When finished preloading graphics dispatch LOAD_FINISHED event
                dispatchLoadEvent(EventResourceLoader::EventCode::LOAD_FINISHED, fileName);
            }
            else
            {
                dispatchLoadEvent(EventResourceLoader::EventCode::LOAD_PROGRESSION, fileName);
            }
        });
        _orderedFileList.pop();
    }
}

ResourceLoader* ResourceLoader::create() {
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

void ResourceLoader::buildPreloadingList() {
    // Add all images we want to preload textures for. Add new images here.
    addImageToBePreloaded("title.png");
    addImageToBePreloaded("Floor.png");
    addImageToBePreloaded("grossini_dance_01.png");
    addImageToBePreloaded("grossini_dance_02.png");
    addImageToBePreloaded("grossini_dance_03.png");
    addImageToBePreloaded("grossini_dance_04.png");
    addImageToBePreloaded("grossini_dance_05.png");
    addImageToBePreloaded("grossini_dance_06.png");
    addImageToBePreloaded("grossini_dance_07.png");
    addImageToBePreloaded("grossini_dance_08.png");
    addImageToBePreloaded("grossini_dance_09.png");
    addImageToBePreloaded("grossini_dance_10.png");
    addImageToBePreloaded("grossini_dance_11.png");
    addImageToBePreloaded("grossini_dance_12.png");
    addImageToBePreloaded("grossini_dance_13.png");
    addImageToBePreloaded("grossini_dance_14.png");
    addImageToBePreloaded("background1.png");
    addImageToBePreloaded("background2.png");
    addImageToBePreloaded("background3.png");
}

void ResourceLoader::addImageToBePreloaded(std::string fileName) {
    _totalSize += FileUtils::getInstance()->getFileSize(fileName);
    _orderedFileList.push(fileName);
}

