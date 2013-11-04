#include "ChartSet.h"
#include "DataSet.h"
#include "Chart.h"
#include "HorizonGraph.h"
#include "LineChart.h"

ChartSet::ChartSet(DataSet *dataSet) {
    this->dataSet = dataSet;

    chartWidth = 500;
    chartHeight = 25;

    currentChart = 0;
}

ChartSet::~ChartSet() {
    delete dataSet;
}

void ChartSet::draw() {
    currentChart->setWidth(chartWidth);
    currentChart->setHeight(chartHeight);
    dataSet->draw(currentChart);     
}

void ChartSet::updateValues() {
    dataSet->updateValues();
}