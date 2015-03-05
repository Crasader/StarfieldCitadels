/*
 * EventResourceLoader.h
 *
 *  Created on: Mar 5, 2015
 *      Author: ihall1
 */

#ifndef __EVENT_RESOURCE_LOADER_H__
#define __EVENT_RESOURCE_LOADER_H__
#define COCOS2D_DEBUG 1

#include "cocos2d.h"
USING_NS_CC;

class ResourceLoader;

class EventResourceLoader : public cocos2d::EventCustom
{
public:

    friend class ResourceLoader;

    //! Update events code
    enum class EventCode
    {
        LOAD_PROGRESSION,
        RESOURCE_LOADED,
        ERROR_LOADING,
        LOAD_FINISHED,
        LOAD_FAILED
    };

    inline EventCode getEventCode() const { return _code; };

    inline std::string getMessage() const { return _message; };

    inline std::string getAssetId() const { return _assetId; };

    inline ResourceLoader *getResourceLoader() const { return _loader; };

    inline float getPercent() const { return _percent; };

protected:
    /** Constructor */
    EventResourceLoader(const std::string& eventName, ResourceLoader *loader, const EventCode &code, float percent = 0, const std::string& assetId = "", const std::string& message = "");

private:
    EventCode _code;

    ResourceLoader *_loader;

    std::string _message;

    std::string _assetId;

    float _percent;
};

#endif /* __EVENT_RESOURCE_LOADER_H__ */
