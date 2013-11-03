#include "RandomWalk.h"
#include "HorizonGraph.h"
#include "LineChart.h"
#include "ChartSet.h"
#include "DataSet.h"
#include <vector>
#include <iostream>
#include <GL/glut.h>

float winWid,winHeight;

/*RandomWalk *rw = 0;
HorizonGraph *hg = 0;
LineChart *line = 0;
std::vector<float> *values = 0;
float minY, maxY;*/
DataSet *dataSet = 0;
ChartSet *chartSet = 0;

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
   
    if (chartSet != 0) {
        chartSet->draw();
    }
    /*
    if (hg != 0) {
        hg->setWidth(500);
        hg->setHeight(25);
        hg->setGlobalMinX(0);
        hg->setGlobalMaxX(values->size() - 1);
        hg->setGlobalMinY(minY);
        hg->setGlobalMaxY(maxY);
        hg->draw(values, 50, 50);
    }
    if (line != 0) {
        line->setWidth(500);
        line->setHeight(25);
        line->setGlobalMinX(0);
        line->setGlobalMaxX(values->size() - 1);
        line->setGlobalMinY(minY);
        line->setGlobalMaxY(maxY);
        line->draw(values, 50, 100);
    }*/

	glutSwapBuffers();
}

void reshape(int w, int h) {
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


void mousebutton(int button, int state, int x, int y) {

}

void keyboard(unsigned char key, int x, int y) {
    // x and y givethe mouse pos
	
}

int main(int argc, char *argv[]) {
    dataSet = new DataSet();
    chartSet = new ChartSet(dataSet);
    chartSet->updateValues();
  /*  rw = new RandomWalk();
    values = rw->generate(1000, 500);
    values->clear();
    values->push_back(1);
    values->push_back(0);
    values->push_back(1);
    values->push_back(2);
    values->push_back(3);
    values->push_back(4);
    values->push_back(3);
    values->push_back(4);
    values->push_back(5);
    values->push_back(6);
    values->push_back(7);
    values->push_back(8);
    values->push_back(9);  // 10
    values->push_back(10);
    values->push_back(9);
    values->push_back(10);
    values->push_back(9);
    values->push_back(8);
    values->push_back(7);
    values->push_back(6);
    values->push_back(5);
    values->push_back(4);
    values->push_back(3);
    values->push_back(2);
    values->push_back(1);
    values->push_back(0);
    values->push_back(1); // 20
    values->push_back(2);
    values->push_back(3);
    values->push_back(4);
    values->push_back(5);
    values->push_back(6);
    values->push_back(7);
    values->push_back(8);
    values->push_back(9);  
    values->push_back(8);
    values->push_back(7);
    values->push_back(6); // 30
    values->push_back(5);
    values->push_back(4);
    values->push_back(3);
    values->push_back(2);
    values->push_back(1);
    values->push_back(0); // 36


    hg = new HorizonGraph();
    line = new LineChart();
    
    minY = 1000;
    maxY = -1000;

    for (int i = 0; i < values->size(); i++) {
        float v = values->at(i);
        std::cout << v << " ";

        if (minY > v) {
            minY = v;
        }

        if (maxY < v) {
            maxY = v;
        }
    }*/

	winWid = 1200.0;
	winHeight = 800.0;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Basic example");
	glutPositionWindow(200,100);
	glutReshapeWindow(int(winWid),int(winHeight));

	glClearColor(0.9,0.9,0.9,1.0);
	InitLighting();

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0.0,winWid,0.0,winHeight, -1.01, 1.01); // size in cm.

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

	glutMainLoop();

	return 0;
}