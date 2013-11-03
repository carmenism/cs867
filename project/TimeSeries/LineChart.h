#ifndef LINECHART_H_
#define LINECHART_H_

#include "Chart.h"
#include <vector>

class Color;

class LineChart : public Chart {
public:
    LineChart();
    ~LineChart();

    void setColor(Color *c) { color = c; }
    Color *getColor() { return color; }

    virtual void drawAtOrigin(std::vector<float> *values);
private:
    Color *color;
};

#endif /* LINECHART_H_ */