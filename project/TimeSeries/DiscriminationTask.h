#ifndef DISCRIMINATIONTASK_H_
#define DISCRIMINATIONTASK_H_

class DataSet;

#include "Task.h"
#include <vector>

class DiscriminationTask : public Task {
public:
    DiscriminationTask(DataSet *dataSet);
    ~DiscriminationTask();
protected:
    float distanceFromStart;
    float distanceFromEnd;

    std::vector<int> *times;
    
    virtual void determineTimes();
    virtual void determineAnswer();
};

#endif /* DISCRIMINATIONTASK_H_ */