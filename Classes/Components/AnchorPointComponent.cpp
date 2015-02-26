/*
 * AnchorPointComponent.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: ihall1
 */

#include "AnchorPointComponent.h"

AnchorPointComponent::AnchorPointComponent(float anchorPointX, float anchorPointY) {
	this->_anchorPointX = anchorPointX;
	this->_anchorPointY = anchorPointY;

}

AnchorPointComponent::~AnchorPointComponent() {
	// TODO Auto-generated destructor stub
}

float AnchorPointComponent::getAnchorPointX() {
	return _anchorPointX;
}

float AnchorPointComponent::getAnchorPointY() {
	return _anchorPointY;
}

