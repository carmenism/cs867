#include "Task.h"
#include "DataSet.h"

Task::Task(DataSet *dataSet) {
    this->dataSet = dataSet;
}

Task::~Task() {

}

void Task::configure() {
    determineTimes();
    determineAnswer();
}

bool Task::responseCorrect(int responseIndex) {
    return answerIndex == responseIndex;
}