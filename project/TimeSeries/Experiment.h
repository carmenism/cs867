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
class StackedChart;
class Chart;
class Stopwatch;
class PickColor;

#include <vector>
#include <fstream>
#include <string>

class Experiment {
public:
    Experiment(std::string participant);
    ~Experiment();

    void draw();
    void drawToPick(std::vector<PickColor *> *pickColors);
    void startTrial();
    bool endTrial(int responseIndex);

    int getNumberCharts();
private:
    std::string participant;
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
    StackedChart *stacked;

    int getTaskIndex();
    int getTypeIndex();
    void writeRecord(bool correctAnswer, double time);
};

#endif /* EXPERIMENT_H_ */