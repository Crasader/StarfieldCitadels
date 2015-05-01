/*
 * MainScene.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#include "MainScene.h"

const float MAX_SCALE = 6.0;
const float MAX_SCALE_LIMIT = 10.0;

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Generate Scene layers
    auto baseLayer = BaseLayer::create();
    baseLayer->setName("BaseLayer");
    baseLayer->setContentSize(Size(2248, 1224));
    drawBoundingBox(baseLayer, Color4F(1,1,1,1));
    auto bottomLeft = Vec2(visibleSize.width/2-baseLayer->getContentSize().width/2, visibleSize.height/2-baseLayer->getContentSize().height/2);
    auto topRight = Vec2(bottomLeft.x+baseLayer->getContentSize().width, bottomLeft.y+baseLayer->getContentSize().height);
    baseLayer->setPosition(bottomLeft);
    baseLayer->ignoreAnchorPointForPosition(true);
    _bounds = Rect(bottomLeft.x, bottomLeft.y, topRight.x, topRight.y);
    
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
    
    _coords = Label::createWithTTF("", "fonts/arial.ttf", 30);
    _coords->setName("Coords");
    _coords->setPosition(visibleSize.width/2, visibleSize.height/2);
    baseLayer->addChild(_coords, 1);
    
    _tapDragPinchInput = TapDragPinchInput::create(this);
    _tapDragPinchInput->setName("TouchLayer");
    _tapDragPinchInput->setAnchorPoint(Vec2(0.5, 0.5));
    this->addChild(_tapDragPinchInput,4);

    _map = TMXTiledMap::create("asteroid_map.tmx");
    _map->setName("Map");
    _map->setAnchorPoint(Vec2(0.5, 0.5));
    auto baseLayerSize = baseLayer->getContentSize();
    _map->setPosition(baseLayerSize.width/2, baseLayerSize.height/2);
    baseLayer->addChild(_map, 0);
    CCLOG("Map Size: %f, %f", _map->getContentSize().width, _map->getContentSize().height);
    drawBoundingBox(_map, Color4F(1, 1, 1, 1));

    return true;
}

void MainScene::drawBoundingBox(Node* target, Color4F color)
{
    glLineWidth(10);
    Size rectSize = target->getContentSize();
    CCLOG("Bounding Box: %f, %f, %f, %f", 0.0, 0.0, rectSize.width, rectSize.height);
    
    auto rectNode = DrawNode::create();
    rectNode->drawRect(Vec2(0, 0), Vec2(rectSize.width,rectSize.height), color);
    target->addChild(rectNode, 100);
}

void MainScene::update(float delta) {
    /*world.loopStart();
    world.setDelta(delta);
    movementSys->process();
    renderSys->process();*/
    
    //CCLOG("X: %f", comp->posX);
    //CCLOG("Y: %f", comp->posY);
}

// Misc methods
void MainScene::onEnter()
{
    Scene::onEnter();
}

void MainScene::onExit()
{
    Scene::onExit();
}

void MainScene::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();
    // It is a good practice to attach/detach from the Notifier
    // on screen transition times.  This gets you out of the question
    // of when the scene deletion occurs.
    Notifier::Instance().Attach(this, Notifier::NE_VIEWPORT_CHANGED);
    
    // Schedule Updates
    scheduleUpdate();
}

void MainScene::onExitTransitionDidStart()
{
    Scene::onExitTransitionDidStart();
    // It is a good practice to attach/detach from the Notifier
    // on screen transition times.  This gets you out of the question
    // of when the scene deletion occurs.
    Notifier::Instance().Detach(this);
    
    // Turn off updates
    unscheduleUpdate();
}

// Handler for Notifier Events
void MainScene::Notify(Notifier::NOTIFIED_EVENT_TYPE_T eventType, const void* eventData)
{
    switch(eventType)
    {
        case Notifier::NE_VIEWPORT_CHANGED:
            {
                
            }
            break;
        default:
            assert(false);
            break;
    }
}

