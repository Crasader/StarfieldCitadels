/*
 * VelocityComponent.h
 *
 *  Created on: Feb 12, 2015
 *      Author: ihall1
 */

#ifndef __VELOCITY_COMPONENT_H__
#define __VELOCITY_COMPONENT_H__

#include "../Evolve/evolve2d.h"

class VelocityComponent: public evolve2d::Component {
public:
	float velocityX;
	float velocityY;

	VelocityComponent(float velocityX, float velocityY);
	virtual ~VelocityComponent();
};

#endif /* __VELOCITY_COMPONENT_H__ */
