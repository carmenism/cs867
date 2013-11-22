#include "Experiment.h"
#include "DataSet.h"
#include "ChartSet.h"
#include "MaximumTask.h"
#include "DiscriminationTask.h"
#include "SlopeTask.h"
#include "HorizonGraph.h"
#include "StackedChart.h"
#include "LineChart.h"
#include "Stopwatch.h"
#include "PickColor.h"

Experiment::Experiment(std::string participant) {
    this->participant = participant;
    //std::string title = participant + "-outputResults.csv";
    outFile.open("outputResults.csv");

    stopwatch = new Stopwatch();

    dataSet = new DataSet();
    chartSet = new ChartSet(dataSet);

    taskMax = new MaximumTask(dataSet);
    taskDisc = new DiscriminationTask(dataSet);
    taskSlope = new SlopeTask(dataSet);

    tasks = new std::vector<Task *>();
    //tasks->push_back(taskDisc);
    tasks->push_back(taskSlope);
    tasks->push_back(taskMax);

    stacked = new StackedChart();
    hg = new HorizonGraph();
    line = new LineChart();

    chartTypes = new std::vector<Chart *>();
    chartTypes->push_back(stacked);
    chartTypes->push_back(hg);
    chartTypes->push_back(line);

    nTrials = 10;
    nTasks = tasks->size();
    nTypes = chartTypes->size();

    totalTrials = nTrials * nTasks * nTypes;

    trialNumber = 0;
}

Experiment::~Experiment() {
    delete stopwatch;
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
    int taskIndex = getTaskIndex();
    int typeIndex = getTypeIndex();

    std::vector<TimeMark *> *timeMarks = tasks->at(taskIndex)->getTimeMarks();

    chartSet->setCurrentChart(chartTypes->at(typeIndex));
    chartSet->draw(timeMarks);

    tasks->at(taskIndex)->drawInstructions(25, 650);
}

void Experiment::drawToPick(std::vector<PickColor *> *pickColors) {
    int typeIndex = getTypeIndex();

    chartSet->setCurrentChart(chartTypes->at(typeIndex));
    chartSet->drawToPick(pickColors);
}

void Experiment::startTrial() {   
    chartSet->updateValues();
    int taskIndex = getTaskIndex();
    tasks->at(taskIndex)->configure();
    stopwatch->start();
}

bool Experiment::endTrial(int responseIndex) {
    double time = stopwatch->stop();
    bool answerCorrect = tasks->at(getTaskIndex())->responseCorrect(responseIndex);

    this->writeRecord(answerCorrect, time);

    trialNumber++;

    if (trialNumber == totalTrials) {
        outFile.close();

        return false;
    }

    return true;
}

int Experiment::getTaskIndex() {
    return trialNumber / (nTrials * nTypes);
}

int Experiment::getTypeIndex() {
    return (trialNumber / nTrials) % nTypes;
}

void Experiment::writeRecord(bool correctAnswer, double time) {
    outFile << participant << ",";    
    outFile << tasks->at(getTaskIndex())->getLabel() << ",";
    outFile << chartTypes->at(getTypeIndex())->getLabel() << ",";

    if (correctAnswer) {
        outFile << "Correct,";
    } else {
        outFile << "Incorrect,";
    }

    outFile << time << "\n";
}

int Experiment::getNumberCharts() {
    return dataSet->getNumberCharts();
}