class flowVis
{
public:
	flowVis();
	void load();
	void traceN(int n);
	bool getVec(float x, float y, float &dx, float &dy);
private:
	int nRows, nCols;
	float **u;
	float **v;
    
    float age;
    float number;
};