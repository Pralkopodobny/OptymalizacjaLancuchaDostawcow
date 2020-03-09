//
// Created by marceli on 11.01.20.
//

#ifndef THEBIGESTPROJECT_RANDOMSEARCH_H
#define THEBIGESTPROJECT_RANDOMSEARCH_H

#include <iostream>
#include <cfloat>

#include "Optimizer.h"
#include "Problem.h"
#include "CRandom.h"
#include "MscnSolution.h"
#include "Timer.h"
class RandomSearch : public Optimizer {
public:
    explicit RandomSearch(Problem* tProblem);
    RandomSearch(Problem* tProblem, int tSeed);
    double* search(bool &tSuccess) override;
    double* search(unsigned long long tSeconds, bool &tSuccess) override;
private:
    std::vector<double> generateSolution();
    Problem* problem;
    CRandom rng;
};


#endif //THEBIGESTPROJECT_RANDOMSEARCH_H
