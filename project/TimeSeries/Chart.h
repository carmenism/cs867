#ifndef CHART_H_
#define CHART_H_

#include <vector>
#include <string>

class Chart {
public:
    Chart(std::string label);
    ~Chart();

    void setGlobalMinX(float mX) { globalMinX = mX; }
    void setGlobalMaxX(float mX) { globalMaxX = mX; } 

    void setGlobalMinY(float mY) { globalMinY = mY; }
    void setGlobalMaxY(float mY) { globalMaxY = mY; }

    void setWidth(float w) { width = w; }
    void setHeight(float h) { height = h; }

    void draw(std::vector<float> *values, float x, float y);
    virtual void drawAtOrigin(std::vector<float> *values) = 0;
    
    void drawLine(float x, float y, int time);

    std::string getLabel() { return label; }
protected:
    float x, y;
    float globalMinX, globalMaxX;
    float globalMinY, globalMaxY;
    float width, height;

    std::string label;

    virtual float getXLocation(float value);
    virtual float getYLocation(float value);
};

#endif /* CHART_H_ */