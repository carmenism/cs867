#include "Textures.h"
#include "PickColor.h"
#include "GL/glut.h"
#include <iostream>

Textures::Textures() {
    colors = new std::vector<PickColor *>();
    colors->push_back(new PickColor(254, 0, 0)); // red
    colors->push_back(new PickColor(150, 150, 150));
    colors->push_back(new PickColor(10, 215, 0)); // green
    colors->push_back(new PickColor(0, 0, 0));
    //colors->push_back(new PickColor(75, 75, 75));
    init();
}

Textures::~Textures() {

}

PickColor *Textures::getColor(int i) {
    return colors->at(i % colors->size());
}

void Textures::init() {
    unsigned char trans = 130;
    unsigned char transSolid = 50;

    // solidA
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
		    slantstripes[i][j][0] = colors->at(SLANT)->r;
			slantstripes[i][j][1] = colors->at(SLANT)->g;
			slantstripes[i][j][2] = colors->at(SLANT)->b;

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

    // solidB
    for (int i = 0; i < TEX_SIZE; i++) {
        for (int j = 0; j < TEX_SIZE; j++) {
		    solidB[i][j][0] = colors->at(SOLIDB)->r;
			solidB[i][j][1] = colors->at(SOLIDB)->g;
			solidB[i][j][2] = colors->at(SOLIDB)->b;
      		solidB[i][j][3] = transSolid;	
		}
	}

	glGenTextures(5, textures);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textures[SOLIDA]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_BLEND);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, solidA);

	glBindTexture(GL_TEXTURE_2D, textures[SLANT]);
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