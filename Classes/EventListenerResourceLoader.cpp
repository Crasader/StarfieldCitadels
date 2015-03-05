/*
 * EventListenerResourceLoader.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: ihall1
 */

#include "EventListenerResourceLoader.h"
#include "EventResourceLoader.h"
#include "ResourceLoader.h"
#include "cocos2d.h"

const std::string EventListenerResourceLoader::LISTENER_ID = "__resource_loader_";

EventListenerResourceLoader::EventListenerResourceLoader()
: _onResourceLoaderEvent(nullptr)
, _ResourceLoader(nullptr)
{
}

EventListenerResourceLoader* EventListenerResourceLoader::create(ResourceLoader *ResourceLoader, const std::function<void(EventResourceLoader*)>& callback)
{
    EventListenerResourceLoader* ret = new EventListenerResourceLoader();
    if (ret && ret->init(ResourceLoader, callback))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool EventListenerResourceLoader::init(const ResourceLoader *ResourceLoader, const std::function<void(EventResourceLoader*)>& callback)
{
    bool ret = false;

    _ResourceLoader = ResourceLoader;
    _onResourceLoaderEvent = callback;

    auto func = [this](EventCustom *event) -> void
    {
        EventResourceLoader *eventResourceLoader = dynamic_cast<EventResourceLoader*>(event);
        _onResourceLoaderEvent(eventResourceLoader);
    };
    std::string pointer = StringUtils::format("%p", ResourceLoader);
    if (EventListenerCustom::init(LISTENER_ID + pointer, func))
    {
        ret = true;
    }
    return ret;
}

EventListenerResourceLoader* EventListenerResourceLoader::clone()
{
    EventListenerResourceLoader* ret = new EventListenerResourceLoader();
    if (ret && ret->init(_ResourceLoader, _onResourceLoaderEvent))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool EventListenerResourceLoader::checkAvailable()
{
    bool ret = false;
    if (EventListener::checkAvailable() && _ResourceLoader != nullptr && _onResourceLoaderEvent != nullptr)
    {
        ret = true;
    }
    return ret;
}

