#include "Textures.h"
#include "PickColor.h"
#include "GL/glut.h"
#include <iostream>

Textures::Textures() {
    colors = new std::vector<PickColor *>();
    colors->push_back(new PickColor(250, 0, 0)); //red
    colors->push_back(new PickColor(37, 52, 148)); // teal
    colors->push_back(new PickColor(254, 153, 41)); // orange
    colors->push_back(new PickColor(178, 58, 238)); // purple
    colors->push_back(new PickColor(10, 215, 0)); // green
    colors->push_back(new PickColor(255, 215, 0)); // yellow
    init();
}

Textures::~Textures() {

}

PickColor *Textures::getColor(int i) {
    return colors->at(i % colors->size());
}

void Textures::init() {
    unsigned char trans = 120;
    unsigned char transSolid = 60;

    // even dots
    for (int i = 0; i < TEX_SIZE; i++) {
        for (int j = 0; j < TEX_SIZE; j++) {	
            dots[i][j][0] = colors->at(DOTS)->r;
			dots[i][j][1] = colors->at(DOTS)->g;
			dots[i][j][2] = colors->at(DOTS)->b;

            int ii = i % 8;
            int jj = j % 8;

			if ((ii == 0 || ii == 1 || ii == 2)
                && (jj == 0 || jj == 1 || jj == 2)) {
				dots[i][j][3] = trans;
			} else {
				dots[i][j][3] = 0;
			}	
		}
	}

    // slantstripes
    for (int i = 0; i < TEX_SIZE; i++) {
        for (int j = 0; j < TEX_SIZE; j++) {		
			unevendots[i][j][0] = colors->at(SLANTA)->r;
			unevendots[i][j][1] = colors->at(SLANTA)->g;
			unevendots[i][j][2] = colors->at(SLANTA)->b;

            int ii = i % 4;
            int jj = j % 4;

            if (ii == jj) {
				unevendots[i][j][3] = trans;
			} else {
				unevendots[i][j][3] = 0;
			}	
		}
	}

    // slantstripes
    for (int i = 0; i < TEX_SIZE; i++) {
        for (int j = 0; j < TEX_SIZE; j++) {
		    solidA[i][j][0] = colors->at(SOLIDA)->r;
			solidA[i][j][1] = colors->at(SOLIDA)->g;
			solidA[i][j][2] = colors->at(SOLIDA)->b;
		    solidA[i][j][3] = transSolid;
		}
	}

    // slantstripes
    for (int i = 0; i < TEX_SIZE; i++) {
        for (int j = 0; j < TEX_SIZE; j++) {
		    slantstripes[i][j][0] = colors->at(SLANTB)->r;
			slantstripes[i][j][1] = colors->at(SLANTB)->g;
			slantstripes[i][j][2] = colors->at(SLANTB)->b;

            int ii = i % 4;
            int jj = j % 4;

			if ((ii == 3 && jj == 0)
                || (ii == 2 && jj == 1)
                || (ii == 1 && jj == 2)
                || (ii == 0 && jj == 3)) {
				slantstripes[i][j][3] = trans;
			} else {
				slantstripes[i][j][3] = 0;
			}	
		}
	}

    // stripes
    for (int i = 0; i < TEX_SIZE; i++) {
        for (int j = 0; j < TEX_SIZE; j++) {
		    stripes[i][j][0] = colors->at(STRIPES)->r;
			stripes[i][j][1] = colors->at(STRIPES)->g;
			stripes[i][j][2] = colors->at(STRIPES)->b;

            int jj = j % 8;

			if (jj == 0 || jj == 1 || jj == 4 || jj == 5) {
				stripes[i][j][3] = trans;
			} else {
				stripes[i][j][3] = 0;
			}	
		}
	}

    // stripes
    for (int i = 0; i < TEX_SIZE; i++) {
        for (int j = 0; j < TEX_SIZE; j++) {
		    solidB[i][j][0] = colors->at(SOLIDB)->r;
			solidB[i][j][1] = colors->at(SOLIDB)->g;
			solidB[i][j][2] = colors->at(SOLIDB)->b;
      		solidB[i][j][3] = transSolid;	
		}
	}

	glGenTextures(6, textures);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textures[DOTS]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_BLEND);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, dots);

    glBindTexture(GL_TEXTURE_2D, textures[SLANTA]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_BLEND);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, unevendots);

    glBindTexture(GL_TEXTURE_2D, textures[SOLIDA]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_BLEND);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, solidA);

	glBindTexture(GL_TEXTURE_2D, textures[SLANTB]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_BLEND); //GL_BLEND
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, slantstripes);

	glBindTexture(GL_TEXTURE_2D, textures[STRIPES]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_BLEND); //GL_BLEND
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, stripes);
	
    glBindTexture(GL_TEXTURE_2D, textures[SOLIDB]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_BLEND); //GL_BLEND
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, solidB);
	
    glDisable(GL_TEXTURE_2D);
}