//
// Created by marceli on 20.01.20.
//

#ifndef THEBIGESTPROJECT_TRIVIALOPTIMIZER_H
#define THEBIGESTPROJECT_TRIVIALOPTIMIZER_H

#include "Optimizer.h"
const unsigned long long DEFAULT_N = 10;
class TrivialOptimizer : public Optimizer{
public:
    explicit TrivialOptimizer(Problem *tProblem);
    double* search(bool &tSuccess) override;
    double* search(unsigned long long tN, bool &tSuccess) override;
private:
    Problem *problem;
};


#endif //THEBIGESTPROJECT_TRIVIALOPTIMIZER_H
