#include "Picker.h"
#include "Experiment.h"
#include "PickColor.h"
#include <GL/glut.h>
#include <vector>

Picker::Picker(Experiment *experiment) {
    this->experiment = experiment;
}

/**
 * Assigns pick colors to clickable items, tells the experiment to draw
 * using pick colors, and determines which pick color lies underneath the
 * mouse click coordinates.
 *
 * @param x The x-coordinate of the mouse event.
 * @param y The y-coordinate of the mouse event.
 * @return The index of the chart clicked or -1 if no chart was clicked.
 */
int Picker::pick(int x, int y) {
    float color[4];    
    unsigned char val[3] = {'\0'};
    unsigned int pick;

    // Clear your buffer.
    glGetFloatv(GL_COLOR_CLEAR_VALUE, color);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(color[0], color[1], color[2], color[3]);

    std::vector<PickColor *> *pickColors = new std::vector<PickColor *>();

    // For the number of charts that will be "pickable", assign a unique
    // pick color (which will act like a hash code for each chart).
    for (unsigned int i = 0; i < experiment->getNumberCharts(); i++) {
        pickColors->push_back(new PickColor(i & 0xFF, (i >> 8) & 0xFF, 0));
    }

    // Tell the experiment to draw according to the pick colors.
    glDisable(GL_BLEND);
    experiment->drawToPick(pickColors);
    glEnable(GL_BLEND);

    // Flush the buffer and switch back to buffer where all of your charts
    // are rendered normally.
    glFlush();

    // Read from the back buffer, which is where we drew the pick colors
    // earlier, using the x and y coordinates of the mouse click. Store the
    // result in val.
    glReadBuffer(GL_BACK);
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, val);
    
    // Convert the pick color (val) back to chart index (pick).
    pick = (val[1] << 8) + val[0];

    // If pick is a valid chart index, then return the chart index that was
    // clicked.
    int size = pickColors->size();

    if (pick >=0 && pick < size) {
        return pick;
    }

    // Otherwise, return -1 or some kind of flag that indicates nothing was
    // clicked.
    return -1;
}