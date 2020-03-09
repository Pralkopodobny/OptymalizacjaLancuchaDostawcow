//
// Created by marceli on 11.01.20.
//

#ifndef THEBIGESTPROJECT_OPTIMIZER_H
#define THEBIGESTPROJECT_OPTIMIZER_H

#include "Problem.h"
const unsigned long long DEFAULT_TIME = 6;
class Optimizer {
    virtual double* search(bool &tSuccess) = 0;
    virtual double* search(unsigned long long tSeconds, bool &tSuccess) = 0;
};


#endif //THEBIGESTPROJECT_OPTIMIZER_H
