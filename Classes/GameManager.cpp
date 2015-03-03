/*
 * GameManager.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: ihall1
 */

#include "GameManager.h"
#include "cocos2d.h"

USING_NS_CC;

#define kDIRHD "HD/"
#define kDIRUHD "UHD/"
#define kDIRND "ND/"

GameManager *GameManager::_pInstance = NULL;

GameManager *GameManager::getInstance() {
	if(!_pInstance)
		_pInstance = new GameManager;
	return _pInstance;
}

float GameManager::GetScaleX() {
	return _scaleX;
}

float GameManager::GetScaleY() {
	return _scaleY;
}

float GameManager::GetScaleFactor() {
	return _scaleFactor;
}

void GameManager::SetUpScaleFactors() {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	std::vector<std::string> resDirOrders;

	if(visibleSize.width * visibleSize.height > 960 * 640) {
		_scaleFactor = 2.0;
		resDirOrders.push_back(kDIRUHD);

	}
	else if(visibleSize.width * visibleSize.height <= 480 * 320) {
		_scaleFactor = 0.5;
		resDirOrders.push_back(kDIRND);
	}
	else
	{
		_scaleFactor = 1.0;
		resDirOrders.push_back(kDIRHD);
	}

	// Set search resolutions order for application
	FileUtils::getInstance()->setSearchResolutionsOrder(resDirOrders);

	_scaleX = visibleSize.width / (960 * _scaleFactor);
	_scaleY = visibleSize.height / (640 * _scaleFactor);

	CCLOG("_scaleFactor:%.2f _scaleX:%.2f _scaleY:%.2f", _scaleFactor, _scaleX, _scaleY);
}
