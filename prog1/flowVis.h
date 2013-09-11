class Color;

class flowVis
{
public:
	flowVis();
	void load();
	void traceN(int n);
	bool getVec(float x, float y, float &dx, float &dy);
    void drawBackground(float orthoRight, float orthoTop);
private:
	int nRows, nCols;
	float **u;
	float **v;
    
    float age;
    float number;

    void drawTriangle(float xp, float yp, float dx, float dy);

    float minSpeed, maxSpeed;

    void findMinMaxSpeeds();
};