#include "Experiment.h"
#include "Picker.h"
#include <vector>
#include <iostream>
#include <GL/glut.h>

float winWid,winHeight;

Experiment *experiment;
Picker *picker;

void InitLighting() {
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
   
    if (experiment != 0) {
        experiment->draw();
    }

	glutSwapBuffers();
}

void reshape(int w, int h) {
    winWid = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0l, 1.0l); // set origin to bottom left corner
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void motion(int x, int y) {
    // called when a mouse is in motion with a button down
}

void pause(int pauseLength) {
	for(int i = 0; i < pauseLength; i++) {
		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
	}
}

void mousebutton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        int response = picker->pick(x, winHeight - y);

        if (response != -1) {
            std::cout << response << "\n";
            bool continueTrial = experiment->endTrial(response);

            if (continueTrial) {
                pause(1000);
                experiment->startTrial();
            } else {
                exit(0);
            }
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    	
}

int main(int argc, char *argv[]) {  
	winWid = 900.0;
	winHeight = 700.0;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Basic example");
	glutPositionWindow(200,100);
	glutReshapeWindow(int(winWid),int(winHeight));

	glClearColor(1,1,1,1.0);
	InitLighting();

    glViewport(0, 0, winWid, winHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, winWid, 0, winHeight, -1.0l, 1.0l); // set origin to bottom left corner

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutDisplayFunc(redraw);
	glutIdleFunc(redraw);
    glutReshapeFunc(reshape );
	glutMotionFunc( motion);	
	glutMouseFunc( mousebutton);
	glutKeyboardFunc( keyboard );

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    experiment = new Experiment();
    experiment->startTrial();

    picker = new Picker(experiment);

	glutMainLoop();

	return 0;
}