//
// Created by marceli on 04.01.20.
//

#include "CRandom.h"
CRandom::CRandom() {
    std::random_device rd;
    engine.seed(rd());
}
CRandom::CRandom(int tSeed) {
    engine.seed(tSeed);
}
void CRandom::seed(int tSeed) {
    engine.seed(tSeed);
}
int CRandom::nextInt(int tLowerBound, int tUpperBound) {
    std::uniform_int_distribution<> dis(tLowerBound, tUpperBound);
    return dis(engine);
}
int CRandom::nextInt(int tUpperBound) {
    return nextInt(0, tUpperBound);
}
double CRandom::nextDouble(double tLowerBound, double tUpperBound) {
    std::uniform_real_distribution<double> dis(tLowerBound, tUpperBound);
    return dis(engine);
}
double CRandom::nextDouble(double tUpperBound) {
    return nextDouble(0, tUpperBound);
}