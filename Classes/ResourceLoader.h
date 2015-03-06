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

struct Order
{
	bool operator()(std::string const& a, std::string const& b)
	{
		return FileUtils::getInstance()->getFileSize(a) < FileUtils::getInstance()->getFileSize(b);
	}
};

class ResourceLoader : public Ref {
private:
	int _numberOfSprites;
	int _numberOfLoadedSprites;
protected:
	ResourceLoader();
	virtual ~ResourceLoader();
public:
	void startResourceLoad();
	void loadingCallBack(Texture2D *texture);

	//! Update states
	enum class State
	{
		UNCHECKED,
		UPDATING,
		FAIL_TO_UPDATE
	};

	const static std::string BATCH_UPDATE_ID;

	static ResourceLoader* create();

	/** @brief Update with the current local manifest.
	 */
	void update();

	/** @brief Gets the current update state.
	 */
	State getState() const;

protected:
	void dispatchLoadEvent(EventResourceLoader::EventCode code, const std::string &message = "", const std::string &assetId = "");

private:

	//! The event of the current Resource Loader in event dispatcher
	std::string _eventName;

	//! Reference to the global event dispatcher
	EventDispatcher *_eventDispatcher;

	//! State of update
	State _updateState;

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
