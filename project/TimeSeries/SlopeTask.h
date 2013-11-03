#ifndef SLOPETASK_H_
#define SLOPETASK_H_

class DataSet;

#include "Task.h"

class SlopeTask : public Task {
public:
    SlopeTask(DataSet *dataSet);
    ~SlopeTask();
protected:
    float distanceFromStart;
    float distanceFromEnd;
    float distanceBetween;

    int timeA;
    int timeB;

    void findTimeBAfterA(int startI, int distanceBetweenI);
    void findTimeBBeforeA(int endI, int distBetweenI);
    
    virtual void determineTimes();
    virtual void determineAnswer();
};

#endif /* TASK_H_ */