#include "HorizonGraph.h"
#include "Color.h"
#include <GL/glut.h>
#include <iostream>

HorizonGraph::HorizonGraph() {
    numberBands = 3;
    
    colorPos = new Color(0, 0, 0.8, 0.4);
    colorNeg = new Color(1, 0, 0, 0.4);
}

HorizonGraph::~HorizonGraph() {
    delete colorPos;
    delete colorNeg;
}

void HorizonGraph::drawAtOrigin(std::vector<float> *values) {
    glEnable(GL_SCISSOR_TEST);
    glScissor(x, y, width, height);

    float rangeY = globalMaxY - globalMinY;
    bandSize = rangeY / (2 * numberBands);
    middle = globalMinY + (rangeY / 2);

    drawColor(values, colorPos, true, false);
    drawColor(values, colorNeg, false, true);
    
    glDisable(GL_SCISSOR_TEST);
}

void HorizonGraph::drawColor(std::vector<float> *values, Color *color, bool fillUnderLine, bool flip) {
    glPolygonMode( GL_FRONT, GL_FILL ); 
    glColor4f(color->r, color->g, color->b, color->a);
    
    //float otherEndPolygon = height * 2 * numberBands;
    //if (fillUnderLine) {
    //    otherEndPolygon = 0;
    //}

    float otherEndPolygon = getYLocation(middle) * (2 * numberBands);

    for (int b = 0; b < numberBands; b++) {
        if (b == numberBands - 1) {
            glColor4f(color->r, color->g, color->b, 1);
        }

        glPushMatrix();
        
        if (flip) {
            glTranslatef(0, -b * height + numberBands * height, 0);
            glScalef(1, -1, 1);
        } else {
            glTranslatef(0, -b * height - numberBands * height, 0);
        }

        float lastX = -1;
        float lastY = -1;        
        
        for (int time = 0; time < values->size(); time++) {
            float value = values->at(time);
            float posX = getXLocation(time);
            float posY = getYLocation(value) * (2 * numberBands);

            if (lastX != -1) {
                glBegin( GL_POLYGON );
                glVertex2f(lastX, otherEndPolygon);
                glVertex2f(lastX, lastY);
                glVertex2f(posX, posY);
                glVertex2f(posX, otherEndPolygon);
                glEnd();
            }

            lastX = posX;
            lastY = posY;
        }        

        glPopMatrix();
    }
}