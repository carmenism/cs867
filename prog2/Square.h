#ifndef SQUARE_H_
#define SQUARE_H_

#include "Symbol.h"

class Square: public Symbol
{
public:
   Square();
   virtual ~Square();
   void drawAtOrigin();
};

#endif /*SQUARE_H_*/