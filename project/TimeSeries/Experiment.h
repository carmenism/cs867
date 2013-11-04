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
class Stopwatch;

#include <vector>
#include <fstream>

class Experiment {
public:
    Experiment();
    ~Experiment();

    void draw();
    void startTrial();
    bool endTrial(int responseIndex);
private:
    int nTrials;
    int nTasks;
    int nTypes;

    int trialNumber;
    int totalTrials;

    std::ofstream outFile;

    Stopwatch *stopwatch;

    DataSet *dataSet;
    ChartSet *chartSet;

    std::vector<Task *> *tasks;

    MaximumTask *taskMax;
    DiscriminationTask *taskDisc;
    SlopeTask *taskSlope;

    std::vector<Chart *> *chartTypes;

    HorizonGraph *hg;
    LineChart *line;

    int getTaskIndex();
    int getTypeIndex();
    void writeRecord(bool correctAnswer, double time);
};

#endif /* EXPERIMENT_H_ */