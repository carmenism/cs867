
#include <glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "flowVis.h"

using namespace std;


float winWid,winHeight;
float orthoTop, orthoRight;
float rx,ry;

float red,green,blue;

flowVis *fv;

void redraw( void )
{
	glClear(GL_COLOR_BUFFER_BIT);
	
    fv->drawBackground(orthoRight, orthoTop);
		glColor3f(1.0,1.0,1.0);
		fv->traceN(2500);

	glutSwapBuffers();
}

void rightMenu(int sel)
{
	switch(sel)
	{
	case 1: cerr << "Menu One \n";
		break;
	case 2: cerr << "Menu Two \n";
		break; 
	case 3: exit(1);
		break;
	}
}


void motion(int x, int y) 
// called when a mouse is in motion with a button down
{
 	rx = float(x); ry = winHeight - float(y);
}


void mousebutton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)

	{
		rx = float(x); ry = winHeight - float(y);

		redraw();
	}
}

void keyboard(unsigned char key, int x, int y) 
// x and y givethe mouse pos
{
	cerr << "Key " << key << " " << int(key) << "\n";
	switch(key)
	{
	case 'r': red = 1.0; green = 0.0; blue = 0.0;
		break;
	case 'g': red = 0.0; green = 1.0; blue = 0.0;
		break;
	case 'b': red = 0.0; green = 0.0; blue = 1.0;
		break; 
	}
}

int main(int argc, char *argv[])
{
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
	glutAddMenuEntry("Choice One",1);
	glutAddMenuEntry("Choice Two",2);
	glutAddMenuEntry("Quit",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(redraw);
	//glutIdleFunc(redraw);
	glutMotionFunc( motion);	
	glutMouseFunc( mousebutton);
	glutKeyboardFunc( keyboard );
	glutMainLoop();

	return 0;
}