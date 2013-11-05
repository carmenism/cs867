#include "Task.h"
#include "DataSet.h"
#include "TimeMark.h"
#include "PrintText.h"
#include <GL/glut.h>

Task::Task(std::string label, std::string instructions, DataSet *dataSet) {
    this->label = label;
    this->instructions = instructions;
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

void Task::drawInstructions(int x, int y) {
    glColor3f(0, 0, 0);
    PrintText::drawStrokeText(instructions, x, y, 16);
}