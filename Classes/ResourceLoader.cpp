/*
 * ResourceLoader.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: ihall1
 */

#include "ResourceLoader.h"
#include "dirent.h"

ResourceLoader::ResourceLoader()
: _numberOfSprites(2),
  _numberOfLoadedSprites(0) {

}

ResourceLoader::~ResourceLoader() {
	// TODO Auto-generated destructor stub
}

void ResourceLoader::startResourceLoad() {
	GameManager::getInstance()->SetUpScaleFactors();

	std::vector<std::string> resDirOrders = FileUtils::getInstance()->getSearchResolutionsOrder();

	CCLOG("# of resDirOrders: %d", resDirOrders.size());
	for(std::string path : resDirOrders)
	{
		CCLOG("Path: %s", path.c_str());
	}

	std::vector<std::string> searchPaths = FileUtils::getInstance()->getSearchPaths();
	CCLOG("# of searchPaths: %d", searchPaths.size());
	for(std::string path : searchPaths)
	{
		CCLOG("Path: %s", path.c_str());
	}

	std::string temp = FileUtils::getInstance()->fullPathForFilename("BG.png");
	CCLOG("FilePath: %s", temp.c_str());

	Director::getInstance()->getTextureCache()->addImageAsync("BG.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Floor.png", CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
}

void ResourceLoader::loadingCallBack(Texture2D *texture) {
	++_numberOfLoadedSprites;
	char tmp[10];
	sprintf(tmp,"%%%d", (int)(((float)_numberOfLoadedSprites / _numberOfSprites) * 100));

	CCLOG("Percent: %s", tmp);
}

