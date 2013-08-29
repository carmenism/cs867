#include <stdio.h>
#include "flowVis.h"
#include <glut.h>
#include <iostream>
#include <math.h>

using namespace std;

flowVis::flowVis()
{
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

void flowVis::traceN(int n)
{
	int i,j;
	float xp,yp,dx,dy;

	for (i=0;i< n;++i)
	{
		xp = rand()%nCols;
		yp = rand()%nRows;

		for(j=0;j<100;++j)
		{
			getVec(xp,yp,dx,dy);
			xp = xp + dx*0.5;
			yp = yp + dy*0.5;
			
			glRectf(xp-2.0,yp-2.0, xp+2.0,yp+2.0);

		}
	}
		
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