#ifndef TASK_H_
#define TASK_H_

class DataSet;
class TimeMark;

#include <vector>
#include <string>

class Task {
public:
    Task(std::string label, DataSet *dataSet);
    ~Task();
    
    bool responseCorrect(int responseIndex);

    void configure();

    std::vector<TimeMark *> *getTimeMarks() { return timeMarks; }

    void clearTimeMarks();

    std::string getLabel() { return label; }
protected:
    DataSet *dataSet;
    std::string label;
    int answerIndex;
    
    std::vector<TimeMark *> *timeMarks;

    virtual void determineTimes() = 0;
    virtual void determineAnswer() = 0;
};

#endif /* TASK_H_ */