//
// Created by marceli on 11.01.20.
//

#include "DiffEvol.h"
std::vector<double> Population::generateProperCorrectIndividual() {
    bool success = false;
    std::vector<double> solution;
    while (!success) {
        solution = std::vector<double>();
        bool success_temp_1 = false;
        bool success_temp_2 = false;
        for (int i = 0; i < problem->solutionSize(); i++) {
            double temp_val = rng.nextDouble(problem->minRequiredVal(i, success_temp_1),problem->maxRequiredVal(i, success_temp_2));
            solution.push_back(temp_val);
            if (!success_temp_1 || !success_temp_2) {
                std::cout << "Impossible!";
                exit(EXIT_FAILURE);
            }
        }
        success = problem->constraintsSatisfiedAndFixed(solution.data());
    }
    return solution;
}
Population::Population(int tSize, Problem *tProblem) {
    rng = CRandom();
    problem =tProblem;
    population = std::vector<std::vector<double>>();
    initialize(tSize);
}
Population::Population(int tSize, Problem *tProblem, int seed) {
    rng = CRandom(seed);
    problem = tProblem;
    population = std::vector<std::vector<double>>();
    initialize(tSize);
}
void Population::initialize(int tSize) {
    for (int i = 0; i < tSize; i++){
        population.push_back(generateProperCorrectIndividual());
    }
}
std::vector<double>& Population::getIndividual(int tIndex) {
    return population[tIndex];
}
std::vector<double>& Population::getRandomIndividual() {
    return population[rng.nextInt((int)population.size()-1)];
}
std::vector<double>& Population::operator[](int i) {
    return population[i];
}
DiffEvol::DiffEvol(Problem *tProblem, int tPopulationSize, int tSeed, double tCrossProbability, double tDiffWeight):population(tPopulationSize,tProblem,tSeed) {
    rng = CRandom(tSeed);
    problem = tProblem;
    individualSize = tProblem->solutionSize();
    quality_counter = 0;
    cross_probability = tCrossProbability;
    diff_weight = tDiffWeight;

}
DiffEvol::DiffEvol(int tPopulationSize, Problem *tProblem, double tCrossProbability, double tDiffWeight):population(tPopulationSize,tProblem) {
    rng =CRandom();
    problem = tProblem;
    individualSize = tProblem->solutionSize();
    quality_counter = 0;
    cross_probability = tCrossProbability;
    diff_weight = tDiffWeight;
}
bool DiffEvol::individualsAreDifferent(std::vector<double> *tInd1, std::vector<double> *tInd2, std::vector<double> *tInd3,
                                      std::vector<double> *tInd4) {
    std::vector<std::vector<double>*> tab;
    tab.push_back(tInd1);
    tab.push_back(tInd2);
    tab.push_back(tInd3);
    tab.push_back(tInd4);
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4 ; j++){
            if (tab[i] == tab[j])
                return false;
        }
    }
    return true;
}
void DiffEvol::iteration() {
    for (int i = 0; i < population.size(); i++) {
        std::vector<double> *base_ind = &population.getRandomIndividual();
        std::vector<double> *add_ind0 = &population.getRandomIndividual();
        std::vector<double> *add_ind1 = &population.getRandomIndividual();
        std::vector<double> new_ind(individualSize);
        if (individualsAreDifferent(&population[i],base_ind,add_ind0,add_ind1)) {
            for (int gene_offset = 0; gene_offset < individualSize; gene_offset++){
                if (rng.nextDouble(1) < cross_probability) {
                    new_ind[gene_offset] = (*base_ind)[gene_offset] +
                                           diff_weight * ((*add_ind0)[gene_offset] - (*add_ind1)[gene_offset]);
                }
                else {
                    new_ind[gene_offset] = population[i][gene_offset];
                }
            }
            bool success = false;
            quality_counter+=2;
            if (problem->getQuality(population[i],success) < problem->getQuality(new_ind.data(),success) && success){
                population[i] = new_ind;
            }
        }
    }
}

double* DiffEvol::search(unsigned long long tSeconds, bool &tSuccess) {
    Timer timer(tSeconds);
    while (!timer.checkAlarm()){
        iteration();
    }
    int index_of_best = 0;
    bool success = false;
    double quality_of_best = problem->getQuality(population[0].data(),success);
    for (int i = 0; i < population.size(); i++) {
        double temp_quality = problem->getQualityAndFix(population[i].data(),success);
            if(!success) std::cout << "Impossible!\n";
        if (temp_quality > quality_of_best) {
            index_of_best = i;
            quality_of_best = temp_quality;
        }
    }
    double* solution = new double[individualSize];
    std::copy(population[index_of_best].begin(), population[index_of_best].end(), solution);
    return solution;
}
double* DiffEvol::search(bool &tSuccess) {
    return search(DEFAULT_TIME,tSuccess);
}
