#include "TapDragPinchInput.h"
#include "Notifier.h"

const static float DRAG_RADIUS = 2.0f;
const static float DRAG_RADIUS_SQ = (DRAG_RADIUS*DRAG_RADIUS);


void TapDragPinchInput::StoreTouchData(Touch* touch, TOUCH_DATA_T* touchData)
{
   touchData->pos = touch->getLocation(); // openGL coordinates
   touchData->ID = touch->getID();
   touchData->timestamp = _stopWatch.GetSeconds();
}


bool TapDragPinchInput::init(TapDragPinchInputTarget* target)
{
   assert(target != NULL);
   _enabled = true;
   _state = DPT_IDLE;
   _target = target;
   return true;
}

TapDragPinchInput::TapDragPinchInput()
{
}

TapDragPinchInput::~TapDragPinchInput()
{
   
}


void TapDragPinchInput::DrawDebug()
{
   LINE_PIXELS_DATA ld;
   
   ld.color = ccc4f(0.9f, 0.2f, 0.1f, 0.90f);
   ld.markerRadius = 25;
   
   switch(_state)
   {
      case DPT_IDLE:
         // Nothing to draw.
         break;
      case DPT_FINGER_DOWN:
         // Draw two lines as a cross where the finger is down.
         ld.start = Vec2(_points[0].pos.x,_points[0].pos.y);
         ld.end = ld.start;
         Notifier::Instance().Notify(Notifier::NE_DEBUG_LINE_DRAW_ADD_LINE_PIXELS, &ld);
         break;
      case DPT_DRAG:
         ld.start = Vec2(_points[1].pos.x,_points[1].pos.y);
         ld.end = ld.start;
         Notifier::Instance().Notify(Notifier::NE_DEBUG_LINE_DRAW_ADD_LINE_PIXELS, &ld);
         break;
      case DPT_PINCH:
         ld.start = Vec2(_points[0].pos.x,_points[0].pos.y);
         ld.end = ld.start;
         Notifier::Instance().Notify(Notifier::NE_DEBUG_LINE_DRAW_ADD_LINE_PIXELS, &ld);
         
         ld.start = Vec2(_points[1].pos.x,_points[1].pos.y);
         ld.end = ld.start;
         Notifier::Instance().Notify(Notifier::NE_DEBUG_LINE_DRAW_ADD_LINE_PIXELS, &ld);
         
         ld.markerRadius = 0.0;
         ld.start = Vec2(_points[0].pos.x,_points[0].pos.y);
         ld.end = Vec2(_points[1].pos.x,_points[1].pos.y);
         Notifier::Instance().Notify(Notifier::NE_DEBUG_LINE_DRAW_ADD_LINE_PIXELS, &ld);
         break;
      default:
         assert(false);
         break;
   }
}

// The class registers/unregisters on entry
// or exit of the layer.  This
void TapDragPinchInput::onEnterTransitionDidFinish()
{
   CCNode::onEnterTransitionDidFinish();
   init(_target);
   Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority((EventListenerTouchAllAtOnce*)this, 0);
}

void TapDragPinchInput::onExitTransitionDidStart()
{
   CCNode::onExitTransitionDidStart();
   Director::getInstance()->getEventDispatcher()->removeEventListener((EventListenerTouchAllAtOnce*)this);
}


bool TapDragPinchInput::onTouchBegan(Touch *touch, Event *pEvent)
{
   switch(_state)
   {
      case DPT_FINGER_DOWN:
         // If you are already in finger down and another finger comes,
         // you must be trying a pinch.
         StoreTouchData(touch, &_points[1]);
         _state = DPT_PINCH;
         _target->SetPinchPoint0(_points[0]);
         _target->SetPinchPoint1(_points[1]);
         _target->TapDragPinchInputPinchBegin(_points[0], _points[1]);
         break;
      case DPT_IDLE:
         // Reset the stopwtach for a first point.
         _stopWatch.Start();
         StoreTouchData(touch, &_points[0]);
         _state = DPT_FINGER_DOWN;
         break;
      case DPT_DRAG:
         return false;
         break;
      case DPT_PINCH:
         return false;
         break;
   }
   return true;
}

void TapDragPinchInput::onTouchMoved(Touch *touch, Event *pEvent)
{
   switch(_state)
   {
      case DPT_DRAG:
         if(_points[1].ID == touch->getID())
         {
            StoreTouchData(touch, &_points[1]);
            _target->TapDragPinchInputDragContinue(_points[0], _points[1]);
         }
         break;
      case DPT_FINGER_DOWN:
         if(touch->getID()== _points[0].ID)
         {
            float distSq = _points[0].pos.getDistanceSq(touch->getLocation());
            if(distSq >= DRAG_RADIUS_SQ)
            {  // Starting a drag.
               StoreTouchData(touch, &_points[1]);
               _target->TapDragPinchInputDragBegin(_points[0], _points[1]);
               _state = DPT_DRAG;
            }
         }
         else
         {  // Should not happen.
            _state = DPT_IDLE;
         }
         break;
      case DPT_IDLE:
         // You can get here if you were doing a pinch and lifted
         // only one finger.
         break;
      case DPT_PINCH:
         if(touch->getID() == _points[0].ID)
         {  // Point 0 moved.
            StoreTouchData(touch, &_points[0]);
         }
         if(touch->getID() == _points[1].ID)
         {  // Point 1 moved.
            StoreTouchData(touch, &_points[1]);
         }
         _target->TapDragPinchInputPinchContinue(_points[0], _points[1]);
         break;
   }
   
}

void TapDragPinchInput::onTouchEnded(Touch *touch, Event *pEvent)
{
   switch(_state)
   {
      case DPT_DRAG:
         if(_points[1].ID == touch->getID())
         {
            StoreTouchData(touch, &_points[1]);
            _target->TapDragPinchInputDragEnd(_points[0], _points[1]);
            _state = DPT_IDLE;
         }
         break;
      case DPT_FINGER_DOWN:
         _stopWatch.Stop();
         StoreTouchData(touch, &_points[0]);
         if(_stopWatch.GetSeconds() > 0.5)
         {
            _target->TapDragPinchInputLongTap(_points[0]);
         }
         else
         {
            _target->TapDragPinchInputTap(_points[0]);
         }
         _state = DPT_IDLE;
         break;
      case DPT_IDLE:
         break;
      case DPT_PINCH:
         if(touch->getID() == _points[0].ID)
         {  // Point 0 moved.
            StoreTouchData(touch, &_points[0]);
         }
         if(touch->getID() == _points[1].ID)
         {  // Point 1 moved.
            StoreTouchData(touch, &_points[1]);
         }
         _target->TapDragPinchInputPinchEnd(_points[0], _points[1]);
         _state = DPT_IDLE;
         break;
   }
}

void TapDragPinchInput::onTouchCancelled(Touch *touch, Event *pEvent)
{
   onTouchEnded(touch, pEvent);
}


TapDragPinchInput* TapDragPinchInput::create(TapDragPinchInputTarget* target)
{
   TapDragPinchInput *pRet = new (std::nothrow) TapDragPinchInput();
   if (pRet && pRet->init(target))
   {
      pRet->autorelease();
      return pRet;
   }
   else
   {
      CC_SAFE_DELETE(pRet);
   }
   return pRet;
}

