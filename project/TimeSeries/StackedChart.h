#ifndef STACKEDCHART_H_
#define STACKEDCHART_H_

#include "Chart.h"
#include <vector>

class Color;
class Textures;

class StackedChart : public Chart {
public:
    StackedChart();
    ~StackedChart();

    void setColor(Color *c) { color = c; }
    Color *getColor() { return color; }

    void drawTex(float *Xpts, float*Ypts, int n,int t);
    virtual void drawLine(float x, float y, int time, int chart);

    virtual void drawAtOrigin(std::vector<float> *values);
    virtual float calculateHeight(float fullHeight, int numberCharts);

    virtual void drawButton(float x, float y);
private:
    Textures *textures;
    Color *color;

    int hScale;

    virtual void drawWhiteBackground(float x, float y);
    virtual void drawBorder(float x, float y);
};

#endif /* STACKEDCHART_H_ */