#ifndef __COMMON_PROJECT_H__
#define __COMMON_PROJECT_H__

#include "cocos2d.h"
#include "cocos-ext.h"

//#define TICKS_PER_SECOND (30)
//#define SECONDS_PER_TICK (1.0/30)

// Some convenient shortcuts.

using namespace cocos2d;
using namespace cocos2d::extension;

typedef float Number;

typedef struct LINE_METERS_DATA
{
   Vec2 start;
   Vec2 end;
   Color4F color;
   float markerRadius;
   
   LINE_METERS_DATA()
   {
      color.r = 1.0f;
      color.g = 1.0f;
      color.b = 1.0f;
      color.a = 1.0f;
      markerRadius = 2.0f;
   }
   
} LINE_METERS_DATA_T;

typedef struct
{
   Vec2 start;
   Vec2 end;
   float length;
} LINE_METERS_WITH_LENGTH_DATA_T;

typedef struct LINE_PIXELS_DATA
{
   Point start;
   Point end;
   Color4F color;
   float markerRadius;
   float width;
   
   LINE_PIXELS_DATA()
   {
      color.r = 1.0f;
      color.g = 1.0f;
      color.b = 1.0f;
      color.a = 1.0f;
      markerRadius = 2.0f;
      width = 1.0f;
   }
} LINE_PIXELS_DATA_T;


#endif /* __COMMON_PROJECT_H__ */
