#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Symbol.h"

class Triangle: public Symbol
{
public:
   Triangle();
   virtual ~Triangle();
   void drawAtOrigin();
};

#endif 