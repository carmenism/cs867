#include "Task.h"
#include "DataSet.h"
#include "TimeMark.h"

Task::Task(std::string label, DataSet *dataSet) {
    this->label = label;
    this->dataSet = dataSet;

    timeMarks = new std::vector<TimeMark *>();
}

Task::~Task() {
    clearTimeMarks();
    delete timeMarks;
}

void Task::configure() {
    clearTimeMarks();
    determineTimes();
    determineAnswer();
}

bool Task::responseCorrect(int responseIndex) {
    return answerIndex == responseIndex;
}

void Task::clearTimeMarks() {
    while (!timeMarks->empty()) {
        TimeMark *tm = timeMarks->back();
        timeMarks->pop_back();
        delete tm;
    }

    timeMarks->clear();
}