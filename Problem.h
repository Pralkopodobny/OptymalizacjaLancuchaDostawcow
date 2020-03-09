//
// Created by marceli on 11.01.20.
//

#ifndef THEBIGESTPROJECT_PROBLEM_H
#define THEBIGESTPROJECT_PROBLEM_H

#include "vector"

class Problem {
public:
    virtual double minRequiredVal(int tIndex, bool &tSuccess) = 0;
    virtual double maxRequiredVal(int tIndex, bool &tSuccess) = 0;
    virtual int solutionSize() = 0;
    virtual double getQuality(double *tSolution,bool &tSuccess) = 0;
    virtual double getQuality(std::vector<double> &tSolution, bool &tSuccess) = 0;
    virtual bool constraintsSatisfied(double *tSolution) = 0;
    virtual double getQualityAndFix(double *tSolution,bool &tSuccess) = 0;
    virtual double getQualityAndFix(std::vector<double> &tSolution, bool &tSuccess) = 0;
    virtual bool constraintsSatisfiedAndFixed(double *tSolution) = 0;


};


#endif //THEBIGESTPROJECT_PROBLEM_H
