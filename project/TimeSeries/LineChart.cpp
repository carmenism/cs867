#include "LineChart.h"
#include "Color.h"
#include "GL/glut.h"

LineChart::LineChart() {
    color = new Color(1, 0, 0, 1);
}

LineChart::~LineChart() {
    delete color;
}

void LineChart::drawAtOrigin(std::vector<float> *values) {
    glPolygonMode( GL_FRONT, GL_FILL ); 
    glColor4f(color->r, color->g, color->b, color->a);
    
    float lastX = -1;
    float lastY = -1;

    for (int time = 0; time < values->size(); time++) {
        float value = values->at(time);
        float posX = getXLocation(time);
        float posY = getYLocation(value);

        if (lastX != -1) {
            glBegin( GL_POLYGON );
            glVertex2f(lastX, 0);
            glVertex2f(lastX, lastY);
            glVertex2f(posX, posY);
            glVertex2f(posX, 0);
            glEnd();
        }

        lastX = posX;
        lastY = posY;
    }    
}