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
    currentChart->setGlobalMinX(dataSet->getGlobalMinX());
    currentChart->setGlobalMaxX(dataSet->getGlobalMaxX());
    currentChart->setGlobalMinY(dataSet->getGlobalMinY());
    currentChart->setGlobalMaxY(dataSet->getGlobalMaxY());

    for (int i = 0; i < dataSet->getNumberCharts(); i++) {
        currentChart->draw(dataSet->getValues(i), 100, 100 + 35 * i);
    }
}

void ChartSet::updateValues() {
    dataSet->updateValues();
}