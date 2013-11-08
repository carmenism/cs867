#include "ChartSet.h"
#include "DataSet.h"
#include "Chart.h"
#include "HorizonGraph.h"
#include "LineChart.h"
#include "TimeMark.h"
#include "PickColor.h"

ChartSet::ChartSet(DataSet *dataSet) {
    this->dataSet = dataSet;

    x = 200;
    y = 150;

    totalWidth = 500;
    totalHeight = 515;

    currentChart = 0;
}

ChartSet::~ChartSet() {
    delete dataSet;
}

void ChartSet::draw(std::vector<TimeMark *> *timeMarks) {
    float chartSpacing = currentChart->getSpacing();

    currentChart->setWidth(totalWidth);
    currentChart->setHeight(currentChart->calculateHeight(totalHeight, dataSet->getNumberCharts()));
    currentChart->setGlobalMinX(dataSet->getGlobalMinX());
    currentChart->setGlobalMaxX(dataSet->getGlobalMaxX());
    currentChart->setGlobalMinY(dataSet->getGlobalMinY());
    currentChart->setGlobalMaxY(dataSet->getGlobalMaxY());

    for (int chart = 0; chart < dataSet->getNumberCharts(); chart++) {
        currentChart->setIndex(chart % 8);
        currentChart->draw(dataSet->getValues(chart), x, getChartYLocation(chart));
    }

    for (int tm = 0; tm < timeMarks->size(); tm++) {
        TimeMark *timeMark = timeMarks->at(tm);
        int chart = timeMark->getChart();
        int time = timeMark->getTime();

        currentChart->drawLine(x, getChartYLocation(chart), time);
    }
}

int ChartSet::getChartYLocation(int chartIndex) {
    return y + (currentChart->getHeight() + currentChart->getSpacing()) * (dataSet->getNumberCharts() - chartIndex - 1);
}

void ChartSet::updateValues() {
    dataSet->updateValues();
}

void ChartSet::drawToPick(std::vector<PickColor *> *pickColors) {
    for (int i = 0; i < dataSet->getNumberCharts(); i++) {
        currentChart->drawToPick(pickColors->at(i), x, getChartYLocation(i));
    }
}
