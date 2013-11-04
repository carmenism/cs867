#ifndef TASK_H_
#define TASK_H_

class DataSet;
class TimeMark;

#include <vector>

class Task {
public:
    Task(DataSet *dataSet);
    ~Task();
    
    bool responseCorrect(int responseIndex);

    void configure();

    std::vector<TimeMark *> *getTimeMarks() { return timeMarks; }

    void clearTimeMarks();
protected:
    DataSet *dataSet;
    int answerIndex;
    
    std::vector<TimeMark *> *timeMarks;

    virtual void determineTimes() = 0;
    virtual void determineAnswer() = 0;
};

#endif /* TASK_H_ */