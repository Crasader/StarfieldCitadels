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

GameManager *GameManager::Instance() {
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

	_dir  = (char*)kDIRHD;
	_scaleFactor = 1.0;

	if(visibleSize.width * visibleSize.height > 960 * 640) {
		_scaleFactor = 2.0;
		_dir = (char*)kDIRUHD;
	}
	else if(visibleSize.width * visibleSize.height <= 480 * 320) {
		_scaleFactor = 0.5;
		_dir = (char*)kDIRND;
	}

	_scaleX = visibleSize.width / (960 * _scaleFactor);
	_scaleY = visibleSize.height / (640 * _scaleFactor);

	CCLOG("_scaleFactor:%.2f _scaleX:%.2f _scaleY:%.2f", _scaleFactor, _scaleX, _scaleY);
}

void GameManager::GetFileName(char *array, const int len, const char *name) {
	memset(array, 0, sizeof(char) * len);
	sprintf(array, "%s%s", _dir, name);
}
