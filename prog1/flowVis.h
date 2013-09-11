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
private:
	int nRows, nCols;
	float **u;
	float **v;
    
    float age;
    float number;

    float minSpeed, maxSpeed, interval;

    std::vector<Color *> * colors;

    void findMinMaxSpeeds();
    void drawTriangle(float xp, float yp, float dx, float dy);
    void drawBoundingBox(float x, float y, float width, float height);
    void drawLegendBox(float x, float y, float width, float height, Color *c);
    void drawLegendLabel(float x, float y, float speed, float fontHeight);
};