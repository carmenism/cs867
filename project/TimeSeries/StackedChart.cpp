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
    glBindTexture(GL_TEXTURE_2D, textures->textures[index]);

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
    glLineWidth(2.0);
    glColor3f(pColor->r / 255.0, pColor->g / 255.0, pColor->b / 255.0);

    glBegin(GL_LINE_LOOP);
    glVertex2f(0, 0);
    for (int time = 0; time < values->size(); time++) {
        float value = values->at(time);
        float posX = getXLocation(time);
        float posY = getYLocation(value) * hScale;
	        
        glVertex2f(posX, posY);
    }
    glVertex2f(width, 0);
    glEnd();
}

void StackedChart::drawWhiteBackground(float x, float y) {
    /*glPolygonMode(GL_FRONT, GL_FILL);  
    glColor4f(1, 1, 1, 1);

    glPushMatrix();
        glTranslatef(x, y, 0);
        glBegin(GL_POLYGON);
            glVertex2f( 0, 0 );
            glVertex2f( 0, height * hScale );
            glVertex2f( width, height * hScale );
            glVertex2f( width, 0 );
        glEnd();
    glPopMatrix();*/
}

void StackedChart::drawBorder(float x, float y) {

}