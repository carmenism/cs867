#include "Chart.h"
#include "PickColor.h"
#include <GL/glut.h>

Chart::Chart(std::string label) {
    this->label = label;
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
    
    /*for (int i = 0; i < 10; i++) {
        glPushMatrix();
            glTranslatef(x, y, 0);

            float xPos = getXLocation(i * 100);

            glPolygonMode(GL_FRONT, GL_LINE);  
            glLineWidth(1.0);
            glColor4f(0, 1, 0, 1);

            glBegin(GL_LINE_LOOP);
                glVertex2f( xPos, 0 );
                glVertex2f( xPos, height );
            glEnd();
        glPopMatrix();
    }*/
}

void Chart::drawLine(float x, float y, int time) {
    glPushMatrix();
        glTranslatef(x, y, 0);

        float xPos = getXLocation(time);

        glPolygonMode(GL_FRONT, GL_LINE);  
        glLineWidth(1.0);
        glColor4f(0, 0, 0, 1);

        glBegin(GL_LINE_LOOP);
            glVertex2f( xPos, 0 );
            glVertex2f( xPos, height );
        glEnd();
    glPopMatrix();
}

void Chart::drawToPick(PickColor *pickColor, float x, float y) {
    glPushMatrix();
        glTranslatef(x, y, 0);

        glPolygonMode(GL_FRONT, GL_FILL);            
        glColor3ub(pickColor->r, pickColor->g, pickColor->b);

        glBegin(GL_POLYGON);
            glVertex2f( 0, 0 );
            glVertex2f( 0, height );
            glVertex2f( width, height );
            glVertex2f( width, 0 );
        glEnd();
    glPopMatrix();
}