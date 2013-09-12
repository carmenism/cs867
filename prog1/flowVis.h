class Color;

#include <vector>

class flowVis
{
public:
	flowVis();
    ~flowVis();
	void load();
	void traceN(int n);
	bool getVec(float x, float y, float &dx, float &dy);
    void drawBackground(float orthoRight, float orthoTop);
    void drawLegend();
 
    void useRainbow();
    void useBlueToYellow();
    void useBlackToWhite();
    void useWhiteArrow();
    void useBlackArrow();
    void useRedArrow();
private:
	int nRows, nCols;
	float **u;
	float **v;
    
    float age;
    float number;

    float minSpeed, maxSpeed, interval;

    std::vector<Color *> * colors;
    
    std::vector<Color *> * rainbow;    
    std::vector<Color *> * blueToYellow;
    std::vector<Color *> * blackToWhite;

    Color *arrowColor;
    Color *white;
    Color *black;
    Color *red;

    void findMinMaxSpeeds();
    void drawTriangle(float xp, float yp, float dx, float dy);
    void drawBoundingBox(float x, float y, float width, float height);
    void drawLegendBox(float x, float y, float width, float height, Color *c);
    void drawLegendLabel(float x, float y, float speed, float fontHeight);
};