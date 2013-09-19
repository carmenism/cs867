#include "Star.h"
#include <GL/glut.h>
#include <math.h>

Star::Star() {
}

//------------- destructor -----------------------
Star::~Star() {
}

void Star::drawOutlineAtOrigin() {
    float b = 0.4 / 2.5;
    float a = 66.0 / (15 * 19);

    glVertex2f(0, 0.5);     // top              1
    glVertex2f(b, 0.1);
    glVertex2f(0.5, 0.1);   // middle right     2
    glVertex2f(a, 0.5 - 2.5 * a); 
    glVertex2f(0.4, -0.5);  // bottom right     3
    glVertex2f(0, -7.0/30.0);
    glVertex2f(-0.4, -0.5); // bottom left      4
    glVertex2f(-a, 0.5 - 2.5 * a);
    glVertex2f(-0.5, 0.1);  // middle left      5
    glVertex2f(-b, 0.1);
}

void Star::drawFillAtOrigin() {
    float a = 66.0 / (15 * 19);

    glVertex2f(-0.5, 0.1);  // middle left      5
    glVertex2f(0.5, 0.1);   // middle right     2
    glVertex2f(0, -7.0/30.0);
    glEnd();

    glBegin( GL_POLYGON );
    glVertex2f(0, 0.5);     // top              1
    glVertex2f(-a, 0.5 - 2.5 * a);
    glVertex2f(0.4, -0.5);  // bottom right     3
    glEnd();

    glBegin( GL_POLYGON );
    glVertex2f(0, -7.0/30.0);
    glVertex2f(-0.4, -0.5); // bottom left      4
    glVertex2f(-a, 0.5 - 2.5 * a);
}