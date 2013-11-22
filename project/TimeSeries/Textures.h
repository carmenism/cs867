#ifndef TEXTURES_H_
#define TEXTURES_H_

#define TEX_SIZE 32

#define SOLIDA 0
#define STRIPES 1
#define SOLIDB 2
#define SLANT 3

class PickColor;

#include <vector>

class Textures {
public: 
    Textures();
    ~Textures();

    unsigned int textures[4];

    PickColor *getColor(int i);
private:
	unsigned char stripes[TEX_SIZE][TEX_SIZE][4];
	unsigned char solidA[TEX_SIZE][TEX_SIZE][4];
	unsigned char slantstripes[TEX_SIZE][TEX_SIZE][4];
	unsigned char solidB[TEX_SIZE][TEX_SIZE][4];

    void init();

    std::vector<PickColor *> *colors;
};

#endif