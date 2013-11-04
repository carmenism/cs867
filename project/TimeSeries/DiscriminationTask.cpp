#include "DiscriminationTask.h"
#include "DataSet.h"
#include "TimeMark.h"
#include <stdlib.h>
#include <iostream>
#include <cmath>

DiscriminationTask::DiscriminationTask(DataSet *dataSet) : Task(dataSet) {
    distanceFromStart = 0.1;
    distanceFromEnd = 0.1;

    times = new std::vector<int>();
}

DiscriminationTask::~DiscriminationTask() {
    times->clear();

    delete times;
}

void DiscriminationTask::determineTimes() {
    float globalMinX = dataSet->getGlobalMinX();
    float globalMaxX = dataSet->getGlobalMaxX();
    float timeRange = globalMaxX - globalMinX;
    float start = globalMinX + distanceFromStart * timeRange;
    float end = globalMaxX - distanceFromEnd * timeRange;

    int startI = int(start);
    int endI = int(end);
    int rangeI = endI - startI;

    times->clear();

    int tenPercent = int(timeRange * 0.1);

    for (int i = 0; i < dataSet->getNumberCharts(); i++) {
        bool unique = false;
        int t;

        while (!unique) {
            t = startI + rand() % rangeI;
            
            if (times->empty()) {
                unique = true;
            } else {
                int numberEqual = 0;

                for (int j = 0; j < times->size(); j++) {
                    if (times->at(j) == t) {
                        numberEqual++;
                    }
                }

                if (numberEqual == 0) {
                    unique = true;
                }

                float diffWithLast = std::abs(times->back() - t);

                if (diffWithLast < tenPercent) {
                    unique = false;
                }
            }
        }

        times->push_back(t);
        timeMarks->push_back(new TimeMark(i, t));
    }

    //for (int i = 0; i < times->size(); i++) {
    //    std::cout << " " << times->at(i);
    //}
}

void DiscriminationTask::determineAnswer() {
    float max = -10000;

    for (int i = 0; i < times->size(); i++) {
        float v = dataSet->getValue(i, times->at(i));

        if (max < v) {
            max = v;
            answerIndex = i;
        }
    }
}