/*
 * ResourceLoader.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: ihall1
 */

#include "ResourceLoader.h"

ResourceLoader::ResourceLoader() {
	GameManager::getInstance()->SetUpScaleFactors();

}

ResourceLoader::~ResourceLoader() {
	// TODO Auto-generated destructor stub
}

