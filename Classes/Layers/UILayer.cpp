/*
 * UILayer.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#include "UILayer.h"

bool UILayer::init() {
    if (!Layer::init()) {
        return false;
    }
    
    return true;
}