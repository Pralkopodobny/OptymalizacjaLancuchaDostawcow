//
// Created by marceli on 20.01.20.
//

#include "TrivialOptimizer.h"
TrivialOptimizer::TrivialOptimizer(Problem *tProblem) {
    problem = tProblem;
}
double * TrivialOptimizer::search(unsigned long long tN,bool &tSuccess) {
    double *solution = new double[problem->solutionSize()];
    for (int i = 0; i < problem->solutionSize(); i++){
        solution[i] = (double)(i%tN);
    }
    tSuccess = problem->constraintsSatisfied(solution);
    return solution;
}
double * TrivialOptimizer::search(bool &tSuccess) {
    return search(DEFAULT_N,tSuccess);
}