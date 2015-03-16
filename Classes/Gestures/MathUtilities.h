#ifndef __MATH_UTILITIES_H__
#define __MATH_UTILITIES_H__

#include "CommonSTL.h"
#include "CommonProject.h"

class MathUtilities
{
public:
   static float LinearTween(float t, float start, float end)
   {
      assert(t>= 0.0);
      assert(t<= 1.0);
      return start + (t)*(end-start);
   }
   
   static float QuadraticEaseIn(float t, float start, float end)
   {
      assert(t>= 0.0);
      assert(t<= 1.0);
      return LinearTween(t*t, start, end);
   }
   
   static float QuadraticEaseInOut(float t, float start, float end)
   {
      assert(t>= 0.0);
      assert(t<= 1.0);
      float middle = (start + end)/2;
      t *= 2;
      if(t <= 1)
      {
         return LinearTween(t*t, start, middle);
      }
      else
      {
         t -= 1;
         return LinearTween(t*t, middle, end);
      }
   }
   
   static float QuadraticEaseInOut(float t, float tEdge, float low, float high)
   {
      assert(t>= 0.0);
      assert(t<= 1.0);
      if(t < tEdge)
      {
         return low + (t/tEdge)*(t/tEdge)*(high-low);
      }
      else if (t >= tEdge && t <= (1.0-tEdge))
      {
         return high;
      }
      else // t > tEdge
      {
         t = t - (1.0-tEdge);
         return low + (t/tEdge)*(t/tEdge)*(high-low);
      }
   }
   
   // Start with a constant acceleration.
   // Vf-Vo = a(Tf-To) = a.deltaT
   // ==> Vf = Vo + a.deltaT or
   // ==> a = (Vf-Vo)/deltaT.
   static inline float CalculateAcceleration(float deltaT, float Vo, float Vf)
   {
      float accel = (Vf-Vo)/deltaT;
      return accel;
   }
   
   // Takes an angle greater than +/- M_PI and converts it back
   // to +/- M_PI.  Useful in Box2D where angles continuously
   // increase/decrease.
   static inline float AdjustAngle(float angleRads)
   {
      if(angleRads > M_PI)
      {
         while(angleRads > M_PI)
         {
            angleRads -= 2*M_PI;
         }
      }
      else if(angleRads < -M_PI)
      {
         while(angleRads < -M_PI)
         {
            angleRads += 2*M_PI;
         }
      }
      return angleRads;
   }
   
   // Indicate which quadrant a point is in.
   // 0 ==> 0 < x < PI/2
   // 1 ==> PI/2 < x < PI
   // 2 ==> PI < x < 3*PI/2
   // 3 ==> 3*PI/2 < x < 2*PI
   //
   // The point 0,0 maps into the first qudrant for simplicity.
   static inline int32 VecToQuadrant(const Vec2& pt)
   {
      if(pt.x >= 0 && pt.y >= 0)
      {
         return 0;
      }
      if(pt.x < 0 && pt.y >= 0)
      {
         return 1;
      }
      if(pt.x < 0 && pt.y < 0)
      {
         return 2;
      }
      return 3;
   }

   template <typename Number>
   static inline bool IsNearZero(Number value)
   {
      if(value < 0)
         value = -value;
      if(value >= 0 && value <= numeric_limits<Number>::epsilon())
         return true;
      return false;
   }
   
   template<typename Number>
   static inline Number NormalizedAngle(Number angleRads)
   {
      Number angle = angleRads / M_PI;
      
      while(angle > 2)
         angle -= 2;
      while(angle < -2)
         angle += 2;
      if(angle < -1)
      {
         angle += 2;
      }
      else if(angle > 1)
      {
         angle = -2 + angle;
      }
      return angle;
   }

};

#endif /* __MATH_UTILITIES_H__ */
