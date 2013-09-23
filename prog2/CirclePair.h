#ifndef CIRCLEPAIR_H_
#define CIRCLEPAIR_H_

#include "Symbol.h"

class CirclePair: public Symbol
{
public:
   CirclePair();
   virtual ~CirclePair();
   void drawFillAtOrigin();
   void drawOutlineAtOrigin();
private:
   void drawAtOrigin();
   void drawAtOrigin(float cenX, float cenY, float radius);
};

#endif /*CIRCLEPAIR_H_*/