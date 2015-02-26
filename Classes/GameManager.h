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
	char *_dir;
public:
	static GameManager* Instance();
	void LateInit();

	float GetScaleX();
	float GetScaleY();
	float GetScaleFactor();

	void SetUpScaleFactors();

	void GetFileName(char *array, const int len, const char *name);

};

#define GETSCALEX ( GameManager::Instance()->GetScaleX() )
#define GETSCALEY ( GameManager::Instance()->GetScaleY() )
#define GETSCALEFAC ( GameManager::Instance()->GetScaleFactor() )

#define SCALEX(p) ( (p) * GETSCALEX)
#define SCALEY(p) ( (p) * GETSCALEY)

#define SCALEPOS(x,y) ( Vec2(  GETSCALEX * (x) * GETSCALEFAC, GETSCALEY * (y) * GETSCALEFAC ) )

#define SCALEFONT(p) ( (p) * SCALEY * GETSCALEFAC )

#define GETFILENAME(a,l,n) \
	(GameManager::Instance()->GetFileName(a,l,n))

#define SCALENODE_XY(n) \
	n->setScaleX(GETSCALEX); \
	n->setScaleY(GETSCALEY)

#define SCALENODE_Y(n) \
	n->setScaleY(GETSCALEY)

#endif /* __GAME_MANAGER_H__ */
