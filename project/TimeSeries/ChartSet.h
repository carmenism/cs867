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

    void draw();
private:
    int numberCharts;
    int chartWidth, chartHeight;

    Chart *currentChart;
    HorizonGraph *hg;
    LineChart *line;

    DataSet *dataSet;
};

#endif /* CHARTSET_H_ */