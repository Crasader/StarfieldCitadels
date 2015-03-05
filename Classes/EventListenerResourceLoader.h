/*
 * EventListenerResourceLoader.h
 *
 *  Created on: Mar 5, 2015
 *      Author: ihall1
 */

#ifndef __EVENT_LISTENER_RESOURCE_LOADER_H__
#define __EVENT_LISTENER_RESOURCE_LOADER_H__

#include "cocos2d.h"
USING_NS_CC;

class EventResourceLoader;
class ResourceLoader;

class EventListenerResourceLoader : public cocos2d::EventListenerCustom
{
public:
    friend class ResourceLoader;

    /** Creates an event listener with type and callback.
     *  @param eventType The type of the event.
     *  @param callback The callback function when the specified event was emitted.
     */
    static EventListenerResourceLoader* create(ResourceLoader *ResourceLoader, const std::function<void(EventResourceLoader*)>& callback);

    /// Overrides
    virtual bool checkAvailable() override;
    virtual EventListenerResourceLoader* clone() override;

protected:
    /** Constructor */
    EventListenerResourceLoader();

    /** Initializes event with type and callback function */
    bool init(const ResourceLoader *ResourceLoader, const std::function<void(EventResourceLoader*)>& callback);

protected:
    static const std::string LISTENER_ID;

    std::function<void(EventResourceLoader*)> _onResourceLoaderEvent;

    const ResourceLoader *_ResourceLoader;
};

#endif /* __EVENT_LISTENER_RESOURCE_LOADER_H__ */
