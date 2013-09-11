#include <stdio.h>
#include "flowVis.h"
#include <glut.h>
#include <iostream>
#include <math.h>
#include <limits>

#include "Color.h"

using namespace std;

flowVis::flowVis()
{
    age = 500;
	load();
}

void flowVis::load()
{

	FILE *fp;
	int i,j;

	fp = fopen("uVelocity1.dat","r");
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
	fp = fopen("vVelocity1.dat","r");
	fscanf(fp,"%d %d", &nRows, &nCols);
	for(i=0;i<nRows;++i)
		for(j=0;j<nCols;++j)
		{
			fscanf(fp,"%f",&v[i][j]);
		}
	fclose(fp);
	
    findMinMaxSpeeds();
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

void flowVis::findMinMaxSpeeds() {
    minSpeed = numeric_limits<float>::max();
    maxSpeed = -1 * numeric_limits<float>::max();

    for (int i = 0; i < nCols; i++) {
        for (int j = 0; j < nRows; j++) {
            float dx = u[j][i];
            float dy = v[j][i];

            float speed = sqrt(dx * dx + dy * dy);

            if (speed > maxSpeed) {
                maxSpeed = speed;
            }

            if (speed < minSpeed) {
                minSpeed = speed;
            }
        }
    }
}

void flowVis::drawBackground(float orthoRight, float orthoTop) {
    float width = orthoRight / nCols;
    float height = orthoTop / nRows;

    for (int i = 0; i < nCols; i++) {
        for (int j = 0; j < nRows; j++) {
            float dx = u[j][i];
            float dy = v[j][i];

            float speed = sqrt(dx * dx + dy * dy);

            float interval = (maxSpeed - minSpeed) / 8;

            /*float minSpeed = 0.5;
            float maxSpeed = 18;*/
            /*if (speed < minSpeed) {
                glColor4f(0, 0, 0, 1); //black
            } else {
                float r, g, b;
                Color::getColorFromVelocity((speed - minSpeed) / maxSpeed, r, g, b);
                glColor4f(r, g, b, 1);
            }*/
            if (speed < minSpeed + (interval  / 2)) {
                glColor4f(0, 0, 0, 1); //black
            } else if (speed < minSpeed + interval) {
                glColor4f(0.007, 0.145, 0.404, 1); //blue
            } else if (speed < minSpeed + 2 * interval) {
                glColor4f(0.32, 0.09, 0.61, 1); //purple
            } else if (speed < minSpeed + 3 * interval) {
                glColor4f(0.592, 0, 0.412, 1); //violet
            } else if (speed < minSpeed + 4 * interval) {
                glColor4f(0.706, 0.102, 0.102, 1); //red
            } else if (speed < minSpeed + 5 * interval) {
                glColor4f(0.682, 0.318, 0.094, 1); //orange red
            } else if (speed < minSpeed + 6 * interval) {
                glColor4f(0.808, 0.494, 0.114, 1); //orange
            } else if (speed < minSpeed + 7 * interval) {
                glColor4f(0.710, 0.694, 0.335, 1); //yellow
            } else {
                glColor4f(0.64, 0.64, 0.64, 1); //gray
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
    float thicknessEnd = 4.0;
    float thicknessDelta = (thicknessEnd - thicknessStart) / age;

    float alphaStart = 0.05;
    float alphaEnd = 0.65;
    float alphaDelta = (alphaEnd - alphaStart) / age;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
			xp = xp + dx*0.06;
			yp = yp + dy*0.06;
			
            float t = thicknessStart + thicknessDelta * j;
            float alpha = alphaStart + alphaDelta * j;
            t = t + 0.25 * (speed / 18) * t;

            if (lastXp != -1 && lastYp != -1) {
    

                glLineWidth(t);
                glBegin(GL_LINE_STRIP);
                
                    glColor4f(1, 1, 1, alpha);
                    glVertex2f(lastXp, lastYp);
                    
                    glVertex2f(xp, yp);
                glEnd();
                
            }
            
        	/*glColor4f(1,1,1,alphaEnd);
            if (j == age - 1) {
                drawTriangle(xp, yp, dx, dy);
            } else {
                //glutSolidSphere(t / 2, 15, 2);
            }*/

            lastXp = xp;
            lastYp = yp;
		}

	}
		
}

void flowVis::drawTriangle(float xp, float yp, float dx, float dy) {
    glPushMatrix();
        glTranslatef(xp, yp, 0);

        glPolygonMode( GL_FRONT, GL_FILL );  

        float speed = sqrt(dx * dx + dy * dy);
        float len = 15.0;
        float wid = 5.0;
        glBegin( GL_TRIANGLES );
            glVertex2f(len * dx / speed, len * dy / speed);
            glVertex2f(wid * -dy / speed, wid *  dx / speed);
            glVertex2f(wid *  dy / speed, wid * -dx / speed);
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

			glColor4f(1,1,1,0.1);

			xp += dx*0.06;
			yp += dy*0.06;

			glVertex2f(xp,yp);

		}
		glEnd();
	}
}

*/