/*
 * AnimationLayer.h
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#ifndef __ANIMATION_LAYER_H__
#define __ANIMATION_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class AnimationLayer : public Layer {
public:
	// Override Layer::init() with our own init method for AnimationLayer
	virtual bool init();

	// Create the create method for "AnimationLayer" and call init
	CREATE_FUNC(AnimationLayer);
};

#endif /* __ANIMATION_LAYER_H__ */
