#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include "SymbolSet.h"
#include "Symbol.h"
#include "Circle.h"
#include "CirclePair.h"
#include "Triangle.h"
#include "Square.h"
#include "PrintText.h"
#include "PlusSign.h"
#include "Heart.h"
#include "Star.h"

#define NUM_TRIALS 30
#define NUM_TARGETS 10

SymbolSet::SymbolSet()
{
    initSymbols();

    trialNumber = 0;

    initializeTargetPresence();
    initializeTrial();
}

void SymbolSet::initSymbols() {
    Square *s0 = new Square();
    s0->setFillColor(0.85, 0, 0);
    symbols.push_back(s0);
    
    Square *s1 = new Square();
    s1->setSize(0.5 / sqrt(2.0), 0.5 / sqrt(2.0));
    s1->setRotation(45);
    s1->setFillColor(0.25, 0.99, 0.01);
    symbols.push_back(s1);

    Triangle *t2 = new Triangle();
    t2->setFillColor(0.25, 0.40, 1);
    t2->setSize(0.4, 0.4);
    symbols.push_back(t2);

    Triangle *t3 = new Triangle();
    t3->setFillColor(0.95, 0.6, 0);
    t3->setRotation(180);
    t3->setSize(0.4, 0.4);
    symbols.push_back(t3);
    
    Circle *c4 = new Circle();
    c4->setFillColor(0.93, 0.93, 0);
    symbols.push_back(c4);

    PlusSign *ps5 = new PlusSign();
    ps5->setSize(0.45, 0.45);
    ps5->setFillColor(0.75, 0.75, 0.75);
    symbols.push_back(ps5);
    
    PlusSign *ps6 = new PlusSign();
    ps6->setRotation(45);
    ps6->setSize(0.5 / sqrt(2.0), 0.5 / sqrt(2.0));
    ps6->setFillColor(0.45, 0.125, 0.65);
    symbols.push_back(ps6);

    Heart *h7 = new Heart();
    h7->setFillColor(0.96, 0.66, 0.71);
    //h7->setSize(0.45, 0.45);
    symbols.push_back(h7);

    Star *t8 = new Star();
    t8->setFillColor(0, 0.5, 0);
    symbols.push_back(t8);
    
    CirclePair *c9 = new CirclePair();
    c9->setFillColor(0, 0, 0);
    symbols.push_back(c9);
}

void SymbolSet::initializeTargetPresence() {
    targetPresence.clear();

    std::vector<bool> tempArray;

    for (int i = 0; i < (NUM_TRIALS / 2); i++) {
        tempArray.push_back(true);
        tempArray.push_back(false);
    }

    while (!tempArray.empty()) {
        int index = getRandom(0, tempArray.size() - 1);
        targetPresence.push_back(tempArray[index]);        
        tempArray.erase(tempArray.begin() + index);
    }
}

bool SymbolSet::getTargetPresence() {
    return targetPresence[trialNumber % NUM_TRIALS];
}

bool SymbolSet::advanceTrial() {
    trialNumber++;

    if (trialNumber >= NUM_TRIALS * NUM_TARGETS) {
        return false;
    }

    if (trialNumber % 30 == 0) {
        initializeTargetPresence();
    }

    initializeTrial();

    return true;
}

int SymbolSet::getTargetIndex() {
    return trialNumber / NUM_TRIALS;
}

void SymbolSet::initializeTrial() {
    setShapes();
    setPositions();
}

void SymbolSet::setShapes() {
    int targetIndex = getTargetIndex();

    std::vector<int> distractors;

    for (int i = 0; i < 10; i++) {
        if (i != targetIndex) {
            distractors.push_back(i);
        }
    }

    bool drawTarget = targetPresence[trialNumber % NUM_TRIALS];
    int targetI, targetJ;

    if (drawTarget) {
        targetI = getRandom(0, 9);
        targetJ = getRandom(0, 9);
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (drawTarget && i == targetI && j == targetJ) {
                shapes[i][j] = targetIndex;
            } else {
                shapes[i][j] = distractors[getRandom(0, 8)];
            }
        }
    }
}

