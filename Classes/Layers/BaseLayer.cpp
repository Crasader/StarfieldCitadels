/*
 * BaseLayer.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#include "BaseLayer.h"

bool BaseLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    
    return true;
}