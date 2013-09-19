#include "Symbol.h"
#include "Color.h"
#include <GL/glut.h>

//------------------ Constructors ------------------------------------
/**
 * Create a new shape at position 0,0 of size 1,1 with a black border of width
 * 2.
 */
Symbol::Symbol() {
   setRotation(0);
   setSize(0.5, 0.5);
   setBorderWidth(1.0);
   setFillColor(new Color(0.5, 0.5, 0.5));
   setBorderColor(new Color(0.0, 0.0, 0.0));
   setDrawFill(true);
   setDrawBorder(true);
}

//------------------ Destructor ------------------------------------
Symbol::~Symbol() {
    delete fillColor;
    delete borderColor;
}

//------------------ public methods -------------------------------

void Symbol::draw() {//float x, float y) {
    glPushMatrix();
        //glTranslatef(x, y, 0);
        glRotatef(rotation, 0, 0, 1);
        glScalef(width, height, 1.0);

        // Draw the filled polygon from the vertices.
        if (drawFill) {
            glPolygonMode( GL_FRONT, GL_FILL );            
            glColor4f( fillColor->r, fillColor->g, fillColor->b, fillColor->a );

            glBegin( GL_POLYGON );
                drawFillAtOrigin();
            glEnd();
        }

        // Draw the border if one is desired.
        if (drawBorder && borderWidth != 0) {
            glPolygonMode(GL_FRONT, GL_LINE);
            glColor4f( borderColor->r, borderColor->g, borderColor->b, borderColor->a );
            glLineWidth(borderWidth);
            
            glBegin(GL_LINE_LOOP);//glBegin(GL_POLYGON);
                drawOutlineAtOrigin();
            glEnd();

            glLineWidth(1);
        }
    glPopMatrix();
}

/**
 * Set the "nomimal" color of the object to the specified color.  This does not
 * require that all components of the object must be the same color.  Typically,
 * the largest component will take on this color, but the decision is made by
 * the child class.
 *
 * @param r The red component of the desired color (a value from 0.0 to 1.0).
 * @param g The green component of the desired color (a value from 0.0 to 1.0).
 * @param b The blue component of the desired color (a value from 0.0 to 1.0).
 */
void Symbol::setFillColor(float r, float g, float b) {
    fillColor->r = r;
    fillColor->g = g;
    fillColor->b = b;
}

/**
 * Set the border color to the specified RGB color values.
 *
 * @param r The red component of the desired border color (a value from 0.0 to
 *  1.0).
 * @param g The green component of the desired border color (a value from 0.0 to
 *  1.0).
 * @param b The blue component of the desired border color (a value from 0.0 to
 *  1.0).
 */
void Symbol::setBorderColor(float r, float g, float b) {
    borderColor->r = r;
    borderColor->g = g;
    borderColor->b = b;
}