void MainScene::PinchViewport(const Point& p0Org,const Point& p1Org, const Point& p0,const Point& p1)
{
    float distOrg = p0Org.distance(p1Org);
    float distNew = p0.distance(p1);

    if(distOrg < 1)
       distOrg = 1;
    if(distNew < 1)
       distNew = 1;

    float scaleAdjust = distNew/distOrg;
    Vec2 centerOld = p0Org.getMidpoint(p1Org);
    Vec2 centerNew = p0.getMidpoint(p1);
    
    auto baseLayer = this->getChildByName("BaseLayer");
    auto baseLayerSize = baseLayer->getContentSize();
    auto currentScale = baseLayer->getScale();

    // Compute anchor point
    if(currentScale < MAX_SCALE_LIMIT-2)
    {
    	auto tempAnchPoint = Vec2(_pinchPoint.x/baseLayerSize.width, _pinchPoint.y/baseLayerSize.height);
		baseLayer->setAnchorPoint(tempAnchPoint);
		baseLayer->setScale(scaleAdjust*_viewportScaleOrg);
    }
    
    _coords->setPosition(_pinchPoint);
    char tmp[100];
    sprintf(tmp,"%f,%f", _pinchPoint.x, _pinchPoint.y);
    _coords->setString(tmp);
}

// Handler for Tap/Drag/Pinch Events
void MainScene::TapDragPinchInputTap(const TOUCH_DATA_T& point)
{
    CCLOG("Touch");
    auto baseLayer = this->getChildByName("BaseLayer");
    auto mapPoint = baseLayer->convertToNodeSpace(point.pos);
    _coords->setPosition(mapPoint);
    char tmp[100];
    sprintf(tmp,"%f,%f", mapPoint.x, mapPoint.y);
    _coords->setString(tmp);
}

void MainScene::TapDragPinchInputLongTap(const TOUCH_DATA_T& point)
{
    CCLOG("Long Tap");
}

void MainScene::TapDragPinchInputPinchBegin(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
    CCLOG("Pinch Begin");

    auto baseLayer = this->getChildByName("BaseLayer");
    _pinchPoint = baseLayer->convertToNodeSpace(point0.pos.getMidpoint(point1.pos));

    _viewportScaleOrg = baseLayer->getScale();
    PinchViewport(GetPinchPoint0().pos, GetPinchPoint1().pos, point0.pos, point1.pos);
}

void MainScene::TapDragPinchInputPinchContinue(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
    PinchViewport(GetPinchPoint0().pos, GetPinchPoint1().pos, point0.pos, point1.pos);
}

void MainScene::TapDragPinchInputPinchEnd(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
	auto baseLayer = this->getChildByName("BaseLayer");
	auto currentScale = baseLayer->getScale();
	auto baseLayerSize = baseLayer->getContentSize();

	if(currentScale > MAX_SCALE && currentScale <= MAX_SCALE_LIMIT)
	{
		baseLayer->setAnchorPoint(Vec2(_pinchPoint.x/baseLayerSize.width, _pinchPoint.y/baseLayerSize.height));
		auto action = ScaleTo::create(0.5, MAX_SCALE);
		baseLayer->runAction(action);
	}
}

void MainScene::TapDragPinchInputDragBegin(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
    
}

void MainScene::TapDragPinchInputDragContinue(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
    auto baseLayer = this->getChildByName("BaseLayer");
    auto currentPos = baseLayer->getPosition();
    auto localTouch0 = baseLayer->convertToNodeSpace(point0.pos);
    auto localTouch1 = baseLayer->convertToNodeSpace(point1.pos);
    auto delta = localTouch1 - localTouch0;
    CCLOG("Delta: %f, %f", delta.x, delta.y);
    CCLOG("Current Pos: %f, %f", currentPos.x, currentPos.y);
    baseLayer->setPosition(currentPos+delta);
}

void MainScene::TapDragPinchInputDragEnd(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
    
}
