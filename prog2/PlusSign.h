#ifndef PLUSSIGN_H_
#define PLUSSIGN_H_

#include "Symbol.h"

class PlusSign: public Symbol
{
public:
   PlusSign();
   virtual ~PlusSign();
   void drawFillAtOrigin();
   void drawOutlineAtOrigin();
};

#endif /*PLUSSIGN_H_*/