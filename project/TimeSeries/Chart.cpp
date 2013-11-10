#include "Chart.h"
#include "Color.h"
#include "PickColor.h"
#include <GL/glut.h>

Chart::Chart(std::string label) {
    this->label = label;
    buttonOffsetX = 50;
    buttonOffsetY = 5;
    buttonWidth = 15;
    buttonHeight = 15;
    buttonColor = new Color(0, 0, 0, 1);
    spacing = 10;
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

    drawWhiteBackground(x, y);

    glPushMatrix();
        glTranslatef(x, y, 0);

        drawAtOrigin(values);
    glPopMatrix();

    drawBorder(x, y);

    glColor4f(buttonColor->r, buttonColor->g, buttonColor->b, buttonColor->a);
    drawButton(x, y);
}

void Chart::drawWhiteBackground(float x, float y) {
    glPolygonMode(GL_FRONT, GL_FILL);  
    glColor4f(1, 1, 1, 1);

    glPushMatrix();
        glTranslatef(x, y, 0);
        glBegin(GL_POLYGON);
            glVertex2f( 0, 0 );
            glVertex2f( 0, height );
            glVertex2f( width, height );
            glVertex2f( width, 0 );
        glEnd();
    glPopMatrix();
}

void Chart::drawBorder(float x, float y) {
    glPolygonMode(GL_FRONT, GL_LINE);  
    glLineWidth(1.0);
    glColor4f(0, 0, 0, 1);

    glPushMatrix();
        glTranslatef(x, y, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f( 0, 0 );
            glVertex2f( 0, height );
            glVertex2f( width, height );
            glVertex2f( width, 0 );
        glEnd();
    glPopMatrix();
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
    glColor3ub(pickColor->r, pickColor->g, pickColor->b);
    glPushMatrix();
        glTranslatef(x + width + buttonOffsetX, y + buttonOffsetY, 0);
        glPolygonMode(GL_FRONT, GL_FILL);  
        
        glBegin(GL_POLYGON);
            glVertex2f( 0, 0 );
            glVertex2f( 0, buttonHeight );
            glVertex2f( buttonWidth, buttonHeight );
            glVertex2f( buttonWidth, 0 );
        glEnd();
    glPopMatrix();
}

void Chart::drawButton(float x, float y) {
    glPushMatrix();
        glTranslatef(x + width + buttonOffsetX, y + buttonOffsetY, 0);
        glPolygonMode(GL_FRONT, GL_FILL);  
        
        glBegin(GL_POLYGON);
            glVertex2f( 0, 0 );
            glVertex2f( 0, buttonHeight );
            glVertex2f( buttonWidth, buttonHeight );
            glVertex2f( buttonWidth, 0 );
        glEnd();
    glPopMatrix();
}

float Chart::calculateHeight(float fullHeight, int numberCharts) {
    float withoutSpacing = fullHeight - (numberCharts - 1) * spacing;

    return withoutSpacing / numberCharts;
}