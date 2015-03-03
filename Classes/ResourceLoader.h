/*
 * ResourceLoader.h
 *
 *  Created on: Mar 2, 2015
 *      Author: ihall1
 */

#ifndef __RESOURCE_LOADER_H__
#define __RESOURCE_LOADER_H__

#include "GameManager.h"

class ResourceLoader {
public:
	ResourceLoader();
	ResourceLoader(char * fileExt);
	virtual ~ResourceLoader();
};

#endif /* __RESOURCE_LOADER_H__ */
