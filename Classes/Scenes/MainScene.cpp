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

    auto map = TMXTiledMap::create("iso-test.tmx");
    map->setName("Map");
    baseLayer->addChild(map);

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
}

// Handler for Tap/Drag/Pinch Events
void MainScene::TapDragPinchInputTap(const TOUCH_DATA_T& point)
{

}
void MainScene::TapDragPinchInputLongTap(const TOUCH_DATA_T& point)
{
}

void MainScene::TapDragPinchInputPinchBegin(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
   Notifier::Instance().Notify(Notifier::NE_RESET_DRAW_CYCLE);
   _viewportCenterOrg = Viewport::Instance().GetCenterMeters();
   _viewportScaleOrg = Viewport::Instance().GetScale();
   PinchViewport(GetPinchPoint0().pos, GetPinchPoint1().pos, point0.pos, point1.pos);
}
void MainScene::TapDragPinchInputPinchContinue(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
   Notifier::Instance().Notify(Notifier::NE_RESET_DRAW_CYCLE);
   _tapDragPinchInput->DrawDebug();
   PinchViewport(GetPinchPoint0().pos, GetPinchPoint1().pos, point0.pos, point1.pos);
}
void MainScene::TapDragPinchInputPinchEnd(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
   Notifier::Instance().Notify(Notifier::NE_RESET_DRAW_CYCLE);
}
void MainScene::TapDragPinchInputDragBegin(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
   Notifier::Instance().Notify(Notifier::NE_RESET_DRAW_CYCLE);
   _tapDragPinchInput->DrawDebug();
   switch(_dragBehavior)
   {
      case DB_TRACK:
         break;
      case DB_SEEK:
         break;
      case DB_PATH:
      {
         LINE_PIXELS_DATA ld;
         Notifier::Instance().Notify(Notifier::NE_RESET_DRAW_CYCLE);
         _path.clear();
         _path.push_back(point0.pos);
         _path.push_back(point1.pos);

         ld.start = point0.pos;
         ld.end = point1.pos;
         _lastPoint = point1.pos;
         Notifier::Instance().Notify(Notifier::NE_DEBUG_LINE_DRAW_ADD_LINE_PIXELS,&ld);

      }
         break;
   }
}
void MainScene::TapDragPinchInputDragContinue(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
   switch(_dragBehavior)
   {
      case DB_TRACK:
         Notifier::Instance().Notify(Notifier::NE_RESET_DRAW_CYCLE);
         _tapDragPinchInput->DrawDebug();
         break;
      case DB_SEEK:
         Notifier::Instance().Notify(Notifier::NE_RESET_DRAW_CYCLE);
         _tapDragPinchInput->DrawDebug();
         break;
      case DB_PATH:
      {

         LINE_PIXELS_DATA ld;
         _path.push_back(point1.pos);
         ld.start = _lastPoint;
         ld.end = point1.pos;
         _lastPoint = point1.pos;
         Notifier::Instance().Notify(Notifier::NE_DEBUG_LINE_DRAW_ADD_LINE_PIXELS,&ld);
      }
         break;
   }
}
void MainScene::TapDragPinchInputDragEnd(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
   switch(_dragBehavior)
   {
      case DB_TRACK:
         Notifier::Instance().Notify(Notifier::NE_RESET_DRAW_CYCLE);
         break;
      case DB_SEEK:
         Notifier::Instance().Notify(Notifier::NE_RESET_DRAW_CYCLE);
         break;
      case DB_PATH:
         break;
   }
}

void MainScene::SetZoom(float scale)
{
   Viewport::Instance().SetScale(scale);
}