void SymbolSet::setPositions() {
    for (int i = 0; i < 10; i++) {
        std::vector<float> xRow;
        std::vector<float> yRow;

        for (int j = 0; j < 10; j++) {
            float x = float(i) + 0.5;
            float y = float(j) + 0.5;

            x = x + 0.5 * float(rand() % 1000) / 999.0 - 0.25;
            y = y + 0.5 * float(rand() % 1000) / 999.0 - 0.25;

            xPos[i][j] = x;
            yPos[i][j] = y;
        }
    }
}

void SymbolSet::draw() 
{
	glPushMatrix();
	glTranslatef(12.0,5.0,0.0);

	glColor3f(0.0,0.0,1.0);

    for (int i = 0; i < 10; i++) {

        for (int j = 0; j < 10; j++) {
            float x = xPos[i][j];
            float y = yPos[i][j];
            
            glPushMatrix();
			    glTranslatef(x, y, 0);
                symbols[shapes[i][j]]->draw();
		    glPopMatrix();
        }
    }

	glPopMatrix();

    glPushMatrix();
    glTranslatef(6.0, 10.0, 0.0);
    symbols[getTargetIndex()]->draw();
    glPopMatrix();

    glColor4f(0,0,0,1);
    PrintText::drawStrokeText("Target Symbol", 6, 12, 0.5, HORIZ_CENTER);
    
    PrintText::drawStrokeText(toStr((trialNumber / NUM_TRIALS) + 1) + "/10 Targets", 0.5, 0.6, 0.35);
    PrintText::drawStrokeText(toStr((trialNumber % NUM_TRIALS) + 1) + "/30 Trials", 0.5, 0.1, 0.35);
}
/*
void SymbolSet::draw() {
  	glPushMatrix();
	glTranslatef(12.0,5.0,0.0);

    float x = 0.75;
    float yScale = 2.5;

    glPolygonMode( GL_FRONT, GL_FILL );   
    glColor3f(1,1,1);
    glRectf(-2, -1,  14, 12);

    glPolygonMode(GL_FRONT, GL_LINE);
    glColor3f(0.6, 0.6, 0.6);

    glRectf(0, 0, 12, 0.5 * yScale);
    glRectf(0, 0, 12, 1 * yScale);
    glRectf(0, 0, 12, 1.5 * yScale);
    glRectf(0, 0, 12, 2 * yScale);
    glRectf(0, 0, 12, 2.5 * yScale);
    glRectf(0, 0, 12, 3 * yScale);
    glRectf(0, 0, 12, 3.5 * yScale);

    
    glRectf(0, 0, 4, 3.5 * yScale);
    glRectf(0, 0, 8, 3.5 * yScale);

    glColor3f(0, 0, 0);
    PrintText::drawStrokeText("Target Trials", 2, -0.75, 0.45, HORIZ_CENTER, VERT_BOTTOM, false, 0);
    PrintText::drawStrokeText("Blank Trials", 6, -0.75, 0.45, HORIZ_CENTER, VERT_BOTTOM, false, 0);
    PrintText::drawStrokeText("All Trials", 10, -0.75, 0.45, HORIZ_CENTER, VERT_BOTTOM, false, 0);

    PrintText::drawStrokeText("0", -0.25, 0 * yScale, 0.40, HORIZ_CENTER, VERT_BOTTOM, false, 90);
    PrintText::drawStrokeText("0.5", -0.25, 0.5 * yScale, 0.40, HORIZ_CENTER, VERT_BOTTOM, false, 90);
    PrintText::drawStrokeText("1.0", -0.25, 1.0 * yScale, 0.40, HORIZ_CENTER, VERT_BOTTOM, false, 90);
    PrintText::drawStrokeText("1.5", -0.25, 1.5 * yScale, 0.40, HORIZ_CENTER, VERT_BOTTOM, false, 90);
    PrintText::drawStrokeText("2.0", -0.25, 2.0 * yScale, 0.40, HORIZ_CENTER, VERT_BOTTOM, false, 90);
    PrintText::drawStrokeText("2.5", -0.25, 2.5 * yScale, 0.40, HORIZ_CENTER, VERT_BOTTOM, false, 90);
    PrintText::drawStrokeText("3.0", -0.25, 3.0 * yScale, 0.40, HORIZ_CENTER, VERT_BOTTOM, false, 90);
    PrintText::drawStrokeText("3.5", -0.25, 3.5 * yScale, 0.40, HORIZ_CENTER, VERT_BOTTOM, false, 90);

    PrintText::drawStrokeText("Time (seconds)", -1, 1.75 * yScale, 0.45, HORIZ_CENTER, VERT_BOTTOM, false, 90);

    
    PrintText::drawStrokeText("Average Response Times", 6, 3.75 * yScale, 0.55, HORIZ_CENTER, VERT_BOTTOM, false, 0);
           
    glPushMatrix();
	    glTranslatef(x, yScale * 0.59066667, 0);
        symbols[0]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 0.709733333, 0);
        symbols[1]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 0.925266667, 0);
        symbols[2]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 0.811066667, 0);
        symbols[3]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 0.6674, 0);
        symbols[4]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 0.873533333, 0);
        symbols[5]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 1.261466667, 0);
        symbols[6]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 0.750533333, 0);
        symbols[7]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 1.201533333, 0);
        symbols[8]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 0.717533333, 0);
        symbols[9]->draw();
    glPopMatrix();
    x += 0.5;
    glPushMatrix();
        glTranslatef(x, yScale * 0.85087333, 0);
        PrintText::drawStrokeText("*", 0, 0, 0.5, HORIZ_CENTER, VERT_CENTER, false, 0);
    glPopMatrix();

    x +=1.25;
           
    glPushMatrix();
	    glTranslatef(x, yScale * 0.901133333, 0);
        symbols[0]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 0.968066667, 0);
        symbols[1]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 1.877933333, 0);
        symbols[2]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 1.8682, 0);
        symbols[3]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 1.1696, 0);
        symbols[4]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 2.884933333, 0);
        symbols[5]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 3.284933333, 0);
        symbols[6]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 1.964133333, 0);
        symbols[7]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 2.763533333, 0);
        symbols[8]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 1.608133333, 0);
        symbols[9]->draw();
    glPopMatrix();
    x += 0.5;
    glPushMatrix();
        glTranslatef(x, yScale * 1.92906, 0);
        PrintText::drawStrokeText("*", 0, 0, 0.5, HORIZ_CENTER, VERT_CENTER, false, 0);
    glPopMatrix();

    x +=1.25;
           
    glPushMatrix();
	    glTranslatef(x, yScale * 0.7459, 0);
        symbols[0]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 0.8389, 0);
        symbols[1]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 1.4016, 0);
        symbols[2]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 1.339633333, 0);
        symbols[3]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 0.9185, 0);
        symbols[4]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 1.879233333, 0);
        symbols[5]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 2.2732, 0);
        symbols[6]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 1.357333333, 0);
        symbols[7]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 1.982533333, 0);
        symbols[8]->draw();
    glPopMatrix();
    x += 0.25;
    glPushMatrix();
	    glTranslatef(x, yScale * 1.162833333, 0);
        symbols[9]->draw();
    glPopMatrix();
    x += 0.5;
    glPushMatrix();
        glTranslatef(x, yScale * 1.389966667, 0);
        PrintText::drawStrokeText("*", 0, 0, 0.5, HORIZ_CENTER, VERT_CENTER, false, 0);
    glPopMatrix();

    glPopMatrix();
}*/