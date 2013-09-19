#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Symbol.h"

class Circle: public Symbol
{
public:
   Circle();
   virtual ~Circle();
   void drawFillAtOrigin();
   void drawOutlineAtOrigin();
private:
   void drawAtOrigin();
};

#endif /*CIRCLE_H_*/