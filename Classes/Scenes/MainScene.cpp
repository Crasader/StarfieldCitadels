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
    //baseLayer->setAnchorPoint(Vec2(0.5, 0.5));
    
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
    //_map->setAnchorPoint(Vec2(0.5, 0.5));
    _map->setPosition(0, 0);
    baseLayer->addChild(_map, 0);
    CCLOG("Map Size: %f, %f", _map->getContentSize().width, _map->getContentSize().height);
    drawBoundingBox(_map, Color4F(1, 1, 1, 1));
    
    Vec3 eye = Vec3(2048,1024,3000);
    _camera = Camera::createPerspective(60, visibleSize.width/visibleSize.height, 1, 4000);
    _camera->setPosition3D(eye);
    _camera->lookAt(Vec3(2048,1024,0), Vec3(0,1,0));
    _camera->setCameraFlag(CameraFlag::USER1);
    baseLayer->addChild(_camera);
    
    _map->setCameraMask((unsigned short)CameraFlag::USER1);

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
    
    // 1. Convert to world coordinate space
    // 2. Ray trace
    // 3. Update look at and camera position
    
    // Octree
    auto baseLayer = this->getChildByName("BaseLayer");
    auto worldPinchCoords = convertToWorldCoords(centerNew);
    //auto worldMapCoords = baseLayer->convertToWorldSpaceAR(_map->getPosition());
    //auto worldPinchCoords = Director::getInstance()->convertToGL(centerNew);
    auto nodeSpace = _map->convertToNodeSpace(centerNew);
    
    //CCLOG("World Coords of Map: %f, %f", worldMapCoords.x, worldMapCoords.y);
    //CCLOG("Nodespace Coords of Map: %f, %f", nodeSpace.x, nodeSpace.y);
    // Bottom Left corner of the map in world coordinates
    //auto mapSize = _map->getContentSize();
    //worldMapCoords-mapSize.width/2;
    //auto localCoords = _map->convertToNodeSpace(centerNew);
    auto localCoords = convertToLocalCoords(centerNew, _map);
    //CCLOG("Local Coords: %f, %f", localCoords.x, localCoords.y);
    
    Vec3 lookDir = _camera->getPosition3D() - worldPinchCoords;
    Vec3 cameraPos = _camera->getPosition3D();
    if(lookDir.length() >= 50)
    {
        cameraPos -= lookDir.getNormalized()*20;
        _camera->setPosition3D(cameraPos);
    }
    
    _coords->setPosition(centerNew);
    char tmp[100];
    sprintf(tmp,"%f,%f\n%f, %f, %f", worldPinchCoords.x, worldPinchCoords.y, lookDir.getNormalized().x, lookDir.getNormalized().y, lookDir.getNormalized().z);
    _coords->setString(tmp);
}

Vec2 MainScene::convertToLocalCoords(Vec2 pos, Node* target)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto scaleX = pos.x/visibleSize.width;
    auto scaleY = pos.y/visibleSize.height;
    
    auto targetSize = target->getContentSize();
    float newPosX = targetSize.width*scaleX;
    float newPosY = targetSize.height*scaleY;
    
    return Vec2(newPosX, newPosY);
}

// Handler for Tap/Drag/Pinch Events
void MainScene::TapDragPinchInputTap(const TOUCH_DATA_T& point)
{
    CCLOG("Touch");
    //auto localCoords = _map->convertToNodeSpace(point.pos);
    //auto worldCoords = convertToWorldCoords(point.pos);
    auto worldCoords = transformPoint(point.pos);
    _coords->setPosition(point.pos);
    char tmp[100];
    sprintf(tmp,"%f,%f", worldCoords.x, worldCoords.y);
    _coords->setString(tmp);
}

void MainScene::TapDragPinchInputLongTap(const TOUCH_DATA_T& point)
{
    CCLOG("Long Tap");
}

void MainScene::TapDragPinchInputPinchBegin(const TOUCH_DATA_T& point0, const TOUCH_DATA_T& point1)
{
    CCLOG("Pinch Begin");
    auto midp = point0.pos.getMidpoint(point1.pos);
    //auto localCoords = _map->convertToNodeSpace(midp);
    auto localCoords = convertToLocalCoords(midp, _map);
    CCLOG("Local Coords: %f, %f", localCoords.x, localCoords.y);
    Notifier::Instance().Notify(Notifier::NE_RESET_DRAW_CYCLE);
    _viewportCenterOrg = Viewport::Instance().GetCenterMeters();
    _viewportScaleOrg = Viewport::Instance().GetScale();
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
    auto currentPos = _camera->getPosition();
    _camera->setPosition(currentPos+delta);
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
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    double x = 2.0 * pos.x/visibleSize.width - 1;
    double y = 2.0 * pos.y/visibleSize.height - 1;
    
    auto viewProjMatIn = _camera->getViewProjectionMatrix();
    viewProjMatIn.inverse();
    
    auto point3D = Vec3(x, y, 0);
    return viewProjMatIn*point3D;
}

Point MainScene::transformPoint(Point point)
{
    
    Vec4 start = unProjectPoint(Vec3(point.x, point.y, 0));
    Vec4 end = unProjectPoint(Vec3(point.x, point.y, -1));
    
    Vec4 rayDir = end - start;
    rayDir.normalize();
    Vec4 normal = Vec4(0, 0, 1, 0);
    
    float rayDirDotNorm = rayDir.dot(normal);
    float P0DotNorm = start.dot(normal);
    
    float t = 0;
    
    if (rayDirDotNorm != 0) {
        t = -P0DotNorm / rayDirDotNorm;
    }
    
    Vec4 result = (rayDir * t) + start;
    
    return Point(result.x, result.y);
    
}

Vec4 MainScene::unProjectPoint(Vec3 point)
{
    Director *d = Director::getInstance();
    Size screenSize = d->getVisibleSize();
    Rect viewPort = Rect(0, 0, screenSize.width, screenSize.height);
    
    Mat4 projectionMatrix = d->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    Mat4 modelView = _modelViewTransform;
    Mat4 finalMatrix = projectionMatrix * _modelViewTransform;
    assert(finalMatrix.inverse());
    
    Vec4 in = Vec4(point.x, point.y, point.z, 1);
    in.x = (in.x - viewPort.origin.x) / viewPort.size.width;
    in.y = (in.y - viewPort.origin.y) / viewPort.size.height;
    
    in.x = in.x * 2 -1;
    in.y = in.y * 2 -1;
    in.z = in.z * 2 -1;
    
    Vec4 out = finalMatrix * in;
    assert(out.w != 0);
    
    out.x /= out.w;
    out.y /= out.w;
    out.z /= out.w;
    out.w /= out.w;
    
    return out;
    
}
