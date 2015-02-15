/*
 * HUDLayer.h
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class HUDLayer : public Layer {
public:
	// Override Layer::init() with our own init method for HUDLayer
	virtual bool init();

	// Create the create method for "HUDLayer" and call init
	CREATE_FUNC(HUDLayer);
};

#endif /* __HUD_LAYER_H__ */
