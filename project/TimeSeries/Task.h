#ifndef TASK_H_
#define TASK_H_

class DataSet;

class Task {
public:
    Task(DataSet *dataSet);
    ~Task();
    
    bool responseCorrect(int responseIndex);

    void configure();
protected:
    DataSet *dataSet;
    int answerIndex;
    
    virtual void determineTimes() = 0;
    virtual void determineAnswer() = 0;
};

#endif /* TASK_H_ */