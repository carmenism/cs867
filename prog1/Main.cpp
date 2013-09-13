/**
 * Program 1 - Renders a vector flow field using OpenGL.
 *
 * @author Carmen St. Jean (crr8)
 *         Based on Main.cpp by Colin Ware.
 *
 * UNH CS 867, fall 2013
 */
#include <glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "flowVis.h"

using namespace std;

float winWid, winHeight;
float orthoTop, orthoRight;
float rx, ry;
bool showLegend;

float red,green,blue;

flowVis *fv;

void redraw( void ) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    fv->drawBackground(orthoRight, orthoTop);
    glColor3f(1.0,1.0,1.0);
    fv->traceN(2500);

    if (showLegend) {
        fv->drawLegend();
    }

    glutSwapBuffers();
}

void rightMenu(int sel) {
    switch(sel) {
    case 1: cerr << "Show Legend \n";
        showLegend = true;
        redraw();
        break;
    case 2: cerr << "Hide Legend \n";
        showLegend = false;
        redraw();
        break; 
    case 3: cerr << "Rainbow bg \n";
        fv->useRainbow();
        redraw();
        break;
    case 4: cerr << "Blue to yellow bg \n";
        fv->useBlueToYellow();
        redraw();
        break;
    case 5: cerr << "Black to white bg \n";
        fv->useBlackToWhite();
        redraw();
        break;
    case 6: cerr << "White arrows \n";
        fv->useWhiteArrow();
        redraw();
        break;
    case 7: cerr << "Black arrows \n";
        fv->useBlackArrow();
        redraw();
        break;
    case 8: cerr << "Red arrows \n";
        fv->useRedArrow();
        redraw();
        break;
    case 9: exit(1);
        break;
    }
}


void motion(int x, int y) {
     rx = float(x); ry = winHeight - float(y);
}


void mousebutton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        rx = float(x); ry = winHeight - float(y);

        redraw();
    }
}

void keyboard(unsigned char key, int x, int y) {
    cerr << "Key " << key << " " << int(key) << "\n";
    
    switch(key) {
    case 'r': red = 1.0; green = 0.0; blue = 0.0;
        break;
    case 'g': red = 0.0; green = 1.0; blue = 0.0;
        break;
    case 'b': red = 0.0; green = 0.0; blue = 1.0;
        break; 
    }
}

int main(int argc, char *argv[]) {
    showLegend = false;
    cerr << "hello world\n";
    red = green = blue = 1.0;

    fv = new flowVis();

    winWid = 800.0;
    winHeight = 600.0;
    orthoTop = 428;
    orthoRight = 614;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("Basic example");
    glutPositionWindow(200,100);
    glutReshapeWindow(int(winWid),int(winHeight));

    glClearColor(0.0,0.0,0.0,1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,orthoRight,0.0,orthoTop, -100.0, 100.0); // centimeters

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutCreateMenu(rightMenu);
    glutAddMenuEntry("Legend: Show",1);
    glutAddMenuEntry("Legend: Hide",2);
    glutAddMenuEntry("Background: Rainbow",3);
    glutAddMenuEntry("Background: Blue to Yellow",4);
    glutAddMenuEntry("Background: Black to White",5);
    glutAddMenuEntry("Arrows: White",6);
    glutAddMenuEntry("Arrows: Black",7);
    glutAddMenuEntry("Arrows: Red",8);
    glutAddMenuEntry("Quit",9);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(redraw);
    //glutIdleFunc(redraw);
    glutMotionFunc( motion);    
    glutMouseFunc( mousebutton);
    glutKeyboardFunc( keyboard );
    glutMainLoop();

    return 0;
}