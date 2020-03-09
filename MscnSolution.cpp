//
// Created by marceli on 15.12.19.
//

#include <climits>
#include "MscnSolution.h"

MscnSolution::MscnSolution(double *tSolution, int tD, int tF, int tM, int tS, bool &tSuccess) {
    tSuccess = MSCN_SOLUTION_SUCCESS;
    D = tD;
    F = tF;
    M = tM;
    S = tS;
    xd.resize(tF, tD);
    xf.resize(tM, tF);
    xm.resize(tS, tM);
    int index = 0;
    for(int i = 0; i < tD; i++) {
        for(int j = 0; j < tF; j++) {
            xd.set(j, i, tSolution[index]);
            index++;
        }
    }

    for(int i = 0; i < tF; i++) {
        for(int j = 0; j < tM; j++) {
            xf.set(j, i, tSolution[index]);
            index++;
        }
    }

    for(int i = 0; i < tM; i++) {
        for(int j = 0; j < tS; j++) {
            xm.set(j, i, tSolution[index]);
            index++;
        }
    }
}
MscnSolution::MscnSolution(int tD, int tF, int tM, int tS, Matrix tXd, Matrix tXf, Matrix tXm) {
    D = tD;
    F = tF;
    M = tM;
    S = tS;
    xd = tXd;
    xf = tXf;
    xm = tXm;
    xd.resize(tF,tD);
    xf.resize(tM,tF);
    xm.resize(tS,tM);
}
void MscnSolution::loadSolution(std::string tFilename, int tTries) {
    std::string ignore;
    std::ifstream file(tFilename);
    file >> ignore;
    file >> D;
    file >> ignore;
    file >> F;
    file >> ignore;
    file >> M;
    file >> ignore;
    file >> S;

    file >> ignore;
    xd = loadMatrix(file, F, D);
    file >> ignore;
    xf = loadMatrix(file, M, F);
    file >> ignore;
    xm = loadMatrix(file, S, M);
    if (file.fail()){
        if(tTries < 0) exit(EXIT_FAILURE);
        file.close();
        loadSolution(tFilename, tTries - 1);
    }
}
MscnSolution::MscnSolution(std::string tFilename) {
    loadSolution(std::move(tFilename), DEF_TRIES);
}
std::string MscnSolution::str() const {
    std::stringstream out;
    out << "D " << D << "\n";
    out << "F " << F << "\n";
    out << "M " << M << "\n";
    out << "S " << S << "\n";
    out << "xd\n" << xd.str() << "\n";
    out << "xf\n" << xf.str() << "\n";
    out << "xm\n" << xm.str() << "\n";
    return out.str();
}
bool MscnSolution::saveSoution(std::string tFilename) const {
    std::ofstream file(tFilename);
    if(!file.is_open()) return MSCN_SOULUTION_FAILURE;
    file << this->str();
    file.close();
    return MSCN_SOLUTION_SUCCESS;
}
void MscnSolution::getData(double *&tSolution) {
    std::copy(xd.getData(),xd.getData()+xd.getTotalSize(),tSolution);
    std::copy(xf.getData(),xf.getData()+xf.getTotalSize(),tSolution + xd.getTotalSize());
    std::copy(xm.getData(),xm.getData()+xm.getTotalSize(),tSolution + xd.getTotalSize() + xf.getTotalSize());
}
bool MscnSolution::fixMinMaxes(Matrix &tXdMin, Matrix &tXdMax, Matrix &tXfMin, Matrix &tXfMax, Matrix &tXmMin, Matrix &tXmMax) {
    if(!fixMinMax(tXdMin,tXdMax,xd)) return MSCN_SOULUTION_FAILURE;
    if(!fixMinMax(tXfMin,tXfMax,xf)) return MSCN_SOULUTION_FAILURE;
    return fixMinMax(tXmMin,tXmMax,xm);
}
bool MscnSolution::fixMinMax(Matrix &tMin, Matrix &tMax, Matrix &tX) {
    for (int i = 0; i < tX.getColumns(); i++) {
        for (int j  = 0; j < tX.getRows(); j++) {
            if (tMin.get(i,j) > tMax.get(i,j)) return MSCN_SOULUTION_FAILURE;
            if (tX.get(i,j) < tMin.get(i,j)) tX.set(i,j,tMin.get(i,j));
            if (tX.get(i,j) > tMax.get(i,j)) tX.set(i,j,tMax.get(i,j));
        }
    }
    return MSCN_SOLUTION_SUCCESS;
}
void MscnSolution::makeSmaller(double tValue) {
    xd.addToAll(-tValue);
    xf.addToAll(-tValue);
    xm.addToAll(-tValue);
}