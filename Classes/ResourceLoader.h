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
	void dispatchUpdateEvent(EventResourceLoader::EventCode code, const std::string &message = "", const std::string &assetId = "");

	/*void startUpdate();
	void updateSucceed();

	* @brief  Call back function for recording downloading percent of the current asset,
	 the progression will then be reported to user's listener registed in addUpdateProgressEventListener
	 @param total       Total size to download for this asset
	 @param downloaded  Total size already downloaded for this asset
	 @param url         The url of this asset
	 @param customId    The key of this asset
	 @warning AssetsManagerEx internal use only
	 * @js NA
	 * @lua NA

	virtual void onProgress(double total, double downloaded, const std::string &url, const std::string &customId);

	* @brief  Call back function for success of the current asset
	 the success event will then be send to user's listener registed in addUpdateEventListener
	 @param srcUrl      The url of this asset
	 @param customId    The key of this asset
	 @warning AssetsManagerEx internal use only
	 * @js NA
	 * @lua NA

	virtual void onSuccess(const std::string &srcUrl, const std::string &storagePath, const std::string &customId);*/

private:

	//! The event of the current AssetsManagerEx in event dispatcher
	std::string _eventName;

	//! Reference to the global event dispatcher
	EventDispatcher *_eventDispatcher;

	//! State of update
	State _updateState;

	//! Download percent
	float _percent;
};

#endif /* __RESOURCE_LOADER_H__ */
