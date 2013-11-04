#include "Experiment.h"
#include "DataSet.h"
#include "ChartSet.h"
#include "MaximumTask.h"
#include "DiscriminationTask.h"
#include "SlopeTask.h"
#include "HorizonGraph.h"
#include "LineChart.h"

Experiment::Experiment() {
    dataSet = new DataSet();
    chartSet = new ChartSet(dataSet);

    taskMax = new MaximumTask(dataSet);
    taskDisc = new DiscriminationTask(dataSet);
    taskSlope = new SlopeTask(dataSet);

    tasks = new std::vector<Task *>();
    tasks->push_back(taskMax);
    tasks->push_back(taskDisc);
    tasks->push_back(taskSlope);

    hg = new HorizonGraph();
    line = new LineChart();

    chartTypes = new std::vector<Chart *>();
    chartTypes->push_back(hg);
    chartTypes->push_back(line);

    nTrials = 30;
    nTasks = tasks->size();
    nTypes = chartTypes->size();

    totalTrials = nTrials * nTasks * nTypes;

    trialNumber = 0;
}

Experiment::~Experiment() {
    delete taskMax;
    delete taskSlope;
    delete taskDisc;
    delete dataSet;
    delete chartSet;
    
    tasks->clear();
    delete tasks;

    delete hg;
    delete line;
    
    chartTypes->clear();
    delete chartTypes;
}

void Experiment::draw() {
    int taskIndex = trialNumber / (nTrials * nTypes);
    int typeIndex = (trialNumber / nTrials) % nTypes;

    chartSet->setCurrentChart(chartTypes->at(typeIndex));
    chartSet->draw();
}

void Experiment::startTrial() {    
    chartSet->updateValues();
    int taskIndex = trialNumber / (nTrials * nTypes);
    tasks->at(taskIndex)->configure();
}

bool Experiment::endTrial() {
    trialNumber++;

    if (trialNumber == totalTrials) {
        return false;
    }

    return true;
}