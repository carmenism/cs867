#define CIRC 1
#define SQUARE 2
#define SPHERE 3

#include <vector>

class Symbol;

class SymbolSet
{
public:
	SymbolSet();
	void drawSymbol(int i);
	void draw();
    int getTargetIndex();
    bool advanceTrial();
    bool getTargetPresence();
private:
    std::vector<Symbol *> symbols;

	int shapes[10][10];
    float xPos[10][10];
    float yPos[10][10];

    //int targetIndex;
    int trialNumber;
    
    std::vector<bool> targetPresence;
    
    void initSymbols();

    void initializeTargetPresence();
    void setPositions();
    void setShapes();
    void initializeTrial();
};

inline int getRandom(int low, int high) {
    return std::rand() % (high - low + 1) + low;
}