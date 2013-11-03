#ifndef HORIZONGRAPH_H_
#define HORIZONGRAPH_H_

#include "Chart.h"
#include <vector>

class Color;

class HorizonGraph : public Chart {
public:
    HorizonGraph();
    ~HorizonGraph();

    virtual void drawAtOrigin(std::vector<float> *values);
private:
    Color *colorPos;
    Color *colorNeg;

    int numberBands;
    float bandSize;
    float middle;
    
    void drawColor(std::vector<float> *values, Color *color, bool fillUnderLine, bool flip);
};

#endif /* HORIZONGRAPH_H_ */