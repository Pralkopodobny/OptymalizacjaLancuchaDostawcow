//
// Created by marceli on 04.01.20.
//

#ifndef THEBIGESTPROJECT_CRANDOM_H
#define THEBIGESTPROJECT_CRANDOM_H

#include <random>

class CRandom {
public:
    CRandom();
    CRandom(int tSeed);
    void seed(int tSeed);
    int nextInt(int tUpperBound);
    int nextInt(int tLowerBound, int tUpperBound);
    double nextDouble(double tUpperBound);
    double nextDouble(double tLowerBound, double tUpperBound);
private:
    std::default_random_engine engine;
};


#endif //THEBIGESTPROJECT_CRANDOM_H
