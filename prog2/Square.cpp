#include "Square.h"
#include <GL/glut.h>

Square::Square() {
}

//------------- destructor -----------------------
Square::~Square() {
}

void Square::drawFillAtOrigin() {
    drawAtOrigin();
}

void Square::drawOutlineAtOrigin() {
    drawAtOrigin();
}

void Square::drawAtOrigin() {
    float sideLength = 1.0;

    glVertex2f(-sideLength / 2, -sideLength / 2);
    glVertex2f(-sideLength / 2, sideLength / 2);
    glVertex2f(sideLength / 2, sideLength / 2);
    glVertex2f(sideLength / 2, -sideLength / 2);
}