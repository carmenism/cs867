#ifndef CHARTSET_H_
#define CHARTSET_H_

class Chart;
class HorizonGraph;
class LineChart;
class DataSet;

class ChartSet {
public:
    ChartSet(DataSet *dataSet);
    ~ChartSet();

    void updateValues();
    void setCurrentChart(Chart *c) { currentChart = c; }

    void draw();
private:
    int numberCharts;
    int chartWidth, chartHeight;

    Chart *currentChart;

    DataSet *dataSet;
};

#endif /* CHARTSET_H_ */