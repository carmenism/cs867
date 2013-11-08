#include "Textures.h"
#include "PickColor.h"
#include "GL/glut.h"
#include <iostream>

Textures::Textures() {
    colors = new std::vector<PickColor *>();
    colors->push_back(new PickColor(250, 0, 0)); //red
    colors->push_back(new PickColor(65, 182, 196)); // teal
    colors->push_back(new PickColor(247, 104, 161)); // pink
    colors->push_back(new PickColor(254, 153, 41)); // orange
    colors->push_back(new PickColor(84, 39, 143)); //(122, 1, 119)); // purple
    colors->push_back(new PickColor(0, 104, 55)); // green
    colors->push_back(new PickColor(153, 52, 4)); // brown
    colors->push_back(new PickColor(130, 240, 153)); // lime green
    init();
}

Textures::~Textures() {

}

PickColor *Textures::getColor(int i) {
    return colors->at(i % colors->size());
}

void Textures::init() {
    float trans = 170;
    int index = 0;

    // even dots
    for (int i = 0; i < TEX_SIZE; i++) {
        for (int j = 0; j < TEX_SIZE; j++) {	
            dots[i][j][0] = colors->at(index % colors->size())->r;
			dots[i][j][1] = colors->at(index % colors->size())->g;
			dots[i][j][2] = colors->at(index % colors->size())->b;

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

    index++;

    // wavy
    for (int i = 0; i < TEX_SIZE; i++) {
        for (int j = 0; j < TEX_SIZE; j++) {	
		    wavy[i][j][0] = colors->at(index % colors->size())->r;
			wavy[i][j][1] = colors->at(index % colors->size())->g;
			wavy[i][j][2] = colors->at(index % colors->size())->b;

            int ii = i % 8;
            int jj = j % 8;

			if (((ii == 3 || ii == 7) && (jj == 1 || jj == 5))
                || ((ii == 2 || ii == 6) && (jj == 0 || jj == 3 || jj == 6 || jj == 7))
                || ((ii == 1 || ii == 5) && (jj == 2 || jj == 4))
                || ((ii == 0 || ii == 4) && (jj == 2 || jj == 4))) {
				wavy[i][j][3] = trans;
			} else {
				wavy[i][j][3] = 0;
			}	
		}
	}

    index++;

    // uneven dots
    for (int i = 0; i < TEX_SIZE; i++) {
        for (int j = 0; j < TEX_SIZE; j++) {		
			unevendots[i][j][0] = colors->at(index % colors->size())->r;
			unevendots[i][j][1] = colors->at(index % colors->size())->g;
			unevendots[i][j][2] = colors->at(index % colors->size())->b;

            int ii = i % 4;
            int jj = j % 4;

            if (ii == jj) {
			//if (((ii == 0 || ii == 1)
            //    && (jj == 0 || jj == 1)) 
            //    || ((ii == 4 || ii == 5)
            //    && (jj == 4 || jj == 5))) {
				unevendots[i][j][3] = trans;
			} else {
				unevendots[i][j][3] = 0;
			}	
		}
	}

    index++;

    // grid
    for (int i = 0; i < TEX_SIZE; i++) {
        for (int j = 0; j < TEX_SIZE; j++) {	
		    grid[i][j][0] = colors->at(index % colors->size())->r;
			grid[i][j][1] = colors->at(index % colors->size())->g;
			grid[i][j][2] = colors->at(index % colors->size())->b;

            int ii = i % 8;
            int jj = j % 8;

			if (ii == 2 || ii == 3 || jj == 2 || jj == 3) {
				grid[i][j][3] = trans;
			} else {
				grid[i][j][3] = 0;
			}	
		}
	}

    index++;

    // slantstripes
    for (int i = 0; i < TEX_SIZE; i++) {
        for (int j = 0; j < TEX_SIZE; j++) {
		    slantstripes[i][j][0] = colors->at(index % colors->size())->r;
			slantstripes[i][j][1] = colors->at(index % colors->size())->g;
			slantstripes[i][j][2] = colors->at(index % colors->size())->b;

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

    index++;

    // zigzag
    for (int i = 0; i < TEX_SIZE; i++) {
        for (int j = 0; j < TEX_SIZE; j++) {
		    zigzag[i][j][0] = colors->at(index % colors->size())->r;
			zigzag[i][j][1] = colors->at(index % colors->size())->g;
			zigzag[i][j][2] = colors->at(index % colors->size())->b;

            int ii = i % 8;
            int jj = j % 8;

			if (((ii == 0 || ii == 4) && (jj == 0 || jj == 4))
                || ((ii == 1 || ii == 5) && (jj == 1 || jj == 7))
                || ((ii == 2 || ii == 6) && (jj == 2 || jj == 6))
                || ((ii == 3 || ii == 7) && (jj == 3 || jj == 5))) {
				zigzag[i][j][3] = trans;
			} else {
				zigzag[i][j][3] = 0;
			}	
		}
	}

    index++;

    // slantstripes
    for (int i = 0; i < TEX_SIZE; i++) {
        for (int j = 0; j < TEX_SIZE; j++) {	
		    slantgrid[i][j][0] = colors->at(index % colors->size())->r;
			slantgrid[i][j][1] = colors->at(index % colors->size())->g;
			slantgrid[i][j][2] = colors->at(index % colors->size())->b;

            int ii = i % 8;
            int jj = j % 8;

			if ((ii == jj) 
                || (ii == 7 && jj == 0)
                || (ii == 6 && jj == 1)
                || (ii == 5 && jj == 2)
                || (ii == 4 && jj == 3)
                || (ii == 3 && jj == 4)
                || (ii == 2 && jj == 5)
                || (ii == 1 && jj == 6)
                || (ii == 0 && jj == 7)) {
				slantgrid[i][j][3] = trans;
			} else {
				slantgrid[i][j][3] = 0;
			}	
		}
	}

    index++;

    // stripes
    for (int i = 0; i < TEX_SIZE; i++) {
        for (int j = 0; j < TEX_SIZE; j++) {
		    stripes[i][j][0] = colors->at(index % colors->size())->r;
			stripes[i][j][1] = colors->at(index % colors->size())->g;
			stripes[i][j][2] = colors->at(index % colors->size())->b;

            int jj = j % 8;

			if (jj == 0 || jj == 1 || jj == 4 || jj == 5) {
				stripes[i][j][3] = trans;
			} else {
				stripes[i][j][3] = 0;
			}	
		}
	}

    index++;

	glGenTextures(9, textures);

	std::cerr << "TEX 1 " << textures[1] << "\n";
    std::cerr << "TEX 2 " << textures[2] << "\n";

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_BLEND);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, dots);
	
    glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_BLEND); //GL_BLEND
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, wavy);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_BLEND);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, unevendots);

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_BLEND); //GL_BLEND
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, grid);
	
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_BLEND); //GL_BLEND
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, slantstripes);

    glBindTexture(GL_TEXTURE_2D, textures[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_BLEND); //GL_BLEND
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, zigzag);
	
    glBindTexture(GL_TEXTURE_2D, textures[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_BLEND); //GL_BLEND
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, slantgrid);

	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_BLEND); //GL_BLEND
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, stripes);
	
    glDisable(GL_TEXTURE_2D);
}