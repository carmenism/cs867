#include <stdio.h>
#include "flowVis.h"
#include <glut.h>
#include <iostream>
#include <math.h>

#include "Color.h"

using namespace std;

flowVis::flowVis()
{
    age = 100;
	load();
}

void flowVis::load()
{

	FILE *fp;
	int i,j;

	fp = fopen("uVelocity2.dat","r");
	fscanf(fp,"%d %d", &nRows, &nCols);
	cerr <<"R C " << nRows << " " << nCols << "\n";
	u = new float*[nRows];
	v = new float*[nCols];
	for(i=0;i<nCols;++i)
	{
		u[i] = new float[nCols];
		v[i] = new float[nCols];
	}

	for(i=0;i<nRows;++i)
		for(j=0;j<nCols;++j)
		{
			fscanf(fp,"%f",&u[i][j]);
		}

	fclose(fp);
	fp = fopen("vVelocity2.dat","r");
	fscanf(fp,"%d %d", &nRows, &nCols);
	for(i=0;i<nRows;++i)
		for(j=0;j<nCols;++j)
		{
			fscanf(fp,"%f",&v[i][j]);
		}
	fclose(fp);
	
}

bool flowVis::getVec(float x, float y, float &dx, float &dy)
{
	int ix,iy;
	if (x>(nCols-1) || x < 0)return false;
	if (y>(nRows-1) || y < 0)return false;

	ix = int(x); iy = int(y);
	dx = u[iy][ix];
	dy = v[iy][ix];


}

void flowVis::drawBackground(float winWidth, float winHeight) {
    float width = winWidth / nCols;
    float height = winHeight / nRows;

    for (int i = 0; i < nCols; i++) {
        for (int j = 0; j < nRows; j++) {
            float dx = u[j][i];
            float dy = v[j][i];

            float speed = sqrt(dx * dx + dy * dy);

            float minSpeed = 0.5;
            float maxSpeed = 18;
            if (speed < minSpeed) {
                glColor4f(0, 0, 0, 1); //black
            } else {
                float r, g, b;
                Color::getColorFromVelocity((speed - minSpeed) / maxSpeed, r, g, b);
                glColor4f(r, g, b, 1);
            }

            float x = i * width;
            float y =  j * height;
            glRectf(x, y, x + width, y + height);
        }
    }
}

void flowVis::traceN(int number)
{
	float xp, yp, dx, dy;
    float thicknessStart = 1.0;
    float thicknessEnd = 10.0;
    float thicknessDelta = (thicknessEnd - thicknessStart) / age;

    glColor4f(1, 1, 1, 1);

	for (int i = 0; i < number; i++)
	{
		xp = rand() % nCols;
		yp = rand() % nRows;

        
		float lastXp = -1;
        float lastYp = -1;

        for (int j = 0; j < age; j++)
		{
			getVec(xp,yp,dx,dy);
            float speed = sqrt(dx * dx + dy * dy);
			xp = xp + dx*0.5;
			yp = yp + dy*0.5;
			
            float t = thicknessStart + thicknessDelta * j;
            t = t + 0.25 * (speed / 18) * t;

            if (lastXp != -1 && lastYp != -1) {
    

                glLineWidth(1);
                glBegin(GL_LINE_STRIP);
                
                    glVertex2f(lastXp, lastYp);
                    
                    glVertex2f(xp, yp);
                glEnd();
                
            }
            
        	glColor4f(1,1,1,0.1);
            glPushMatrix();
            glTranslatef(xp, yp, 0);
            if (j == age - 1) {
                float angle = atan((dy)/(dx)) * 180 / 3.1415926 - 90;
                drawTriangle(angle, t);
            } else {
                //glutSolidSphere(t / 2, 15, 2);
            }
            glPopMatrix();

            lastXp = xp;
            lastYp = yp;
		}

	}
		
}

void flowVis::drawTriangle(float rotation, float t) {
    glPushMatrix();
        glRotatef(rotation, 0, 0, 1);
        glScalef(5 * t, 2 *t, 1);

        float sideLength = 1.0 / sqrt(3.0);
        float altitude = 0.5;

        glPolygonMode( GL_FRONT, GL_FILL );            
        glColor4f( 1,1,1,1 );

        glBegin( GL_POLYGON );
            glVertex2f(-sideLength / 2, -altitude / 2);
            glVertex2f(sideLength / 2, -altitude / 2);
            glVertex2f(0, altitude / 2);
        glEnd();
    glPopMatrix();
}

/*
void flowVis::traceN(int n)
{
	int i,j;
	float xp,yp,dx,dy;
	float r,g,b;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLineWidth(2.0);
	for (i=0;i< n;++i)
	{
		xp = rand()%nCols;
		yp = rand()%nRows;

		glBegin(GL_LINE_STRIP);

		for(j=0;j<100;++j)
		{
			getVec(xp,yp,dx,dy);
		
			r = float(j)*0.01; // link to age

			glColor4f(r,r,1.0-r,0.1);

			xp += dx*0.1;
			yp += dy*0.1;

			glVertex2f(xp,yp);

		}
		glEnd();
	}
}

*/