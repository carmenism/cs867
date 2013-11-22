#include "StackedChart.h"
#include "Color.h"
#include "Textures.h"
#include "PickColor.h"
#include "GL/glut.h"

StackedChart::StackedChart() 
: Chart("Stacked Chart") {
    color = new Color(1, 0, 0, 1);
    textures = new Textures();

    hScale = 4;

    spacing = 0;
}

StackedChart::~StackedChart() {
    delete color;
}

void StackedChart::drawAtOrigin(std::vector<float> *values) {
    glPolygonMode( GL_FRONT, GL_FILL ); 
    glColor4f(1,0,0,1);
    
    float lastX = -1;
    float lastY = -1;

    float scale = 0.03;
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures->textures[index % 4]);

    for (int time = 0; time < values->size(); time++) {
        float value = values->at(time);
        float posX = getXLocation(time);
        float posY = getYLocation(value) * hScale;

        if (lastX != -1) {	        
            glBegin( GL_POLYGON );
            
            glNormal3d(0, 0, 1);
            glTexCoord2f(lastX * scale, 0);
            glVertex2f(lastX, 0);

            glNormal3d(0, 0, 1);
            glTexCoord2f(lastX * scale, lastY * scale);
            glVertex2f(lastX, lastY);

            glNormal3d(0, 0, 1);
            glTexCoord2f(posX * scale, posY * scale);
            glVertex2f(posX, posY);
            
            glNormal3d(0, 0, 1);
            glTexCoord2f(posX * scale, 0);
            glVertex2f(posX, 0);

            glEnd();
        }

        lastX = posX;
        lastY = posY;
    } 
    
    glDisable(GL_TEXTURE_2D);

    PickColor *pColor = textures->getColor(index);
    glPolygonMode(GL_FRONT, GL_LINE);  
    //glLineWidth(2.0);
    glColor3ub(pColor->r, pColor->g, pColor->b);

    glBegin(GL_LINE_STRIP);
    glLineWidth(1.0);
    glColor3ub(pColor->r, pColor->g, pColor->b);
    glVertex2f(0, 0);
    for (int time = 0; time < values->size(); time++) {
        float value = values->at(time);
        float posX = getXLocation(time);
        float posY = getYLocation(value) * hScale;
	    glLineWidth(1.0);
        glColor3ub(pColor->r, pColor->g, pColor->b);
        glVertex2f(posX, posY);
    }
    
    glColor3ub(pColor->r, pColor->g, pColor->b);
    //glLineWidth(2.0);
    glVertex2f(width, 0);
    glVertex2f(0, 0);
    glEnd();
}

void StackedChart::drawWhiteBackground(float x, float y) {

}

void StackedChart::drawBorder(float x, float y) {

}

float StackedChart::calculateHeight(float fullHeight, int numberCharts) {
    float h = fullHeight / (numberCharts + (hScale - 1));

    return h;
}

void StackedChart::drawButton(float x, float y) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures->textures[index % 4]);
    glColor3f(1,1,1);
    glPolygonMode(GL_FRONT, GL_FILL);  
    float scale = 0.03;
    glPushMatrix();
    glTranslatef(x + width + buttonOffsetX, y + buttonOffsetY, 0);
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex2f( 0, 0 );
            glTexCoord2f(0, buttonHeight * scale);
            glVertex2f( 0, buttonHeight );
            glTexCoord2f(buttonWidth * scale, buttonHeight * scale);
            glVertex2f( buttonWidth, buttonHeight );
            glTexCoord2f(buttonWidth * scale, 0);
            glVertex2f( buttonWidth, 0 );
        glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    PickColor *pColor = textures->getColor(index);
    glLineWidth(1.0);
    glColor3ub(pColor->r, pColor->g, pColor->b);
    
    glPushMatrix();
        glTranslatef(x + width + buttonOffsetX, y + buttonOffsetY, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f( 0, 0 );
            glVertex2f( 0, buttonHeight );
            glVertex2f( buttonWidth, buttonHeight );
            glVertex2f( buttonWidth, 0 );
        glEnd();
    glPopMatrix();
}

void StackedChart::drawLine(float x, float y, int time, int chart) {
    glPushMatrix();
        glTranslatef(x, y, 0);

        float xPos = getXLocation(time);

        glPolygonMode(GL_FRONT, GL_LINE);  
        glLineWidth(1.0);

        glColor4f(0, 0, 0, 1);
        glBegin(GL_LINE_LOOP);
            glVertex2f( xPos, 0 );
            glVertex2f( xPos, height * hScale);
        glEnd();
        glLineWidth(1.0);
        PickColor *pc = textures->getColor(chart);
        
        glColor4ub(pc->r, pc->g, pc->b, 60);
        glBegin(GL_LINE_LOOP);
            glVertex2f( xPos - 1, 0 );
            glVertex2f( xPos - 1, height * hScale);
        glEnd();

        glBegin(GL_LINE_LOOP);
            glVertex2f( xPos + 1, 0 );
            glVertex2f( xPos + 1, height * hScale);
        glEnd();
    glPopMatrix();
}