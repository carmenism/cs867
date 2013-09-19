#include "PlusSign.h"
#include <GL/glut.h>

PlusSign::PlusSign() {
}

//------------- destructor -----------------------
PlusSign::~PlusSign() {
}

void PlusSign::drawOutlineAtOrigin() {
    float sideLength = 1.0;

    glVertex2f(sideLength / 6, sideLength / 2); 
    glVertex2f(sideLength / 6, sideLength / 6);
    glVertex2f(sideLength / 2, sideLength / 6);
    glVertex2f(sideLength / 2, -sideLength / 6);
    glVertex2f(sideLength / 6, -sideLength / 6);
    glVertex2f(sideLength / 6, -sideLength / 2);
    
    glVertex2f(-sideLength / 6, -sideLength / 2);
    glVertex2f(-sideLength / 6, -sideLength / 6);
    glVertex2f(-sideLength / 2, -sideLength / 6);
    glVertex2f(-sideLength / 2, sideLength / 6);
    glVertex2f(-sideLength / 6, sideLength / 6);
    glVertex2f(-sideLength / 6, sideLength / 2);
}

void PlusSign::drawFillAtOrigin() {
    glEnd();

    float sideLength = 1.0;

    glRectf(-sideLength / 6, -sideLength / 2, sideLength / 6, sideLength / 2);
    glRectf(-sideLength / 2, -sideLength / 6, sideLength / 2, sideLength / 6);

    glBegin( GL_POLYGON );
}