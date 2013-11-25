#include "Textures.h"
#include "PickColor.h"
#include "GL/glut.h"
#include <iostream>

Textures::Textures() {
    colors = new std::vector<PickColor *>();
    colors->push_back(new PickColor(254, 0, 0)); // red
    colors->push_back(new PickColor(50, 50, 50));
    colors->push_back(new PickColor(10, 215, 0)); // green
    colors->push_back(new PickColor(0, 0, 0));
    colors->push_back(new PickColor(0, 150, 240)); ///
    init();
}

Textures::~Textures() {

}

PickColor *Textures::getColor(int i) {
    return colors->at(i % colors->size());
}

void Textures::init() {
	glGenTextures(15, textures);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glEnable(GL_TEXTURE_2D);

    for (int i = 0; i < 15; i++) {
        makeTexture(i);
    }

    glDisable(GL_TEXTURE_2D);
}

void Textures::makeTexture(int index) {
    PickColor *color = getColor(index);
    unsigned char trans = 80;
    unsigned char transSolid = 30;

    int i = index % 4;

    if (i == 0 || i == 2) {
        makeSolid(solidA, color, transSolid);
        registerTexture(solidA, index);
    } else if (i == 1) {
        makeStripes(stripes, color, trans);
        registerTexture(stripes, index);
    } else {
        makeSlantedStripes(slantstripes, color, trans);
        registerTexture(slantstripes, index);
    }
}

void Textures::registerTexture(unsigned char arr[TEX_SIZE][TEX_SIZE][4], int index) {
    glBindTexture(GL_TEXTURE_2D, textures[index]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_BLEND); //GL_BLEND
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, arr);
}

void Textures::makeStripes(unsigned char arr[TEX_SIZE][TEX_SIZE][4], PickColor *color, unsigned char trans) {
    for (int i = 0; i < TEX_SIZE; i++) {
        for (int j = 0; j < TEX_SIZE; j++) {
		    arr[i][j][0] = color->r;
			arr[i][j][1] = color->g;
			arr[i][j][2] = color->b;

            int jj = j % 8;

			if (jj == 0 || jj == 1 || jj == 4 || jj == 5) {
				arr[i][j][3] = trans;
			} else {
				arr[i][j][3] = 0;
			}	
		}
	}
}

void Textures::makeSlantedStripes(unsigned char arr[TEX_SIZE][TEX_SIZE][4], PickColor *color, unsigned char trans) {
    for (int i = 0; i < TEX_SIZE; i++) {
        for (int j = 0; j < TEX_SIZE; j++) {
		    arr[i][j][0] = color->r;
			arr[i][j][1] = color->g;
			arr[i][j][2] = color->b;

            int ii = i % 8;
            int jj = j % 8;

			if ((ii == 3 && jj == 0)
                || (ii == 2 && jj == 1)
                || (ii == 1 && jj == 2)
                || (ii == 0 && jj == 3)
                || (ii == 0 && jj == 4)
                || (ii == 1 && jj == 3)
                || (ii == 2 && jj == 2)
                || (ii == 3 && jj == 1)
                || (ii == 4 && jj == 0)//
                || (ii == 4 && jj == 7)
                || (ii == 5 && jj == 6)
                || (ii == 6 && jj == 5)
                || (ii == 7 && jj == 4)
                || (ii == 5 && jj == 7)
                || (ii == 6 && jj == 6)
                || (ii == 7 && jj == 5)) {
				arr[i][j][3] = trans;
			} else {
				arr[i][j][3] = 0;
			}	
		}
	}
}

void Textures::makeSolid(unsigned char arr[TEX_SIZE][TEX_SIZE][4], PickColor *color, unsigned char trans) {
    for (int i = 0; i < TEX_SIZE; i++) {
        for (int j = 0; j < TEX_SIZE; j++) {
		    arr[i][j][0] = color->r;
			arr[i][j][1] = color->g;
			arr[i][j][2] = color->b;
		    arr[i][j][3] = trans;
		}
	}
}