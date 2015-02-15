/*
 * BaseLayer.h
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#ifndef __BASE_LAYER_H__
#define __BASE_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class BaseLayer : public Layer {
public:
	// Override Layer::init() with our own init method for BaseLayer
	virtual bool init();

	// Create the create method for "BaseLayer" and call init
	CREATE_FUNC(BaseLayer);
};

#endif /* __BASE_LAYER_H__ */
