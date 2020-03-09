//
// Created by marceli on 11.01.20.
//

#ifndef THEBIGESTPROJECT_DIFFEVOL_H
#define THEBIGESTPROJECT_DIFFEVOL_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include "Problem.h"
#include "CRandom.h"
#include "Optimizer.h"
#include "Timer.h"
const double CROSS_PROB = 0.12;
const double DIFF_WEIGHT = 0.23;

class Population {
public:
    Population(int tSize, Problem *tProblem);
    Population(int tSize, Problem *tProblem, int seed);
    std::vector<double> & getRandomIndividual();
    std::vector<double> & getIndividual(int tIndex);
    std::vector<double> & operator[](int i);
    int size() { return population.size(); }
private:
    std::vector<double> generateProperCorrectIndividual();
    void initialize(int tSize);

    std::vector<std::vector<double>> population;
    Problem *problem;
    CRandom rng;

};
class DiffEvol : public Optimizer{
public:
    DiffEvol(Problem *tProblem, int tPopulationSize, int tSeed, double tCrossProbability = CROSS_PROB, double tDiffWeight = DIFF_WEIGHT );
    DiffEvol(int tPopulationSize, Problem *tProblem, double tCrossProbability = CROSS_PROB, double tDiffWeight = DIFF_WEIGHT);
    double* search(bool &tSuccess) override;
    double* search(unsigned long long tSeconds, bool &tSuccess) override;
private:
    bool individualsAreDifferent(std::vector<double> *tInd1, std::vector<double> *tInd2, std::vector<double> *tInd3,
            std::vector<double> *tInd4);
    void iteration();
    unsigned long long quality_counter;
    int individualSize;
    double diff_weight;
    double cross_probability;
    Population population;
    Problem *problem;
    CRandom rng;
};


#endif //THEBIGESTPROJECT_DIFFEVOL_H
