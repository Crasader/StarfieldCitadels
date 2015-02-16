/*
 * MainScene.h
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__
#define COCOS2D_DEBUG 1

#include "../Evolve/evolve2d.h"
using namespace evolve2d;

#include "cocos2d.h"
// Using namespace cocos2d macro
USING_NS_CC;

#include "../Components/Components.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"

class MainScene : public Scene {
private:
    World world;
    SystemManager * sm;
    EntityManager * em;
    
    // System declaration
    MovementSystem * movementSys;
    RenderSystem * renderSys;
    
    // Entity declaration
    
    // Component declaration
    PositionComponent * comp;
public:
	static Scene * createScene();

	// Override Scene::init() with our own init method for our main scene
	virtual bool init();
    
    virtual void update(float delta);

	// Create the create method for "MainScene" and make the call to the init method using this macro
	CREATE_FUNC(MainScene);
};

#endif /* __MAIN_SCENE_H__ */
