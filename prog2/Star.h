#ifndef STAR_H_
#define STAR_H_

#include "Symbol.h"

class Star: public Symbol
{
public:
   Star();
   virtual ~Star();
   void drawFillAtOrigin();
   void drawOutlineAtOrigin();
};

#endif /*HEART_H_*/