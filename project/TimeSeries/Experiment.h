#ifndef EXPERIMENT_H_
#define EXPERIMENT_H_

class DataSet;
class ChartSet;
class Task;
class DiscriminationTask;
class MaximumTask;
class SlopeTask;
class HorizonGraph;
class LineChart;
class Chart;

#include <vector>

class Experiment {
public:
    Experiment();
    ~Experiment();

    void draw();
    void startTrial();
    bool endTrial();
private:
    int nTrials;
    int nTasks;
    int nTypes;

    int trialNumber;
    int totalTrials;

    DataSet *dataSet;
    ChartSet *chartSet;

    std::vector<Task *> *tasks;

    MaximumTask *taskMax;
    DiscriminationTask *taskDisc;
    SlopeTask *taskSlope;

    std::vector<Chart *> *chartTypes;

    HorizonGraph *hg;
    LineChart *line;
};

#endif /* EXPERIMENT_H_ */