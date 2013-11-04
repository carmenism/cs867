#ifndef IIMEMARK_H_
#define TASK_H_

class TimeMark {
public:
    TimeMark(int c, int t) { chart = c; time = t; }
    ~TimeMark() {}
    
    int getChart() { return chart; }
    int getTime() { return time; }
private:
    int chart;
    int time;
};

#endif /* TASK_H_ */