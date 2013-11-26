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

    unsigned int textures[15];

    PickColor *getColor(int i);
private:
	unsigned char grid[TEX_SIZE][TEX_SIZE][4];

    void init();

    std::vector<PickColor *> *colors;

    void makeTexture(int index);

    void makeStripes(unsigned char arr[TEX_SIZE][TEX_SIZE][4], PickColor *color, unsigned char trans);
    
    void makeSlantedStripes(unsigned char arr[TEX_SIZE][TEX_SIZE][4], PickColor *color, unsigned char trans);
    
    void makeSolid(unsigned char arr[TEX_SIZE][TEX_SIZE][4], PickColor *color, unsigned char trans);

    void registerTexture(unsigned char arr[TEX_SIZE][TEX_SIZE][4], int index);
};

#endif