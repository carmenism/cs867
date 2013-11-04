#include "Chart.h"
#include <GL/glut.h>

Chart::Chart() {

}

Chart::~Chart() {

}

float Chart::getXLocation(float value) {
    float valueRange = globalMaxX - globalMinX;
    float distanceToMinValue = value - globalMinX;
    float percentage = distanceToMinValue / valueRange;

    return width * percentage;
}

float Chart::getYLocation(float value) {
    float valueRange = globalMaxY - globalMinY;
    float distanceToMinValue = value - globalMinY;
    float percentage = distanceToMinValue / valueRange;

    return height * percentage;
}

void Chart::draw(std::vector<float> *values, float x, float y) {
    //glEnable(GL_SCISSOR_TEST);
    //glScissor(x, y, width, height);

    this->x = x;
    this->y = y;

    glPushMatrix();
        glTranslatef(x, y, 0);

        drawAtOrigin(values);

        glPolygonMode(GL_FRONT, GL_LINE);  
        glLineWidth(1.0);
        glColor4f(0, 0, 0, 1);

        glBegin(GL_LINE_LOOP);
            glVertex2f( 0, 0 );
            glVertex2f( 0, height );
            glVertex2f( width, height );
            glVertex2f( width, 0 );
        glEnd();
    glPopMatrix();

    //glDisable(GL_SCISSOR_TEST);
}