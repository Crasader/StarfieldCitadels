/*
 * UILayer.h
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#ifndef __UI_LAYER_H__
#define __UI_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class UILayer : Layer {
public:
	// Override Layer::init() with our own init method for UILayer
	virtual bool init();

	// Create the create method for "UILayer" and call init
	CREATE_FUNC(UILayer);
};

#endif /* __UI_LAYER_H__ */
