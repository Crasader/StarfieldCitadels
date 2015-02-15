/*
 * AnimationLayer.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#include "AnimationLayer.h"

bool AnimationLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    
    return true;
}