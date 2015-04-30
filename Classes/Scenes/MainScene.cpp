/*
 * MainScene.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: ihall1
 */

#include "MainScene.h"
#include "../Gestures/Viewport.h"

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
    
    Viewport::Instance().Init(100.0);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Generate Scene layers
    auto baseLayer = BaseLayer::create();
    baseLayer->setName("BaseLayer");
    baseLayer->setContentSize(Size(4296, 2248));
    drawBoundingBox(baseLayer, Color4F(1,1,1,1));
    baseLayer->setAnchorPoint(Vec2(0.5, 0.5));
    
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
    
    _coords = Label::createWithTTF("Test", "fonts/arial.ttf", 30);
    _coords->setName("Coords");
    _coords->setPosition(visibleSize.width/2, visibleSize.height/2);
    baseLayer->addChild(_coords, 1);
    
    _tapDragPinchInput = TapDragPinchInput::create(this);
    _tapDragPinchInput->setName("TouchLayer");
    _tapDragPinchInput->setAnchorPoint(Vec2(0.5, 0.5));
    this->addChild(_tapDragPinchInput,4);

    _map = TMXTiledMap::create("iso-test.tmx");
    //_map = TMXTiledMap::create("orthogonal-test6.tmx");
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
    Viewport& vp = Viewport::Instance();
    float distOrg = p0Org.distance(p1Org);
    float distNew = p0.distance(p1);

    if(distOrg < 1)
       distOrg = 1;
    if(distNew < 1)
       distNew = 1;

    float scaleAdjust = distNew/distOrg;
    Vec2 centerOld = p0Org.getMidpoint(p1Org);
    Vec2 centerNew = p0.getMidpoint(p1);
    
    vp.SetCenter(_viewportCenterOrg-centerNew+centerOld);
    vp.SetScale(scaleAdjust*_viewportScaleOrg);
    
    auto baseLayer = this->getChildByName("BaseLayer");
    auto baseLayerSize = baseLayer->getContentSize();
    auto currentScale = baseLayer->getScale();

    // Compute anchor point
    CCLOG("Current scale: %f", currentScale);
    if(currentScale < MAX_SCALE_LIMIT-1)
    {
    	//auto baseLayerAP = baseLayer->getAnchorPoint();
    	//CCLOG("Base Layer Anchor Point: %f, %f", baseLayerAP.x, baseLayerAP.y);
    	//auto baseLayerPos = baseLayer->getPosition();
    	//baseLayer->setPosition(_pinchPoint);
    	auto tempAnchPoint = Vec2(_pinchPoint.x/baseLayerSize.width, _pinchPoint.y/baseLayerSize.height);
    	//CCLOG("Anchor Point: %f, %f", tempAnchPoint.x, tempAnchPoint.y);
		baseLayer->setAnchorPoint(tempAnchPoint);
		baseLayer->setScale(scaleAdjust*_viewportScaleOrg);
		//baseLayer->setPosition(baseLayerPos);
		//baseLayer->setAnchorPoint(baseLayerAP);
    }
    else
    {

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

    Notifier::Instance().Notify(Notifier::NE_RESET_DRAW_CYCLE);
    _viewportCenterOrg = Viewport::Instance().GetCenterMeters();
    _viewportScaleOrg = baseLayer->getScale();
    PinchViewport(GetPinchPoint0().pos, GetPinchPoint1().pos, point0.pos, point1.pos);
}

void MainScene::TapDragPinchInputPinchContinue(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
    Notifier::Instance().Notify(Notifier::NE_RESET_DRAW_CYCLE);
    PinchViewport(GetPinchPoint0().pos, GetPinchPoint1().pos, point0.pos, point1.pos);
}

void MainScene::TapDragPinchInputPinchEnd(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
	auto baseLayer = this->getChildByName("BaseLayer");
	auto currentScale = baseLayer->getScale();
	auto baseLayerSize = baseLayer->getContentSize();

	if(currentScale > MAX_SCALE && currentScale <= MAX_SCALE_LIMIT)
	{
		//auto baseLayerAP = baseLayer->getAnchorPoint();
		baseLayer->setAnchorPoint(Vec2(_pinchPoint.x/baseLayerSize.width, _pinchPoint.y/baseLayerSize.height));
		auto action = ScaleTo::create(0.5, MAX_SCALE);
		baseLayer->runAction(action);
		//baseLayer->setAnchorPoint(baseLayerAP);
	}
	CCLOG("Current Scale: %f", baseLayer->getScale());

	baseLayer->setAnchorPoint(Vec2(0.5, 0.5));
    Notifier::Instance().Notify(Notifier::NE_RESET_DRAW_CYCLE);
}

void MainScene::TapDragPinchInputDragBegin(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
    Notifier::Instance().Notify(Notifier::NE_RESET_DRAW_CYCLE);
}

void MainScene::TapDragPinchInputDragContinue(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
    //CCLOG("Draging");
    auto baseLayer = this->getChildByName("BaseLayer");
    auto localTouch0 = baseLayer->convertToNodeSpace(point0.pos);
    auto localTouch1 = baseLayer->convertToNodeSpace(point1.pos);
    auto delta = localTouch1 - localTouch0;
    /*CCLOG("Point 1: %f, %f", localTouch0.x, localTouch0.y);
    CCLOG("Point 2: %f, %f", localTouch1.x, localTouch1.y);
    CCLOG("Delta: %f, %f", delta.x, delta.y);*/
    auto currentPos = baseLayer->getPosition();
    baseLayer->setPosition(currentPos+delta*0.05);
}

void MainScene::TapDragPinchInputDragEnd(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
    
}

void MainScene::SetZoom(float scale)
{
    Viewport::Instance().SetScale(scale);
}
