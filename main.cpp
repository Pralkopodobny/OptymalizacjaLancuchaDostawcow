#include <iostream>
#include "MscnProblem.h"
#include "RandomSearch.h"
#include "DiffEvol.h"
#include "TrivialOptimizer.h"
void test_2() {
    std::cout << "\nTEST_2\n";
    MscnProblem problem = generateRandomProblem(222334,3,2,3,2);//4 2 3 2
    RandomSearch search(&problem, 21378);//987246
    bool success = false;
    bool success_2 = false;
    double *raw_solution = search.search(6,success);
    MscnSolution solution(raw_solution,3,2,3,2,success_2); // 4 2 3 2

    std::cout << "PROBLEM:\n" << problem.str();
    std::cout << "\nSOLUTION:\n" << solution.str();
    std::cout << "\nQuality: " << problem.getQuality(solution, success) << " Poprawnosc: "  << success << std::endl;
    std::cout << "\nCHECK\n: " << problem.constraintsSatisfied(raw_solution);
    delete[] raw_solution;
}
void test_3() {
    std::cout << "\nTEST_3\n";
    MscnProblem problem = generateRandomProblem(222334,3,2,3,2);
    std::cout << "PROBLEM:\n" << problem.str();
    Population population(20,&problem, 987246);
    std::cout << "\nSOLUTIONS:\n";
    for (int i = 0 ; i < 4 ; i++) {
        bool success = false;
        std::cout << std::endl << "index: " << i << std::endl << MscnSolution(population.getIndividual(i).data(),3,2,3,2,success).str();
        std::cout << "\nQuality: " << problem.getQuality(population.getIndividual(i).data(),success) << " Poprawnosc: " << success;
    }
}
void test_5(){
    std::cout << "\nTEST_5\n";
    MscnProblem problem = generateRandomProblem(222334,3,2,3,2);
    DiffEvol evolution(&problem,20,987246);
    bool success = true;
    double* best_solution = evolution.search(100000,success);
    best_solution[1] = 2002;
    for (int i = 2; i < 7; i++) {
        best_solution[i] = 200000;
    }

    std::cout << "wypisuje popsute best solution\n";
    for (int i = 0; i < problem.solutionSize(); i++) {
        std::cout << best_solution[i] << " ";
    }
    std::cout << "\nTworze solution_class\n";
    MscnSolution solution_class(best_solution,3,2,3,2,success);
    double* converted_solution = new double[problem.solutionSize()];
    std::cout << "dokonuje konwersji i podmiany kilku wartosci\n";
    solution_class.getData(converted_solution);
    std::cout << "wypisuje converted_solution\n";
    for (int i = 0; i < solution_class.size(); i++) {
        std::cout << converted_solution[i] << " ";
    }
    std::cout << "\nnaprawiam solution_class i podmieniam converted_solution\n";
    std::cout << "powodzenie naprawy: " << problem.minMaxSatisfiedAndFixed(solution_class);
    solution_class.getData(converted_solution);
    std::cout << "\nwypisuje poprawione converted_solution o minMax\n";
    for (int i = 0; i < solution_class.size(); i++) {
        std::cout << converted_solution[i] << " ";
    }
    std::cout << "\nconstrainPoprawnosc:" << problem.constraintsSatisfied(solution_class);
    std::cout << "\nnaprawaTego: " << problem.constraintsSatisfiedAndFixed(solution_class);
    solution_class.getData(converted_solution);
    std::cout << "\ni wypisanie:\n";
    for (int i = 0; i < solution_class.size(); i++) {
        std::cout << converted_solution[i] << " ";
    }
    std::cout << "\npoprawne: " << problem.constraintsSatisfied(solution_class);
    std::cout << "\nnaprawaTego: " << problem.constraintsSatisfiedAndFixed(solution_class);
    solution_class.getData(converted_solution);
    std::cout << "\ni wypisanie:\n";
    for (int i = 0; i < solution_class.size(); i++) {
        std::cout << converted_solution[i] << " ";
    }
    std::cout << "\npoprawne: " << problem.constraintsSatisfied(solution_class);
    delete[] converted_solution;
}
void test_6(){
    std::cout << "\nTEST_6\n";
    MscnProblem problem = generateRandomProblem(222334,3,2,3,2);
    DiffEvol evolution(&problem,20,987246);
    bool success = true;
    double* best_solution = evolution.search(100000,success);
    best_solution[1] = 2002;
    for (int i = 2; i < 7; i++) {
        best_solution[i] = 200000;
    }
    std::vector<double> vector_solution;
    for (int i = 0; i < problem.solutionSize(); i++){
        vector_solution.push_back(best_solution[i]);
    }
    std::cout << "\nTworze solution_class:\n";
    MscnSolution solution_class(best_solution,3,2,3,2,success);
    std::cout << solution_class.str() << std::endl;
    std::cout << "Quality po naprawie: " << problem.getQualityAndFix(solution_class,success) << " poprawne: " << success
    << "\npoprawione:\n" << solution_class.str();
    std::cout << "\nwypisuje popsute best solution\n";
    for (int i = 0; i < problem.solutionSize(); i++) {
        std::cout << best_solution[i] << " ";
    }
    std::cout << "\ni naprawiam je\nquality po naprawie: " << problem.getQualityAndFix(best_solution,success)
    << " poprawne " << success << "\npoprawione\n";
    for (int i = 0; i < problem.solutionSize(); i++) {
        std::cout << best_solution[i] << " ";
    }
    std::cout <<"\nNie naprawione VectorSolution:\n";
    for (int i = 0; i < problem.solutionSize(); i++) {
        std::cout << vector_solution[i] << " ";
    }
    std::cout << "\ni naprawiam je\nquality po naprawie: " << problem.getQualityAndFix(vector_solution,success)
    << " poprawne " << success << "\npoprawione\n";
    for (int i = 0; i < problem.solutionSize(); i++) {
        std::cout << vector_solution[i] << " ";
    }
}
void test7(){
    std::cout << "\nTEST_7\n";
    MscnProblem problem = generateRandomProblem(222334,3,2,3,2);
    TrivialOptimizer optimizer(&problem);
    bool success = true;
    double* solution = optimizer.search(12,success);
    MscnSolution class_solution(solution,3,2,3,2,success);
    std::cout << class_solution.str();
}
int main() {
    //test_2();
    //test_3();
    //test_5();
    //test_6();
    //test7();
    return 0;
}
