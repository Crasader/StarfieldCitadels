#ifndef __STOP_WATCH_H__
#define __STOP_WATCH_H__

#include "cocos2d.h"
USING_NS_CC;

class StopWatch : public Node
{
private:
	float _elapsedSeconds;
public:
   void Start();
   void UpdateTimer(float dt);
   void Stop();
   void Reset();
   void Continue();
   float GetSeconds();
};


#endif /* __STOP_WATCH_H__ */
