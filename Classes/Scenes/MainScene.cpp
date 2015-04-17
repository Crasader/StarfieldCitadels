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
    _map->setPosition(0, 0);
    baseLayer->addChild(_map, 0);

    return true;
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
    
    // 1. Convert to world coordinate space
    // 2. Ray trace
    // 3. Update look at and camera position
    
    // Octree
    float scale = scaleAdjust*_viewportScaleOrg;
    
    
    _coords->setPosition(centerNew);
    char tmp[100];
    sprintf(tmp,"%f,%f", centerNew.x, centerNew.y);
    _coords->setString(tmp);
}

// Handler for Tap/Drag/Pinch Events
void MainScene::TapDragPinchInputTap(const TOUCH_DATA_T& point)
{
    CCLOG("Touch");
    _coords->setPosition(point.pos);
    char tmp[100];
    sprintf(tmp,"%f,%f", point.pos.x, point.pos.y);
    _coords->setString(tmp);
}

void MainScene::TapDragPinchInputLongTap(const TOUCH_DATA_T& point)
{
    CCLOG("Long Tap");
}

void MainScene::TapDragPinchInputPinchBegin(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
    CCLOG("Pinch Begin");
    Notifier::Instance().Notify(Notifier::NE_RESET_DRAW_CYCLE);
    //_viewportCenterOrg = Viewport::Instance().GetCenterMeters();
    //_viewportScaleOrg = Viewport::Instance().GetScale();
    PinchViewport(GetPinchPoint0().pos, GetPinchPoint1().pos, point0.pos, point1.pos);
}

void MainScene::TapDragPinchInputPinchContinue(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
    Notifier::Instance().Notify(Notifier::NE_RESET_DRAW_CYCLE);
    PinchViewport(GetPinchPoint0().pos, GetPinchPoint1().pos, point0.pos, point1.pos);
}

void MainScene::TapDragPinchInputPinchEnd(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
    Notifier::Instance().Notify(Notifier::NE_RESET_DRAW_CYCLE);
}

void MainScene::TapDragPinchInputDragBegin(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
    Notifier::Instance().Notify(Notifier::NE_RESET_DRAW_CYCLE);
}

void MainScene::TapDragPinchInputDragContinue(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
    CCLOG("Draging");
    auto delta = point1.pos - point0.pos;
    auto currentPos = _map->getPosition();
    _map->setPosition(currentPos+delta);
}

void MainScene::TapDragPinchInputDragEnd(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
    
}

void MainScene::SetZoom(float scale)
{
    Viewport::Instance().SetScale(scale);
}

Vec3 MainScene::convertToWorldCoords(Vec2 pos)
{
    auto matProjection = _camera->getViewProjectionMatrix();
    matProjection.inverse();
    
    float in[4];
    float winZ = 1.0;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    in[0] = (2.0f*((float)(pos.x-0)/(visibleSize.width-0)))-1.0f;
    in[1]=1.0f-(2.0f*((float)(pos.y-0)/(visibleSize.height-0)));
    in[2]=2.0*winZ-1.0;
    in[3]=1.0;
    
    auto vIn = Vec4(in[0], in[1], in[2], in[3]);
    auto worldPos = matProjection*vIn;
    
    
    
    worldPos.w = 1.0 / worldPos.w;
    
    worldPos.x *= worldPos.w;
    worldPos.y *= worldPos.w;
    worldPos.z *= worldPos.w;
    
    return Vec3(worldPos.x, worldPos.y, worldPos.z);
}
