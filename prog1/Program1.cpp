#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

#define NP 400
#define AGE 200

float winWid,winHeight;
float rx,ry;
float x[NP], y[NP];  // the particles

//This example implements a simple particle tracing system as a 
//starting point for assignment 1

void getVec(float X,float Y, float &dx,float &dy)  
// this is the Differential Equation that defines the flow

{
	X *= 0.8;
	Y *= 0.9;

	dx = 0.5  + sin(0.12*Y) ;
	dy = 4.0*sin(0.6*sqrt(X))*cos(Y*0.03) +  2.7*sin(0.015*X)*(1.0*0.5*cos(Y/50.0)) + 0.02*(Y-200);

}

void initParticles()
{
	// Sets up a set of random start positions
	int i;
	for (i=0;i<NP;++i)
	{
		x[i] = winWid*float(rand()%1000)/1000.0;
		y[i] = winHeight*float(rand()%1000)/1000.0;
	}
}


void traceParticle(int i)
{
	// Traces and draws the i'th particle
	int j;
	float dx,dy;
	float sz;
	float r,g,b,vel;
	
	glColor3f(0.0,1.0,0.0);

	for (j=0;j< AGE;++j)
	{

			getVec(x[i],y[i],dx,dy);

			//vel = sqrt(dx*dx + dy*dy)/10.0; // the magnitude		

			x[i] += 0.1*dx;	  // how far does the particle move
			y[i] += 0.1*dy;
					
			//g = vel*2;
			//g = float(j)/AGE;
			//glColor3f(g,g,g);
			
			glPushMatrix();
				glTranslatef(x[i],y[i],0.0);
				glRectf(-2.0,-2.0,2.0,2.0);
			glPopMatrix();

			if (x[i] > (winWid-1.0)) x[i] = 0;  // wrap around;
			if (x[i] < 0.0) x[i] = winWid-1.0;
			if (y[i] > (winHeight-1.0)) y[i] = 0;  // wrap around;
			if (y[i] < 0.0) y[i] = winHeight-1.0;
						
		}	

}

void redraw( void )
{
	int i;

	initParticles();
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,0.0);
	glRectf(100.0,100.0,300.0,200.0);  // to be removed

	for(i=0;i<NP;++i)
		traceParticle(i);

	glutSwapBuffers();
}




void motion(int x, int y) 
// called when a mouse is in motion with a button down
{
 	rx = x; ry = winHeight - y;
}


void mousebutton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)

	{
		rx = x; ry = winHeight - y;

		redraw();
	}
}

void keyboard(unsigned char key, int x, int y) 
// x and y givethe mouse pos
{
	cerr << "Key " << key << " " << int(key) << "\n";
}

int main(int argc, char *argv[])
{
	int i;
	cerr << "hello world\n";

	winWid = 600.0;
	winHeight = 400.0;

	initParticles();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Basic example");
	glutPositionWindow(200,100);
	glutReshapeWindow(winWid,winHeight);

	glClearColor(0.0,0.0,0.0,1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,winWid,0.0,winHeight, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutDisplayFunc(redraw);
	//glutIdleFunc(redraw);
	glutMotionFunc( motion);	
	glutMouseFunc( mousebutton);
	glutKeyboardFunc( keyboard );
	glutMainLoop();

	return 0;
}



