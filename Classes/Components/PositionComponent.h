/*
 * PositionComponent.h
 *
 *  Created on: Feb 10, 2015
 *      Author: ihall1
 */

#ifndef __POSITION_COMPONENT_H__
#define __POSITION_COMPONENT_H__

#include "../Evolve/evolve2d.h"

class PositionComponent : public evolve2d::Component {
public:
	float posX;
	float posY;

	PositionComponent(float posX, float posY);
	virtual ~PositionComponent();
};

#endif /* __POSITION_COMPONENT_H__ */
