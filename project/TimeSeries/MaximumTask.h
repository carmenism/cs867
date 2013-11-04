#ifndef MAXIMUMTASK_H_
#define MAXIMUMTASK_H_

class DataSet;

#include "Task.h"
#include <vector>

class MaximumTask : public Task {
public:
    MaximumTask(DataSet *dataSet);
    ~MaximumTask();
protected:
    float distanceFromStart;
    float distanceFromEnd;

    int time;
    
    virtual void determineTimes();
    virtual void determineAnswer();
};

#endif /* MAXIMUMTASK_H_ */