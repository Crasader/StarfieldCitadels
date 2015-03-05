/*
 * EventResourceLoader.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: ihall1
 */

#include "EventResourceLoader.h"
#include "ResourceLoader.h"

EventResourceLoader::EventResourceLoader(const std::string& eventName, ResourceLoader *loader, const EventCode &code, float percent/* = 0 */, const std::string& assetId/* = "" */, const std::string& message/* = "" */)
: EventCustom(eventName)
, _code(code)
, _loader(loader)
, _message(message)
, _assetId(assetId)
, _percent(percent)
{
	//CCLOG("%f", _percent);
}

