#ifndef _PICKER_H
#define _PICKER_H

class Pickable;
class Experiment;

#include <vector>

class Picker {
public:
    Picker(Experiment *experiment);
    ~Picker() {}

    int pick(int x, int y);
private:
    Experiment *experiment;
};

#endif