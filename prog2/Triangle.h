#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Symbol.h"

class Triangle: public Symbol
{
public:
   Triangle();
   virtual ~Triangle();
   void drawFillAtOrigin();
   void drawOutlineAtOrigin();
private:
   void drawAtOrigin();
};

#endif 