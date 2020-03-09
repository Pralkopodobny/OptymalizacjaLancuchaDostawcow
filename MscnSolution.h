//
// Created by marceli on 15.12.19.
//

#ifndef THEBIGESTPROJECT_MSCNSOLUTION_H
#define THEBIGESTPROJECT_MSCNSOLUTION_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Matrix.h"


const int DEF_TRIES = 3;
const bool MSCN_SOULUTION_FAILURE = false;
const bool MSCN_SOLUTION_SUCCESS = true;
struct MscnSolution {
    MscnSolution(double* tSolution, int tD, int tF, int tM, int tS, bool &tSuccess);

    explicit MscnSolution(std::string tFilename);
    MscnSolution(int tD, int tF, int tM, int tS ,Matrix tXd, Matrix tXf, Matrix tXm);
    int D, F, M, S;
    Matrix xd;
    Matrix xf;
    Matrix xm;
    std::string str() const;
    bool saveSoution(std::string tFilename) const;
    void getData(double *&tSolution);
    int size() { return xd.getTotalSize() + xf.getTotalSize() + xm.getTotalSize(); }
    bool fixMinMaxes(Matrix &tXdMin, Matrix &tXdMax,Matrix &tXfMin, Matrix &tXfMax,Matrix &tXmMin, Matrix &tXmMax);
    void makeSmaller(double tValue);
private:
    void loadSolution(std::string tFilename, int tTries);
    bool fixMinMax(Matrix &tMin, Matrix &tMax, Matrix &tX);

};

#endif //THEBIGESTPROJECT_MSCNSOLUTION_H
