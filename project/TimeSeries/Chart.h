#ifndef CHART_H_
#define CHART_H_

class PickColor;
class Color;

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
    float getHeight() { return height; }

    void draw(std::vector<float> *values, float x, float y);
    virtual void drawAtOrigin(std::vector<float> *values) = 0;
    
    void drawLine(float x, float y, int time);

    void drawToPick(PickColor *pickColor, float x, float y);

    std::string getLabel() { return label; }

    void setPick(PickColor *pickColor);

    void setIndex(int i) { index = i; }

    float getSpacing() { return spacing; }
    virtual float calculateHeight(float fullHeight, int numberCharts);
protected:
    int index;
    float x, y;
    float globalMinX, globalMaxX;
    float globalMinY, globalMaxY;
    float width, height;
    float buttonOffsetX, buttonOffsetY;
    float buttonWidth, buttonHeight;
    float spacing;

    Color *buttonColor;

    std::string label;

    virtual float getXLocation(float value);
    virtual float getYLocation(float value);

    virtual void drawButton(float x, float y);

    virtual void drawWhiteBackground(float x, float y);
    virtual void drawBorder(float x, float y);
};

#endif /* CHART_H_ */