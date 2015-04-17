#ifndef __TAP_DRAG_PINCH_INPUT_H__
#define __TAP_DRAG_PINCH_INPUT_H__
#define COCOS2D_DEBUG 1

#include "CommonSTL.h"
#include "CommonProject.h"
#include "Stopwatch.h"

class TapDragPinchInput;

/* This class is an interface for 
 * a delegate for the TapDragPinchInput.
 * Any class (usually a scene) that wishes to 
 * receive the input from the layer derives
 * from this class and implements the virtual
 * methods in it.
 */

class TapDragPinchInputTarget
{
public:
   typedef struct
   {
      Point pos;
      int ID;
      double timestamp;
   } TOUCH_DATA_T;

private:
   /* These are used so that derived classes don't have to store the 
    * points from when a pinch began.
    */
   TOUCH_DATA_T _pinchPoint0;
   TOUCH_DATA_T _pinchPoint1;

   inline void SetPinchPoint0(const TOUCH_DATA_T& point0) { _pinchPoint0 = point0; }
   inline void SetPinchPoint1(const TOUCH_DATA_T& point1) { _pinchPoint1 = point1; }
   
   friend class TapDragPinchInput;

protected:
   /* These points are stored automatically at the start of a pinch. 
    * This is because the pinch points can move over the course of the
    * pinch and this may or may not be signficant to the consumer
    * of the points.
    */
   inline const TOUCH_DATA_T& GetPinchPoint0() { return _pinchPoint0; }
   inline const TOUCH_DATA_T& GetPinchPoint1() { return _pinchPoint1; }
public:
   virtual void TapDragPinchInputTap(const TOUCH_DATA_T& point) = 0;
   virtual void TapDragPinchInputLongTap(const TOUCH_DATA_T& point) = 0;
   virtual void TapDragPinchInputPinchBegin(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1) = 0;
   virtual void TapDragPinchInputPinchContinue(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1) = 0;
   virtual void TapDragPinchInputPinchEnd(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1) = 0;
   virtual void TapDragPinchInputDragBegin(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1) = 0;
   virtual void TapDragPinchInputDragContinue(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1) = 0;
   virtual void TapDragPinchInputDragEnd(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1) = 0;
};

/*
 This class operates as a state machine.  A decision
 is made based on the order fingers go down, how far
 they have moved since they went down, etc., to decide
 if the input is a drag, a tap, or a pinch.  A tap
 is registered when the finger moves up.  A long
 tap is the same, with the amount of time since
 the "down" as the discriminator.
 
 
 The class sends out notifications via the Notifier.
 It also receives notifications to enable/disable input.
 
 */
class TapDragPinchInput : public Node
{
   
private:
   typedef TapDragPinchInputTarget::TOUCH_DATA_T TOUCH_DATA_T;
   //  The states it can be in.
   typedef enum
   {
      DPT_IDLE = 0,
      DPT_FINGER_DOWN,
      DPT_DRAG,
      DPT_PINCH,
   } DPT_STATE_T;
   
   
   DPT_STATE_T _state;
   TOUCH_DATA_T _points[2];
   StopWatch _stopWatch;
   bool _enabled;
   
   bool init(TapDragPinchInputTarget* target);
   TapDragPinchInput();
   void StoreTouchData(Touch* touch, TOUCH_DATA_T* touchData);
   TapDragPinchInputTarget* _target;
    
    EventListenerTouchOneByOne *_touchListener;
   
public:
   virtual ~TapDragPinchInput();
   
   // The class registers/unregisters on entry
   // or exit of the layer.
   virtual void onEnterTransitionDidFinish();
   virtual void onExitTransitionDidStart();
   // CCTargetedTouchDelegate virtual methods.
   virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
   virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
   virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
   virtual void onTouchCancelled(Touch *pTouch, Event *pEvent);
   
   // This class will autorelease automatically if added to a layer,
   // scene, etc.
   static TapDragPinchInput* create(TapDragPinchInputTarget* target);
};

#endif /* __TAP_DRAG_PINCH_INPUT_H__ */
