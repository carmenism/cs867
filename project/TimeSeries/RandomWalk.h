#ifndef RANDOMWALK_H_
#define RANDOMWALK_H_

#include <vector>

#define NUM_CHOICES 3

class RandomWalk {
public:
    RandomWalk();
    ~RandomWalk();

    std::vector<float> *generate(int length, float start);
private:
    static int CHOICES[NUM_CHOICES];
};

#endif /* RANDOMWALK_H_ */