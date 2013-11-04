#include "Picker.h"
#include "Experiment.h"
#include "PickColor.h"
#include <GL/glut.h>
#include <vector>

Picker::Picker(Experiment *experiment) {
    this->experiment = experiment;
}

int Picker::pick(int x, int y) {
    float color[4];    
    unsigned char val[3] = {'\0'};
    unsigned int pick;

    glGetFloatv(GL_COLOR_CLEAR_VALUE, color);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(color[0], color[1], color[2], color[3]);

    std::vector<PickColor *> *pickColors = new std::vector<PickColor *>();

    for (unsigned int i = 0; i < experiment->getNumberCharts(); i++) {
        pickColors->push_back(new PickColor(i & 0xFF, (i >> 8) & 0xFF, 0));
    }

    glDisable(GL_BLEND);
    experiment->drawToPick(pickColors);
    glEnable(GL_BLEND);

    glFlush();
    glReadBuffer(GL_BACK);
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, val);
    
    pick = (val[1] << 8) + val[0];

    int size = pickColors->size();
    if (pick >=0 && pick < size) {
        return pick;
    }

    return -1;
}