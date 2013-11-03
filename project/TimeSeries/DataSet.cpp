#include "DataSet.h"
#include "Chart.h"
#include "RandomWalk.h"

DataSet::DataSet() {
    numberCharts = 15;
    numberTimeSteps = 1000;

    walk = new RandomWalk();

    allValues = new std::vector<std::vector<float> *>();
}

DataSet::~DataSet() {
    clearValues();

    delete walk;
    delete allValues;
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

void DataSet::draw(Chart *chartStyle) {
    chartStyle->setGlobalMinX(globalMinX);
    chartStyle->setGlobalMaxX(globalMaxX);
    chartStyle->setGlobalMinY(globalMinY);
    chartStyle->setGlobalMaxY(globalMaxY);

    for (int i = 0; i < numberCharts; i++) {
        chartStyle->draw(allValues->at(i), 100, 100 + 35 * i);
    }  
}