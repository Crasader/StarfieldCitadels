/*
 * MainScene.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#include "MainScene.h"

Scene * MainScene::createScene()
{
    auto scene = MainScene::create();
    
    return scene;
}

bool MainScene::init()
{
    // Call super init first
    if(!Scene::init())
    {
        return false;
    }
    
    // Generate Scene layers
    auto baseLayer = BaseLayer::create();
    baseLayer->setName("BaseLayer");
    
    auto animationLayer = AnimationLayer::create();
    animationLayer->setName("AnimationLayer");
    
    auto hudLayer = HUDLayer::create();
    hudLayer->setName("HUDLayer");
    
    auto uiLayer = UILayer::create();
    uiLayer->setName("UILayer");
    
    this->addChild(baseLayer);
    this->addChild(animationLayer);
    this->addChild(hudLayer);
    this->addChild(uiLayer);
    
    // Initialize managers
    sm = world.getSystemManager();
    em = world.getEntityManager();
    
    // Create and initialize all systems
    movementSys = new MovementSystem();
    sm->setSystem(movementSys);
    renderSys = new RenderSystem();
    sm->setSystem(renderSys);
    sm->initializeAll(); // Calls the initialize method in each system
    
    Entity & player = em->create();
    player.addComponent(new PositionComponent(0,0));
    player.addComponent(new VelocityComponent(2,4));
    player.addComponent(new GraphicsComponent(Sprite::create("CloseNormal.png")));
    player.addComponent(new RenderComponent(this->getChildByName("BaseLayer")));
    player.refresh();
    
    comp = (PositionComponent*)player.getComponent<PositionComponent>();
    
    this->scheduleUpdate();
    
    return true;
}

void MainScene::update(float delta) {
    world.loopStart();
    world.setDelta(delta);
    movementSys->process();
    renderSys->process();
    
    //CCLOG("X: %f", comp->posX);
    //CCLOG("Y: %f", comp->posY);
}
