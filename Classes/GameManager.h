/*
 * GameManager.h
 *
 *  Created on: Feb 25, 2015
 *      Author: ihall1
 */

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__
#define COCOS2D_DEBUG 1

class GameManager {
private:
	GameManager() {};
	GameManager(GameManager const&) {};
	GameManager& operator=(GameManager const&) {};
	~GameManager() {};

	static GameManager* _pInstance;

	float _scaleX;
	float _scaleY;
	float _scaleFactor;
public:
	static GameManager* getInstance();
	void LateInit();

	float GetScaleX();
	float GetScaleY();
	float GetScaleFactor();

	void SetUpScaleFactors();

};

#define GETSCALEX ( GameManager::getInstance()->GetScaleX() )
#define GETSCALEY ( GameManager::getInstance()->GetScaleY() )
#define GETSCALEFAC ( GameManager::getInstance()->GetScaleFactor() )

#define SCALEX(p) ( (p) * GETSCALEX)
#define SCALEY(p) ( (p) * GETSCALEY)

#define SCALEPOS(x,y) ( Vec2(  GETSCALEX * (x) * GETSCALEFAC, GETSCALEY * (y) * GETSCALEFAC ) )

#define SCALEFONT(p) ( (p) * SCALEY * GETSCALEFAC )

#define SCALENODE_XY(n) \
	n->setScaleX(GETSCALEX); \
	n->setScaleY(GETSCALEY)

#define SCALENODE_Y(n) \
	n->setScaleY(GETSCALEY)

#endif /* __GAME_MANAGER_H__ */
