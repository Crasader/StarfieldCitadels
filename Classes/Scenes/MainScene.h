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
#include "../Gestures/CommonProject.h"
#include "../Gestures/CommonSTL.h"
#include "../Gestures/TapDragPinchInput.h"
#include "../Gestures/Notifier.h"

class MainScene : public Scene, public Notified, public TapDragPinchInputTarget {
public:
	static Scene * createScene();

	// Override Scene::init() with our own init method for our main scene
	virtual bool init();

    virtual void update(float delta);

	// Create the create method for "MainScene" and make the call to the init method using this macro
	CREATE_FUNC(MainScene);

	virtual void onEnter();
	virtual void onExit();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();

	// Handler for Notifier Events
	virtual void Notify(Notifier::NOTIFIED_EVENT_TYPE_T eventType, const void* eventData);

	// Handler for Tap/Drag/Pinch Events
	typedef TapDragPinchInputTarget::TOUCH_DATA_T TOUCH_DATA_T;
	virtual void TapDragPinchInputTap(const TOUCH_DATA_T& point);
	virtual void TapDragPinchInputLongTap(const TOUCH_DATA_T& point);
	virtual void TapDragPinchInputPinchBegin(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1);
	virtual void TapDragPinchInputPinchContinue(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1);
	virtual void TapDragPinchInputPinchEnd(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1);
	virtual void TapDragPinchInputDragBegin(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1);
	virtual void TapDragPinchInputDragContinue(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1);
	virtual void TapDragPinchInputDragEnd(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1);
    
    void drawBoundingBox(Node* target, Color4F color);
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

    // Keep the last center point during a pinch.
	float _viewportScaleOrg;
	TapDragPinchInput* _tapDragPinchInput;

    Label *_coords;
    TMXTiledMap *_map;
    Rect _bounds;
    Point _pinchPoint;
private:
    void PinchViewport(const Point& p0Org,const Point& p1Org, const Point& p0,const Point& p1);
};

#endif /* __MAIN_SCENE_H__ */
