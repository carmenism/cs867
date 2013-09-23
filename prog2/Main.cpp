/**
 * Program 2 
 *
 * @author Carmen St. Jean (crr8)
 *
 * UNH CS 867, fall 2013
 */
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include "SymbolSet.h"
#include "Stopwatch.h"
#include "PrintText.h"

using namespace std;

std::ofstream outFile;

float winWid,winHeight;
float rx,ry;

float px, py;
float dx,dy;

SymbolSet *symbSet;
Stopwatch *stopwatch;
bool experimentStarted;
// designed as an introductin to glut

void writeRecord(int targetIndex, bool present, bool correctAnswer, double time) {
    outFile << targetIndex << ", ";

    if (present) {
        outFile << "Present, ";
    } else {
        outFile << "Not Present, ";
    }

    if (correctAnswer) {
        outFile << "Correct, ";
    } else {
        outFile << "Incorrect, ";
    }

    outFile << time << "\n";
}

void InitLighting()
{
	float light_position[] = {20.0,20.0,-40.0,0.0};
	glLightfv(GL_LIGHT0,GL_POSITION, light_position);
	float ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	//float diffuse[] = {0.6f, 0.6f, 0.6f , 1.0f};
	float diffuse[] = {0.8f, 0.8f, 0.8f , 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	float specular[] = {1.0f, 1.0f, 1.0f , 1.0f};
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);	
	float specReflection[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
	float mat_ambient[] = { 0.0f, 0.2f, 0.5f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	float mat_diffuse[] = { 0.6f, 0.6f,0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_ambient);
	glMateriali(GL_FRONT, GL_SHININESS, 80);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);

	glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

}

void redraw( void )
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
    glPolygonMode( GL_FRONT, GL_FILL );    

    if (experimentStarted) {
        glRectf(12.0,5.0,22.0,15.0); 
	    symbSet->draw();
    } else {
        glColor3f(0, 0, 0);
        PrintText::drawStrokeText("Press space to begin.", 17, 10, 1, HORIZ_CENTER);
    }

    glColor3f(0, 0, 0);
    PrintText::drawStrokeText("V - NO",  12, 3, 0.5, HORIZ_CENTER);
    PrintText::drawStrokeText("M - YES", 22, 3, 0.5, HORIZ_CENTER);

	rand();

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
	switch(key)
	{
        case ' ':
            if (!experimentStarted) {
                experimentStarted = true;
                stopwatch->start();
                redraw();
            }
            break;
		case 'v': 
		case 'm': 
        
        // should go to file
        bool present = symbSet->getTargetPresence();
        double time = stopwatch->stop();

		if (key == 'v') {
            writeRecord(symbSet->getTargetIndex(), present, present == false, time); 
            cerr << "no  ";
        }

        if (key == 'm') {
            writeRecord(symbSet->getTargetIndex(), present, present == true, time);
            cerr << "yes ";
            
        }

        cerr << "Time " << time << "\n";

        if (!symbSet->advanceTrial()) {
            exit(0);
        }

        int pause = 1000;
        
        if (symbSet->getTrialNumber() % 30 == 0) {
            pause = 6000;
        }

		for(int i=0;i<pause;++i) // blank for one second
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glutSwapBuffers();
		}

        stopwatch->start();
		
		redraw();
		break;
	}
}

int main(int argc, char *argv[])
{
    srand (time(NULL));

    experimentStarted = false;
	cerr << "hello world\n";

    stopwatch = new Stopwatch();
	symbSet = new SymbolSet();
    
    outFile.open("outputResults.csv");

    px=py = 200.0;

	dx = 2.5;dy = 1.5;

	winWid = 1200.0;
	winHeight = 800.0;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Basic example");
	glutPositionWindow(200,100);
	glutReshapeWindow(int(winWid),int(winHeight));

	glClearColor(0.9,0.9,0.9,1.0);
	InitLighting();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,30.5,0.0,20.3, -100.0, 100.0); // size in cm.

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutCreateMenu(rightMenu);
	glutAddMenuEntry("Choice One",1);
	glutAddMenuEntry("Choice Two",2);
	glutAddMenuEntry("Quit",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(redraw);
	glutIdleFunc(redraw);
	glutMotionFunc( motion);	
	glutMouseFunc( mousebutton);
	glutKeyboardFunc( keyboard );

	glutMainLoop();

    
    outFile.close();

	return 0;
}