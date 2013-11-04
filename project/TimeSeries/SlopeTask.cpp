#include "SlopeTask.h"
#include "DataSet.h"
#include "TimeMark.h"
#include <stdlib.h>
#include <iostream>

SlopeTask::SlopeTask(DataSet *dataSet) 
: Task("Slope", dataSet) {
    distanceFromStart = 0.1;
    distanceFromEnd = 0.1;
    distanceBetween = 0.25;
}

SlopeTask::~SlopeTask() {

}

void SlopeTask::determineTimes() {
    float globalMinX = dataSet->getGlobalMinX();
    float globalMaxX = dataSet->getGlobalMaxX();
    float timeRange = globalMaxX - globalMinX;
    float start = globalMinX + distanceFromStart * timeRange;
    float end = globalMaxX - distanceFromEnd * timeRange;

    int startI = int(start);
    int endI = int(end);
    int rangeI = endI - startI;
    int distBetweenI = int(distanceBetween * timeRange);

    timeA = startI + rand() % rangeI;

    if (timeA + distBetweenI > endI) {
        findTimeBBeforeA(startI, distBetweenI);
    } else if (timeA - distBetweenI < startI) {
        findTimeBAfterA(endI, distBetweenI);
    } else {
        if ((rand() % 2) == 0) {
            findTimeBBeforeA(startI, distBetweenI);
        } else {
            findTimeBAfterA(endI, distBetweenI);
        }
    }

    if (timeA > timeB) {
        float temp = timeA;
        timeA = timeB;
        timeB = temp;
    }

    for (int i = 0; i < dataSet->getNumberCharts(); i++) {
        timeMarks->push_back(new TimeMark(i, timeA));
        timeMarks->push_back(new TimeMark(i, timeB));
    }

    //std::cout << "\n" << timeA << ", " << timeB << "\n";
}

void SlopeTask::findTimeBAfterA(int endI, int distBetweenI) {
    int newStart = timeA + distBetweenI;
    int newRange = endI - newStart;
    timeB = newStart + rand() % newRange;
}

void SlopeTask::findTimeBBeforeA(int startI, int distBetweenI) {
    int newStart = startI;
    int newRange = int(timeA) - distBetweenI - startI;
    timeB = newStart + rand() % newRange;
}

void SlopeTask::determineAnswer() {
    float maxDiff = -10000;

    for (int i = 0; i < dataSet->getNumberCharts(); i++) {
        float d = dataSet->getDifferenceForChartBetweenTimes(i, timeA, timeB);

        if (maxDiff < d) {
            maxDiff = d;
            answerIndex = i;
        }
    }
}