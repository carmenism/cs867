#ifndef TEXTURES_H_
#define TEXTURES_H_

#define TEX_SIZE 32

#define DOTS 0
#define SLANTA 1
#define SOLIDA 2
#define STRIPES 3
#define SLANTB 4
#define SOLIDB 5

class PickColor;

#include <vector>

class Textures {
public: 
    Textures();
    ~Textures();

    unsigned int textures[6];

    PickColor *getColor(int i);
private:
	unsigned char dots[TEX_SIZE][TEX_SIZE][4];
	unsigned char unevendots[TEX_SIZE][TEX_SIZE][4];
	unsigned char stripes[TEX_SIZE][TEX_SIZE][4];
	unsigned char solidA[TEX_SIZE][TEX_SIZE][4];
	unsigned char slantstripes[TEX_SIZE][TEX_SIZE][4];
	unsigned char solidB[TEX_SIZE][TEX_SIZE][4];
	//unsigned char grid[TEX_SIZE][TEX_SIZE][4];
	//unsigned char slantgrid[TEX_SIZE][TEX_SIZE][4];
	//unsigned char zigzag[TEX_SIZE][TEX_SIZE][4];
	//unsigned char wavy[TEX_SIZE][TEX_SIZE][4];

    void init();

    std::vector<PickColor *> *colors;
};

#endif