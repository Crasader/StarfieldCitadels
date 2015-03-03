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

#include "cocos2d.h"
USING_NS_CC;

class ResourceLoader {
private:
	int _numberOfSprites;
	int _numberOfLoadedSprites;
public:
	ResourceLoader();
	virtual ~ResourceLoader();

	void startResourceLoad();
	void loadingCallBack(Texture2D *texture);
};

#endif /* __RESOURCE_LOADER_H__ */
