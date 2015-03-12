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

    _lastDistance = 0;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Generate Scene layers
    auto baseLayer = BaseLayer::create();
    baseLayer->setName("BaseLayer");
    
    auto animationLayer = AnimationLayer::create();
    animationLayer->setName("AnimationLayer");
    
    auto hudLayer = HUDLayer::create();
    hudLayer->setName("HUDLayer");
    
    auto uiLayer = UILayer::create();
    uiLayer->setName("UILayer");
    
    this->addChild(baseLayer, 0);
    this->addChild(animationLayer, 1);
    this->addChild(hudLayer, 2);
    this->addChild(uiLayer, 3);
    
    auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesMoved = [baseLayer, this](const std::vector<Touch*>& touches, Event  *event) {

		if(touches.size() == 2)
		{
			auto touch1 = touches[0];
			auto touch2 = touches[1];
			Vec2 delta1 = touch1->getDelta();
			Vec2 delta2 = touch2->getDelta();

			if ((fabs(delta1.x)<_kPinchThreshold && fabs(delta1.y)<_kPinchThreshold) || (fabs(delta2.x)<_kPinchThreshold && fabs(delta2.y)<_kPinchThreshold)) {
				return;
			}

			float distance = touch1->getLocation().distance(touch2->getLocation());
			if(!_lastDistance) {
				_lastDistance = distance;
				return;
			}

			if (_lastDistance<=distance) {
				// type open
			}
			else {
				// type close
			}

			auto node = baseLayer->getChildByName("Map");
			node->setAnchorPoint(Vec2(0.5, 0.5));
			node->setScale(distance/_lastDistance);
		}
		else
		{
			auto touch = touches[0];

			auto diff = touch->getDelta();
			auto node = baseLayer->getChildByName("Map");
			auto currentPos = node->getPosition();
			node->setPosition(currentPos + diff);
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, baseLayer);

    auto map = TMXTiledMap::create("iso-test.tmx");
    map->setName("Map");
    baseLayer->addChild(map);

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
