#include "PrintText.h"

void PrintText::drawStrokeText(std::string text, float x, float y, float h, int horizAlign, int vertAlign, bool whiteBg, float rotate) {
    float scale = h / 119.05;

    float horizOff = 0;
    float vertOff = 0;

    switch (horizAlign) {
        case HORIZ_RIGHT:
            horizOff = strokeWidth(text, h);
            break;
        case HORIZ_CENTER:   
            horizOff = strokeWidth(text, h) / 2;
            break;
        case HORIZ_LEFT:
        default:
            break;
    }

    switch (vertAlign) {
        case VERT_TOP:
            vertOff = h;
            break;
        case VERT_CENTER:   
            vertOff = h / 2;
            break;
        case VERT_BOTTOM:
        default:
            break;
    }

    if (rotate == 90 || rotate == -270) {
        float tmp = vertOff;
        vertOff = horizOff;
        horizOff = -tmp;
    }

    if (rotate == -90 || rotate == 270) {
        float tmp = vertOff;
        vertOff = -horizOff;
        horizOff = tmp;
    }

    glPushMatrix();
        glTranslatef(x - horizOff, y - vertOff, 0);
        glRotatef(rotate, 0, 0, 1);
        glScalef(scale, scale, 1);
    
        if (whiteBg) {
            drawWhiteBackground(text, h, 4);
        }

        for (unsigned int i = 0; i < text.size(); i++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
        }
    glPopMatrix();
}

void PrintText::drawWhiteBackground(std::string label, float fontHeight, float padding) {
    float scale = fontHeight / 119.05;
    float paddingScaled = padding / scale;

    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR, currentColor);

    float h = 119.05;
    float w = PrintText::strokeWidth(label, h);

    glPolygonMode(GL_FRONT, GL_FILL);  
    glColor4f(1.0, 1.0, 1.0, 0.85);

    glRectf(-paddingScaled,        -paddingScaled,
            w + paddingScaled, h + paddingScaled);

    glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}

float PrintText::strokeWidth(std::string text, float h) {
    int length = 0;
    float scale = h / 119.05;

    for (std::string::size_type i = 0; i < text.size(); i++) {
        length += glutStrokeWidth(GLUT_STROKE_ROMAN, text[i]);
    }

    return scale * length;
}