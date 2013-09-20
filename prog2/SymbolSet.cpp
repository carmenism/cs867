#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include "SymbolSet.h"
#include "Symbol.h"
#include "Circle.h"
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
    s1->setFillColor(0, 0.5, 0);
    symbols.push_back(s1);

    Triangle *t2 = new Triangle();
    t2->setFillColor(0.3, 0.5, 1);
    t2->setSize(0.4, 0.4);
    symbols.push_back(t2);

    Triangle *t3 = new Triangle();
    t3->setFillColor(0.93, 0.6, 0);
    t3->setRotation(180);
    t3->setSize(0.4, 0.4);
    symbols.push_back(t3);
    
    Circle *c4 = new Circle();
    c4->setFillColor(0.93, 0.93, 0);
    symbols.push_back(c4);

    PlusSign *ps5 = new PlusSign();
    ps5->setSize(0.45, 0.45);
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
    t8->setFillColor(0.75, 0.9, 0.12);
    symbols.push_back(t8);
    
    Circle *c9 = new Circle();
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

    /*for (int i = 0; i < 10; i++) {

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
    PrintText::drawStrokeText(toStr((trialNumber % NUM_TRIALS) + 1) + "/30 Trials", 0.5, 0.1, 0.35);*/
    glColor4f(0, 0, 0, 1);
    PrintText::drawStrokeText("< 1.6", 1.5, 1 * 0.75, 0.45, HORIZ_RIGHT, VERT_CENTER);
    glPushMatrix();
	    glTranslatef(2, 1 * 0.75, 0);
        symbols[5]->draw();
    glPopMatrix();

    glColor4f(0, 0, 0, 1);
    PrintText::drawStrokeText("< 1.4", 1.5, 2 * 0.75, 0.45, HORIZ_RIGHT, VERT_CENTER);
    

    glColor4f(0, 0, 0, 1);
    PrintText::drawStrokeText("< 1.2", 1.5, 3 * 0.75, 0.45, HORIZ_RIGHT, VERT_CENTER);
    glPushMatrix();
	    glTranslatef(2, 3 * 0.75, 0);
        symbols[1]->draw();
    glPopMatrix();
    glPushMatrix();
	    glTranslatef(2 + 1 * 0.75, 3 * 0.75, 0);
        symbols[6]->draw();
    glPopMatrix();

    glColor4f(0, 0, 0, 1);
    PrintText::drawStrokeText("< 1.0", 1.5, 4 * 0.75, 0.45, HORIZ_RIGHT, VERT_CENTER);

    glPushMatrix();
	    glTranslatef(2 + 2 * 0.75, 4 * 0.75, 0);
        symbols[9]->draw();
    glPopMatrix();
    glPushMatrix();
	    glTranslatef(2, 4 * 0.75, 0);
        symbols[3]->draw();
    glPopMatrix();    
    glPushMatrix();
	    glTranslatef(2 + 1 * 0.75, 4 * 0.75, 0);
        symbols[8]->draw();
    glPopMatrix();

    glColor4f(0, 0, 0, 1);
    PrintText::drawStrokeText("< 0.8", 1.5, 5 * 0.75, 0.45, HORIZ_RIGHT, VERT_CENTER);
    glPushMatrix();
	    glTranslatef(2, 5 * 0.75, 0);
        symbols[0]->draw();
    glPopMatrix();
    glPushMatrix();
	    glTranslatef(2 + 1 * 0.75, 5 * 0.75, 0);
        symbols[2]->draw();
    glPopMatrix();
    glPushMatrix();
	    glTranslatef(2 + 2 * 0.75, 5 * 0.75, 0);
        symbols[4]->draw();
    glPopMatrix();
    glPushMatrix();
	    glTranslatef(2 + 3 * 0.75, 5 * 0.75, 0);
        symbols[7]->draw();
    glPopMatrix();

    glPopMatrix();
}