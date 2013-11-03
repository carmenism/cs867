#include "ChartSet.h"
#include "DataSet.h"
#include "Chart.h"
#include "HorizonGraph.h"
#include "LineChart.h"

ChartSet::ChartSet(DataSet *dataSet) {
    this->dataSet = dataSet;

    chartWidth = 500;
    chartHeight = 25;

    hg = new HorizonGraph();
    line = new LineChart();

    currentChart = hg;
}

ChartSet::~ChartSet() {
    delete hg;
    delete line;
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