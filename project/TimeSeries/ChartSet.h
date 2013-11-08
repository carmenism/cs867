#ifndef CHARTSET_H_
#define CHARTSET_H_

class Chart;
class HorizonGraph;
class LineChart;
class DataSet;
class TimeMark;
class PickColor;

#include <vector>

class ChartSet {
public:
    ChartSet(DataSet *dataSet);
    ~ChartSet();

    int getX() { return x; }
    int getY() { return y; }

    int getChartYLocation(int chartIndex);

    void updateValues();
    void setCurrentChart(Chart *c) { currentChart = c; }

    void draw(std::vector<TimeMark *> *timeMarks);

    void drawToPick(std::vector<PickColor *> *pickColors);
private:
    int x, y;
    int numberCharts;
    int totalWidth, totalHeight;

    Chart *currentChart;

    DataSet *dataSet;
};

#endif /* CHARTSET_H_ */