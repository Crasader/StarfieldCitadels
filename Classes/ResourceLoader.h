/*
 * ResourceLoader.h
 *
 *  Created on: Mar 2, 2015
 *      Author: ihall1
 */

#ifndef __RESOURCE_LOADER_H__
#define __RESOURCE_LOADER_H__
#define COCOS2D_DEBUG 1

#include "GameManager.h"
#include "EventResourceLoader.h"

#include "cocos2d.h"
USING_NS_CC;

// Order Compare type struct declaration
struct OrderByFileSize
{
	bool operator()(std::string const& a, std::string const& b)
	{
		return FileUtils::getInstance()->getFileSize(a) < FileUtils::getInstance()->getFileSize(b);
	}
};

class ResourceLoader : public Ref {
protected:
    ResourceLoader();
    virtual ~ResourceLoader();
    
    void dispatchLoadEvent(EventResourceLoader::EventCode code, const std::string &message = "", const std::string &assetId = "");
public:
	void startResourceLoad();

	static ResourceLoader* create();
    
    void addImageToBePreloaded(std::string fileName);
private:
    int _numberOfSprites;
    int _numberOfLoadedSprites;
    
    // Collection definition
    std::priority_queue<std::string, std::vector<std::string>, OrderByFileSize> _orderedFileList;
    
    //! The event of the current Resource Loader in event dispatcher
    std::string _eventName;
    
    //! Reference to the global event dispatcher
    EventDispatcher *_eventDispatcher;
    
    //! Preload percent
    float _percent;
    
    //! Preload percent by file
    float _percentByFile;
    
    //! Total size of files needed to be preloaded
    float _totalSize;
    
    //! Total size of files already preloaded
    float _preloadedSize;
};

#endif /* __RESOURCE_LOADER_H__ */
