#ifndef HEART_H_
#define HEART_H_

#include "Symbol.h"

class Heart: public Symbol
{
public:
   Heart();
   virtual ~Heart();
   void drawFillAtOrigin();
   void drawOutlineAtOrigin();
   void drawLineArc(float cenX, float cenY, float radius, float startAngle, float arcAngle);
};

#endif /*HEART_H_*/