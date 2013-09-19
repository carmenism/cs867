#include "Heart.h"
#include <GL/glut.h>
#include <math.h>


#define M_PI 3.14159265359


Heart::Heart() {
}

//------------- destructor -----------------------
Heart::~Heart() {
}

void Heart::drawOutlineAtOrigin() {
    float radius = 1.0 / (2.0 + sqrt(2.0));
    float xShift = radius * sqrt(2.0) / 2;
    
    float off2 = M_PI / 16;

    //left
    drawLineArc(-xShift, xShift / 2, radius, M_PI / 4 - off2, M_PI + off2);

    glVertex2f(0, (xShift / 2) - 3 * xShift);

    //right
    drawLineArc(xShift, xShift / 2, radius, 3 * M_PI / 4 + M_PI + off2, M_PI - off2);    
}

void Heart::drawFillAtOrigin() {
    float radius = 1.0 / (2.0 + sqrt(2.0));
    float xShift = radius * sqrt(2.0) / 2;
    float rectSide = 2 * radius;
    float rectDiagonal = rectSide * sqrt(2.0);

    float off2  = M_PI / 16;
   
    drawLineArc(-xShift, xShift / 2, radius, M_PI / 4 - off2, M_PI + off2);
    glEnd();

    glBegin( GL_POLYGON );
    drawLineArc(xShift, xShift / 2, radius, 3 * M_PI / 4 + M_PI + off2, M_PI - off2);   

    glVertex2f(rectDiagonal / 2 , -xShift / 2);   
    glVertex2f(0, (-xShift / 2) + rectDiagonal / 2);
    glVertex2f(-rectDiagonal / 2, -xShift / 2);
    glVertex2f(0, (-xShift / 2) - rectDiagonal / 2);
}

void Heart::drawLineArc(float cenX, float cenY, float radius, float startAngle, float arcAngle) {
    //glEnable(GL_POLYGON_SMOOTH);
    float num_segments = 180.0;

    float theta = arcAngle / num_segments; 
    float tangetial_factor = tanf(theta);//calculate the tangential factor 

    float radial_factor = cosf(theta);//calculate the radial factor 

    float xx = radius * cosf(startAngle);//we start at angle = 0 
    float yy = radius * sinf(startAngle); 

    for(int ii = 0; ii < num_segments; ii++) 
    { 
        glVertex2f(cenX + xx, cenY + yy);

        //calculate the tangential vector 

        float tx = -yy; 
        float ty = xx; 

        //add the tangential vector 

        xx += tx * tangetial_factor; 
        yy += ty * tangetial_factor; 

        //correct using the radial factor 

        xx *= radial_factor; 
        yy *= radial_factor; 
    }

    //glDisable(GL_POLYGON_SMOOTH);
}