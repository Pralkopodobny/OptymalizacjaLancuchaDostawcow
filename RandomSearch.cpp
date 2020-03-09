//
// Created by marceli on 11.01.20.
//

#include "RandomSearch.h"
RandomSearch::RandomSearch(Problem *tProblem) {
    problem = tProblem;
    rng = CRandom();
}
RandomSearch::RandomSearch(Problem *tProblem, int tSeed) {
    problem = tProblem;
    rng = CRandom(tSeed);
}
std::vector<double> RandomSearch::generateSolution() {
    std::vector<double> solution;
    bool success_1 = false;
    bool success_2 = false;
    for (int i = 0; i < problem->solutionSize(); i++) {
        double temp_val = rng.nextDouble(problem->minRequiredVal(i,success_1), problem->maxRequiredVal(i,success_2));
        solution.push_back(temp_val);
        if (!success_1 || !success_2) std::cout << success_1 << success_2 << std::endl;
    }
    return solution;
}
double* RandomSearch::search(bool &tSuccess) {
    return search(DEFAULT_TIME,tSuccess);
}
double* RandomSearch::search(unsigned long long tSeconds, bool &tSuccess) {
    Timer timer(tSeconds);
    std::vector<double> solution = generateSolution();
    bool success = false;
    double quality = problem->getQualityAndFix(solution, success);
    if (!tSuccess) {
        quality = -DBL_MAX;
    }
    while (!timer.checkAlarm()) {
        std::vector<double> temp_solution = generateSolution();
        bool temp_success = false;
        double temp_quality = problem->getQualityAndFix(temp_solution, temp_success);
        if (temp_quality > quality and temp_success) {
            std::cout << temp_quality << " ";
            temp_success = true;
            solution = temp_solution;
            quality = temp_quality;
        }
    }
    double *out_solution = new double[problem->solutionSize()];
    std::copy(solution.begin(),solution.end(),out_solution);
    return out_solution;
}