#include "Triangle.h"
#include <GL/glut.h>
#include "math.h"

Triangle::Triangle()
{
}

//------------- destructor -----------------------
Triangle::~Triangle()
{
}

void Triangle::drawFillAtOrigin() {
    drawAtOrigin();
}

void Triangle::drawOutlineAtOrigin() {
    drawAtOrigin();
}

void Triangle::drawAtOrigin() {
    float sideLength = 2.0 / sqrt(3.0); //1.0;
    float altitude = 1.0; //sqrt(3.0) / 2.0;

    glVertex2f(-sideLength / 2, -altitude / 2);
    glVertex2f(sideLength / 2, -altitude / 2);
    glVertex2f(0, altitude / 2);
}