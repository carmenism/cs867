#include "RandomWalk.h"
#include <stdlib.h>
#include <time.h>

int RandomWalk::CHOICES[NUM_CHOICES] = { -1, 0, 1 };

RandomWalk::RandomWalk() {
    srand(time(NULL));
}

RandomWalk::~RandomWalk() {

}

std::vector<float> *RandomWalk::generate(int length, float start) {
    std::vector<float> *vec = new std::vector<float>();
    vec->push_back(start);

    for (int i = 1; i < length; i++) {
        int choice = CHOICES[rand() % NUM_CHOICES];
        vec->push_back(vec->back() + choice);
    }

    return vec;
}