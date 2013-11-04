#include "MaximumTask.h"
#include "DataSet.h"
#include "TimeMark.h"
#include <stdlib.h>
#include <iostream>

MaximumTask::MaximumTask(DataSet *dataSet) : Task(dataSet) {
    distanceFromStart = 0.1;
    distanceFromEnd = 0.1;
}

MaximumTask::~MaximumTask() {

}

void MaximumTask::determineTimes() {
    float globalMinX = dataSet->getGlobalMinX();
    float globalMaxX = dataSet->getGlobalMaxX();
    float timeRange = globalMaxX - globalMinX;
    float start = globalMinX + distanceFromStart * timeRange;
    float end = globalMaxX - distanceFromEnd * timeRange;

    int startI = int(start);
    int endI = int(end);
    int rangeI = endI - startI;

    time = startI + rand() % rangeI;

    for (int i = 0; i < dataSet->getNumberCharts(); i++) {
        timeMarks->push_back(new TimeMark(i, time));
    }

    //std::cout << time;
}

void MaximumTask::determineAnswer() {
    float max = -10000;

    for (int i = 0; i < dataSet->getNumberCharts(); i++) {
        float v = dataSet->getValue(i, time);

        if (max < v) {
            max = v;
            answerIndex = i;
        }
    }
}