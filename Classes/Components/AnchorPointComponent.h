/*
 * AnchorPointComponent.h
 *
 *  Created on: Feb 25, 2015
 *      Author: ihall1
 */

#ifndef __ANCHOR_POINT_COMPONENT_H__
#define __ANCHOR_POINT_COMPONENT_H__

#include "../Evolve/evolve2d.h"
#include "cocos2d.h"
USING_NS_CC;

class AnchorPointComponent: public evolve2d::Component {
private:
	float _anchorPointX;
	float _anchorPointY;
public:
	AnchorPointComponent(float anchorPointX, float anchorPointY);
	virtual ~AnchorPointComponent();

	float getAnchorPointX();
	float getAnchorPointY();
};

#endif /* __ANCHOR_POINT_COMPONENT_H__ */
