#include <stdio.h>
#include "flowVis.h"
#include <glut.h>
#include <iostream>
#include <math.h>
#include <limits>

#include "Color.h"
#include "PrintText.h"

using namespace std;

flowVis::flowVis() {
    age = 500;

    colors = new vector<Color *>();

    colors->push_back(new Color(0, 0, 0, 1));          //black
    colors->push_back(new Color(0, 0, 0.55, 1));       //blue
    colors->push_back(new Color(0, 0.35, 0.35, 1));    //teal
    colors->push_back(new Color(0, 0.55, 0, 1));       //green
    colors->push_back(new Color(0.4, 0.62, 0, 1));     //yellow-green
    colors->push_back(new Color(0.8, 0.68, 0, 1));     //yellow
    colors->push_back(new Color(0.8, 0.52, 0, 1));     //orange
    colors->push_back(new Color(0.8, 0.22, 0, 1));     //red-orange
    colors->push_back(new Color(0.62, 0.07, 0.04, 1)); //red
    colors->push_back(new Color(0.55, 0.13, 0.32, 1)); //violet

	load();
}

flowVis::~flowVis() {
    while (!colors->empty()) {
        Color *c = colors->back();
        colors->pop_back();
        delete c;
    }

    delete colors;
}

void flowVis::load() {
	FILE *fp;
	int i,j;

	fp = fopen("uVelocity1.dat","r");
	fscanf(fp,"%d %d", &nRows, &nCols);
	cerr <<"R C " << nRows << " " << nCols << "\n";

	u = new float*[nRows];
	v = new float*[nCols];

	for(i=0;i<nCols;++i) {
		u[i] = new float[nCols];
		v[i] = new float[nCols];
	}

    for(i=0;i<nRows;++i) {
        for(j=0;j<nCols;++j) {
			fscanf(fp,"%f",&u[i][j]);
		}
    }

	fclose(fp);
	fp = fopen("vVelocity1.dat","r");
	fscanf(fp,"%d %d", &nRows, &nCols);

    for(i=0;i<nRows;++i) {
        for(j=0;j<nCols;++j) {
            fscanf(fp,"%f",&v[i][j]);
		}
    }

	fclose(fp);
	
    findMinMaxSpeeds();
}

bool flowVis::getVec(float x, float y, float &dx, float &dy) {
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

    cerr << "Min: " << minSpeed << "\n";
    cerr << "Max: " << maxSpeed << "\n";
    interval = (maxSpeed - minSpeed) / (colors->size() - 1);
}

void flowVis::drawBackground(float orthoRight, float orthoTop) {
    glPolygonMode(GL_FRONT, GL_FILL);

    float width = orthoRight / nCols;
    float height = orthoTop / nRows;

    for (int i = 0; i < nCols; i++) {
        for (int j = 0; j < nRows; j++) {
            float dx = u[j][i];
            float dy = v[j][i];

            float speed = sqrt(dx * dx + dy * dy);

            if (speed < minSpeed + (interval  / 2)) {
                Color *color = colors->at(0);
                glColor4f(color->r, color->g, color->b, color->a);
            } else {
                for (int c = 1; c < colors->size(); c++) {
                    if (speed < minSpeed + c * interval) {
                        Color *color = colors->at(c);
                        glColor4f(color->r, color->g, color->b, color->a);
                        break;
                    }
                }                
            }
         
            float x = i * width;
            float y =  j * height;
            glRectf(x, y, x + width, y + height);
        }
    }
}

void flowVis::drawLegend() {
    glPushMatrix();
    glTranslatef(10, 5, 0);
    if (colors->empty()) {
        return;
    }

    float width = 34;
    float height = 10;
    float fontHeight = 10;
    
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor4f(0, 0, 0, 1);
    glRectf(-10, -5, width * (colors->size() - 1) + 10, height + 5 + fontHeight + 5);

    Color *c = colors->at(0);
    drawLegendBox(0, 0, width / 2, height, c);
    drawLegendLabel(0, height + 5, minSpeed, fontHeight);
    
    c = colors->at(1);
    drawLegendBox(width / 2, 0, width / 2, height, c);
    drawLegendLabel(width / 2, height + 5, minSpeed + interval / 2, fontHeight);

    for (int i = 2; i < colors->size(); i++) {
        Color *color = colors->at(i);
        float x = width * (i - 1);
        float y = 0;
        drawLegendBox(x, y, width, height, color);

        float speed = minSpeed + (i - 1) * interval;
        drawLegendLabel(x, height + 5, speed, fontHeight);
    }  

    drawLegendLabel(width * (colors->size() - 1), height + 5, maxSpeed, fontHeight);
    glPopMatrix();
}

void flowVis::drawLegendLabel(float x, float y, float speed, float fontHeight) {
    glColor4f(1, 1, 1, 1);

    float newSpeed = float(int(10 * (speed + 0.05))) / 10.0;
    string label = toStr(newSpeed);

    PrintText::drawStrokeText(label, x, y, fontHeight, HORIZ_CENTER, VERT_BOTTOM, false, 0);
}

void flowVis::drawLegendBox(float x, float y, float width, float height, Color *c) {
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor4f(c->r, c->g, c->b, c->a);
    glRectf(x, y, x + width, y + height);

    drawBoundingBox(x, y, width, height);
}

void flowVis::drawBoundingBox(float x, float y, float width, float height) {
    glPolygonMode(GL_FRONT, GL_LINE);  
    glLineWidth(1.0);
    glColor4f(1, 1, 1, 1);

    glBegin(GL_LINE_LOOP);
        glVertex2f( x, y );
        glVertex2f( x, y + height );
        glVertex2f( x + width, y + height );
        glVertex2f( x + width, y );
    glEnd();
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

	for (int i = 0; i < number; i++) {
		xp = rand() % nCols;
		yp = rand() % nRows;

        
		float lastXp = -1;
        float lastYp = -1;

        for (int j = 0; j < age; j++) {
			getVec(xp,yp,dx,dy);
            float speed = sqrt(dx * dx + dy * dy);
			xp = xp + dx * 0.06;
			yp = yp + dy * 0.06;
			
            float t = thicknessStart + thicknessDelta * j;
            float alpha = alphaStart + alphaDelta * j;
            t = t + 0.25 * (speed / maxSpeed) * t;

            if (lastXp != -1 && lastYp != -1) {   
                glLineWidth(t);
                glBegin(GL_LINE_STRIP);                
                    glColor4f(1, 1, 1, alpha);
                    glVertex2f(lastXp, lastYp);                    
                    glVertex2f(xp, yp);
                glEnd();
                
            }
            
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