#include "ChartSet.h"
#include "DataSet.h"
#include "Chart.h"
#include "HorizonGraph.h"
#include "LineChart.h"
#include "TimeMark.h"

ChartSet::ChartSet(DataSet *dataSet) {
    this->dataSet = dataSet;

    chartWidth = 500;
    chartHeight = 25;

    currentChart = 0;
}

ChartSet::~ChartSet() {
    delete dataSet;
}

void ChartSet::draw(std::vector<TimeMark *> *timeMarks) {
    currentChart->setWidth(chartWidth);
    currentChart->setHeight(chartHeight);
    currentChart->setGlobalMinX(dataSet->getGlobalMinX());
    currentChart->setGlobalMaxX(dataSet->getGlobalMaxX());
    currentChart->setGlobalMinY(dataSet->getGlobalMinY());
    currentChart->setGlobalMaxY(dataSet->getGlobalMaxY());

    float x = 100;
    float y = 100;
    float spacing = 10;

    for (int chart = 0; chart < dataSet->getNumberCharts(); chart++) {
        currentChart->draw(dataSet->getValues(chart), x, y + (chartHeight + spacing) * chart);
    }

    for (int tm = 0; tm < timeMarks->size(); tm++) {
        TimeMark *timeMark = timeMarks->at(tm);
        int chart = timeMark->getChart();
        int time = timeMark->getTime();

        currentChart->drawLine(x, y + (chartHeight + spacing) * chart, time);
    }
}

void ChartSet::updateValues() {
    dataSet->updateValues();
}