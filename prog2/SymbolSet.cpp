#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include "SymbolSet.h"
#include "Symbol.h"
#include "Circle.h"
#include "Triangle.h"
#include "Square.h"
#include "PrintText.h"

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
    Circle *c0 = new Circle();
    symbols.push_back(c0);

    Square *s1 = new Square();
    s1->setFillColor(0.85, 0, 0);
    symbols.push_back(s1);

    Triangle *t2 = new Triangle();
    t2->setFillColor(0.93, 0.6, 0);
    symbols.push_back(t2);
    
    Circle *c3 = new Circle();
    c3->setFillColor(0.93, 0.93, 0);
    symbols.push_back(c3);

    Square *s4 = new Square();
    s4->setFillColor(0, 0.5, 0);
    symbols.push_back(s4);

    Triangle *t5 = new Triangle();
    t5->setFillColor(0, 0, 0.93);
    symbols.push_back(t5);
    
    Circle *c6 = new Circle();
    c6->setFillColor(0.33, 0.1, 0.55);
    symbols.push_back(c6);

    Square *s7 = new Square();
    s7->setFillColor(0.96, 0.66, 0.71);
    symbols.push_back(s7);

    Triangle *t8 = new Triangle();
    t8->setFillColor(0.64, 0.74, 0.07);
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

    PrintText::drawStrokeText(toStr((trialNumber / NUM_TRIALS) + 1) + "/10 Targets", 1, 2, 0.5);
    PrintText::drawStrokeText(toStr((trialNumber % NUM_TRIALS) + 1) + "/30 Trials", 1, 1, 0.5);
}