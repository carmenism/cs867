#include "DataSet.h"
#include "Chart.h"
#include "RandomWalk.h"

DataSet::DataSet() {
    numberCharts = 15;
    numberTimeSteps = 500;

    walk = new RandomWalk();

    allValues = new std::vector<std::vector<float> *>();
}

DataSet::~DataSet() {
    clearValues();

    delete walk;
    delete allValues;
}

int DataSet::getNumberCharts() {
    return allValues->size();
}

float DataSet::getValue(int chartIndex, int timeIndex) {
    return allValues->at(chartIndex)->at(timeIndex);
}

std::vector<float> *DataSet::getValues(int chartIndex) {
    return allValues->at(chartIndex);
}

float DataSet::getDifferenceForChartBetweenTimes(int chartIndex, int startTime, int endTime) {
    std::vector<float> *chart = allValues->at(chartIndex);

    float valueStart = chart->at(startTime);
    float valueEnd = chart->at(endTime);

    return (valueEnd - valueStart);
}

void DataSet::updateValues() {
    clearValues();    

    globalMinX = 0;
    globalMaxX = numberTimeSteps - 1;

    globalMinY =  10000;
    globalMaxY = -10000;

    for (int i = 0; i < numberCharts; i++) {
        std::vector<float> *values = walk->generate(numberTimeSteps, 50);
        allValues->push_back(values);

        for (int time = 0; time < values->size(); time++) {
            float v = values->at(time);

            if (globalMinY > v) {
                globalMinY = v;
            }

            if (globalMaxY < v) {
                globalMaxY = v;
            }
        }
    }
}

void DataSet::clearValues() {
    while (!allValues->empty()) {
        std::vector<float> *values = allValues->back();
        delete values;
        allValues->pop_back();
    }
}