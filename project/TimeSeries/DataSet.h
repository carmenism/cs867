#ifndef DATASET_H_
#define DATASET_H_

#include <vector>

class Chart;
class RandomWalk;

class DataSet {
public:
    DataSet();
    ~DataSet();

    void updateValues();

    void draw(Chart *chartStyle);

    //void draw();
    float getGlobalMinX() { return globalMinX; }
    float getGlobalMaxX() { return globalMaxX; }

    int getNumberCharts();
    float getValue(int chartIndex, int timeIndex);
    std::vector<float> *getValues(int chartIndex);
    float getDifferenceForChartBetweenTimes(int chartIndex, int startTime, int endTime);
private:
    int numberCharts;
    int chartWidth, chartHeight;
    int numberTimeSteps;
    float globalMinX, globalMaxX;
    float globalMinY, globalMaxY;

    RandomWalk *walk;

    //Chart *currentChart;
    //HorizonGraph *hg;
    //LineChart *line;

    std::vector<std::vector<float> *> *allValues;

    void clearValues();
};

#endif /* DATASET_H_ */