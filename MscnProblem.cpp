//
// Created by marceli on 15.12.19.
//

#include "MscnProblem.h"

MscnProblem::MscnProblem() {
    D = MSCN_PROBLEM_DEF_SIZE;
    F = MSCN_PROBLEM_DEF_SIZE;
    M = MSCN_PROBLEM_DEF_SIZE;
    S = MSCN_PROBLEM_DEF_SIZE;

    sd.resize(MSCN_PROBLEM_DEF_SIZE);
    sf.resize(MSCN_PROBLEM_DEF_SIZE);
    sm.resize(MSCN_PROBLEM_DEF_SIZE);
    ss.resize(MSCN_PROBLEM_DEF_SIZE);

    ud.resize(MSCN_PROBLEM_DEF_SIZE);
    uf.resize(MSCN_PROBLEM_DEF_SIZE);
    um.resize(MSCN_PROBLEM_DEF_SIZE);

    cd.resize(MSCN_PROBLEM_DEF_SIZE, MSCN_PROBLEM_DEF_SIZE);
    cf.resize(MSCN_PROBLEM_DEF_SIZE, MSCN_PROBLEM_DEF_SIZE);
    cm.resize(MSCN_PROBLEM_DEF_SIZE, MSCN_PROBLEM_DEF_SIZE);


    xdmin.resize(MSCN_PROBLEM_DEF_SIZE, MSCN_PROBLEM_DEF_SIZE);
    xfmin.resize(MSCN_PROBLEM_DEF_SIZE, MSCN_PROBLEM_DEF_SIZE);
    xmmin.resize(MSCN_PROBLEM_DEF_SIZE, MSCN_PROBLEM_DEF_SIZE);
    xdmax.resize(MSCN_PROBLEM_DEF_SIZE, MSCN_PROBLEM_DEF_SIZE);
    xfmax.resize(MSCN_PROBLEM_DEF_SIZE, MSCN_PROBLEM_DEF_SIZE);
    xmmax.resize(MSCN_PROBLEM_DEF_SIZE, MSCN_PROBLEM_DEF_SIZE);
}
void MscnProblem::loadProblem(std::string tFilename, int tTries, bool &tSuccess){
    tSuccess = MSCN_PROBLEM_SUCCESS;
    std::string ignore;
    std::ifstream file(tFilename);
    /*
    const auto temp = std::ctype<char>::classic_table();
    std::vector<std::ctype<char>::mask> bar(temp, temp + std::ctype<char>::table_size);
    bar[';'] |= std::ctype_base::space;
    file.imbue(std::locale(file.getloc(), new std::ctype<char>(&bar[0])));
     */
    file >> ignore; if(ignore != "D") tSuccess = MSCN_PROBLEM_FAILURE;
    file >> D;
    file >> ignore; if(ignore != "F") tSuccess = MSCN_PROBLEM_FAILURE;
    file >> F;
    file >> ignore; if(ignore != "M") tSuccess = MSCN_PROBLEM_FAILURE;
    file >> M;
    file >> ignore; if(ignore != "S") tSuccess = MSCN_PROBLEM_FAILURE;
    file >> S;
    setD(D);
    setF(F);
    setM(M);
    setS(S);

    file >> ignore; if(ignore != "sd") tSuccess = MSCN_PROBLEM_FAILURE;
    sd = loadVector(file, D);
    file >> ignore; if(ignore != "sf") tSuccess = MSCN_PROBLEM_FAILURE;
    sf = loadVector(file, F);
    file >> ignore; if(ignore != "sm") tSuccess = MSCN_PROBLEM_FAILURE;
    sm = loadVector(file, M);
    file >> ignore; if(ignore != "ss") tSuccess = MSCN_PROBLEM_FAILURE;
    ss = loadVector(file, S);
    file >> ignore; if(ignore != "cd") tSuccess = MSCN_PROBLEM_FAILURE;
    cd = loadMatrix(file, F, D);
    file >> ignore; if(ignore != "cf") tSuccess = MSCN_PROBLEM_FAILURE;
    cf = loadMatrix(file, M, F);
    file >> ignore; if(ignore != "cm") tSuccess = MSCN_PROBLEM_FAILURE;
    cm = loadMatrix(file, S, M);
    file >> ignore; if(ignore != "ud") tSuccess = MSCN_PROBLEM_FAILURE;
    ud = loadVector(file, D);
    file >> ignore; if(ignore != "uf") tSuccess = MSCN_PROBLEM_FAILURE;
    uf = loadVector(file, F);
    file >> ignore; if(ignore != "um") tSuccess = MSCN_PROBLEM_FAILURE;
    um = loadVector(file, M);
    file >> ignore; if(ignore != "p") tSuccess = MSCN_PROBLEM_FAILURE;
    p = loadVector(file, S);
    file >> ignore; if(ignore != "xdminmax") tSuccess = MSCN_PROBLEM_FAILURE;
    loadMinMax(file,F,D,xdmin,xdmax);
    file >> ignore; if(ignore != "xfminmax") tSuccess = MSCN_PROBLEM_FAILURE;
    loadMinMax(file,M,F,xfmin,xfmax);
    file >> ignore; if(ignore != "xmminmax") tSuccess = MSCN_PROBLEM_FAILURE;
    loadMinMax(file,S,M,xmmin,xmmax);
    if (file.fail()) {
        if (tTries <= 0) tSuccess = MSCN_PROBLEM_FAILURE;
        file.close();
        loadProblem(tFilename, tTries - 1,tSuccess);
    }
}
MscnProblem::MscnProblem(std::string t_filename, bool &tSuccess) {
    loadProblem(std::move(t_filename), MSCN_PROBLEM_TRIES,tSuccess);
}

bool MscnProblem::setD(int tD) {
    if (tD < 0) return MSCN_PROBLEM_FAILURE;
    D = tD;
    cd.resize(F, D);
    sd.resize(D);
    ud.resize(D);
    xdmin.resize(F,D);
    xdmax.resize(F,D);
    return MSCN_PROBLEM_SUCCESS;
}

bool MscnProblem::setF(int tF) {
    if (tF < 0) return MSCN_PROBLEM_FAILURE;
    F = tF;
    cd.resize(F, D);
    cf.resize(M, F);
    sf.resize(F);
    uf.resize(F);
    xdmin.resize(F,D);
    xdmax.resize(F,D);
    xfmin.resize(M,F);
    xfmax.resize(M,F);
    return MSCN_PROBLEM_SUCCESS;
}

bool MscnProblem::setM(int tM) {
    if (tM < 0) return MSCN_PROBLEM_FAILURE;
    M = tM;
    cf.resize(M, F);
    cm.resize(S, M);
    sm.resize(M);
    um.resize(M);
    xfmin.resize(M,F);
    xfmax.resize(M,F);
    xmmin.resize(S,M);
    xmmax.resize(S,M);
    return MSCN_PROBLEM_SUCCESS;
}

bool MscnProblem::setS(int tS) {
    if (tS < 0) return MSCN_PROBLEM_FAILURE;
    S = tS;
    cm.resize(S, M);
    ss.resize(S);
    p.resize(S);
    xmmin.resize(S,M);
    xmmax.resize(S,M);
    return MSCN_PROBLEM_SUCCESS;
}
bool MscnProblem::setCdElement(int tD, int tF, double tVal) {
    return setMatrixElement(tVal, cd, tF, tD, F - 1, D - 1);
}

bool MscnProblem::setCfElement(int tF, int tM, double tVal) {
    return setMatrixElement(tVal, cf, tM, tF, M - 1, F - 1);
}

bool MscnProblem::setCmElement(int tM, int tS, double tVal) {
    return setMatrixElement(tVal, cm, tS, tM, S - 1, M - 1);
}

bool MscnProblem::setSdElement(int tD, double tVal) {
    return setVectorElement(tVal, sd, tD, D - 1);
}

bool MscnProblem::setSfElement(int tF, double tVal) {
    return setVectorElement(tVal, sf, tF, F - 1);
}

bool MscnProblem::setSmElement(int tM, double tVal) {
    return setVectorElement(tVal, sm, tM, M - 1);
}

bool MscnProblem::setSsElement(int tS, double tVal) {
    return setVectorElement(tVal, ss, tS, S - 1);
}

bool MscnProblem::setUdElement(int tD, double tVal) {
    return setVectorElement(tVal, ud, tD, D - 1);
}

bool MscnProblem::setUfElement(int tF, double tVal) {
    return setVectorElement(tVal, uf, tF, F - 1);
}

bool MscnProblem::setUmElement(int tM, double tVal) {
    return setVectorElement(tVal, um, tM, M - 1);
}

bool MscnProblem::setPElement(int tS, double tVal) {
    return setVectorElement(tVal, p, tS, S - 1);
}


double MscnProblem::getQuality(MscnSolution &tSolution, bool &tSuccess) {
    tSuccess = constraintsSatisfied(tSolution);
    return measureP(tSolution) - measureKt(tSolution) - measureKu(tSolution);
}
double MscnProblem::getQualityAndFix(MscnSolution &tSolution, bool &tSuccess) {
    tSuccess = constraintsSatisfiedAndFixed(tSolution);
    return measureP(tSolution) - measureKt(tSolution) - measureKu(tSolution);
}
double MscnProblem::getQualityAndFix(double *tSolution, bool &tSuccess) {
    MscnSolution temp_solution(tSolution,D,F,M,S,tSuccess);
    if(!tSuccess) return getQuality(temp_solution,tSuccess);
    tSuccess = constraintsSatisfiedAndFixed(temp_solution);
    temp_solution.getData(tSolution);
    return measureP(temp_solution) - measureKt(temp_solution) - measureKu(temp_solution);
}
double MscnProblem::getQualityAndFix(std::vector<double> &tSolution, bool &tSuccess) {
    double * temp_solution = new double[tSolution.size()];
    std::copy(tSolution.begin(),tSolution.end(),temp_solution);
    double quality = getQualityAndFix(temp_solution, tSuccess);
    //std::copy(temp_solution,temp_solution+tSolution.size(),tSolution);

    for (int i =0 ;i < tSolution.size();i++){
        tSolution[i] = temp_solution[i];
    }
    delete[] temp_solution;
    return quality;
}
double MscnProblem::getQuality(double *tSolution, bool &t_success) {
    if (tSolution == NULL){
        t_success = MSCN_PROBLEM_FAILURE;
        return MSCN_PROBLEM_FAILURE;
    }
    MscnSolution solution(tSolution, D, F, M, S, t_success);
    return getQuality(solution, t_success);
}
double MscnProblem::getQuality(std::vector<double> &tSolution, bool &tSuccess) {
    return getQuality(tSolution.data(), tSuccess);
}
bool MscnProblem::constraintsSatisfied(MscnSolution &tSolution) {
    if (!minMaxSatisfied(tSolution)) return MSCN_PROBLEM_FAILURE;
    for (int i = 0; i < D; i++) {
        if (tSolution.xd.rowSum(i) > sd[i]) return MSCN_PROBLEM_FAILURE;
    }
    for (int i = 0; i < F; i++) {
        if (tSolution.xf.rowSum(i) > sf[i]) return MSCN_PROBLEM_FAILURE;
    }
    for (int i = 0; i < M; i++) {
        if (tSolution.xm.rowSum(i) > sm[i]) return MSCN_PROBLEM_FAILURE;
    }
    for (int i = 0; i < S; i++) {
        if (tSolution.xm.columnSum(i) > ss[i]) return MSCN_PROBLEM_FAILURE;
    }
    for (int i = 0; i < F; i++) {
        if (tSolution.xd.columnSum(i) < tSolution.xf.rowSum(i)) return MSCN_PROBLEM_FAILURE;
    }
    for (int i = 0; i < M; i++) {
        if (tSolution.xf.columnSum(i) < tSolution.xm.rowSum(i)) return MSCN_PROBLEM_FAILURE;
    }
    return MSCN_PROBLEM_SUCCESS;
}
bool MscnProblem::constraintsSatisfiedAndFixed(MscnSolution &tSolution){
    if (!minMaxSatisfiedAndFixed(tSolution)) return MSCN_PROBLEM_FAILURE;
    for (int j = 0; j < MSCN_PROBLEM_FIXING_TRIES; j++) {
        for (int i = 0; i < D; i++) {
            if (tSolution.xd.rowSum(i) > sd[i]) tSolution.makeSmaller(-(sd[i] - tSolution.xd.rowSum(i))/D);
        }
        for (int i = 0; i < F; i++) {
            if (tSolution.xf.rowSum(i) > sf[i]) tSolution.makeSmaller(-(sf[i] - tSolution.xf.rowSum(i))/F);
        }
        for (int i = 0; i < M; i++) {
            if (tSolution.xm.rowSum(i) > sm[i]) tSolution.makeSmaller(-(sm[i] - tSolution.xm.rowSum(i))/M);
        }
        for (int i = 0; i < S; i++) {
            if (tSolution.xm.columnSum(i) > ss[i]) tSolution.makeSmaller(-(ss[i] - tSolution.xm.columnSum(i))/S);
        }
        minMaxSatisfiedAndFixed(tSolution);
        if (constraintsSatisfied(tSolution)) return MSCN_SOLUTION_SUCCESS;
    }
    return MSCN_PROBLEM_FAILURE;
}
bool MscnProblem::constraintsSatisfiedAndFixed(double *tSolution) {
    bool success = false;
    MscnSolution temp_solution(tSolution,D,F,M,S,success);
    if(!success) return MSCN_PROBLEM_FAILURE;
    success = constraintsSatisfiedAndFixed(temp_solution);
    temp_solution.getData(tSolution);
    return success;
}
bool MscnProblem::constraintsSatisfied(double *tSolution) {
    if (tSolution == NULL) return MSCN_PROBLEM_FAILURE;
    bool success;
    MscnSolution sol(tSolution, D, F, M, S, success);
    if (!success) return MSCN_PROBLEM_FAILURE;
    return constraintsSatisfied(sol);

}
bool MscnProblem::minMaxSatisfied(MscnSolution &tSolution) {
    for (int i = 0; i < tSolution.xd.getTotalSize(); i++) {
        if (tSolution.xd.getData()[i] < xdmin.getData()[i] || tSolution.xd.getData()[i] > xdmax.getData()[i])
            return MSCN_PROBLEM_FAILURE;
    }
    for (int i = 0; i < tSolution.xf.getTotalSize(); i++) {
        if (tSolution.xf.getData()[i] < xfmin.getData()[i] || tSolution.xf.getData()[i] > xfmax.getData()[i])
            return MSCN_PROBLEM_FAILURE;
    }
    for (int i = 0; i < tSolution.xm.getTotalSize(); i++) {
        if (tSolution.xm.getData()[i] < xmmin.getData()[i] || tSolution.xm.getData()[i] > xmmax.getData()[i])
            return MSCN_PROBLEM_FAILURE;
    }

    return MSCN_PROBLEM_SUCCESS;
}
bool MscnProblem::minMaxSatisfiedAndFixed(MscnSolution &tSolution) {
    return tSolution.fixMinMaxes(xdmin,xdmax,xfmin,xfmax,xmmin,xmmax);
}
bool MscnProblem::minMaxSatisfiedAndFixed(double *tSolution) {
    bool success = false;
    MscnSolution temp_solution(tSolution,D,F,M,S,success);
    if(!success) return MSCN_PROBLEM_FAILURE;
    success = temp_solution.fixMinMaxes(xdmin,xdmax,xfmin,xfmax,xmmin,xmmax);
    temp_solution.getData(tSolution);
    return success;
}
double MscnProblem::measureKt(const MscnSolution &tSolution) {
    double out = 0;

    for (int i = 0; i < F; i++) {
        for (int j = 0; j < D; j++) {
            out += cd.get(i, j) * tSolution.xd.get(i, j);
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < F; j++) {
            out += cf.get(i, j) * tSolution.xf.get(i, j);
        }
    }

    for (int i = 0; i < S; i++) {
        for (int j = 0; j < M; j++) {
            out += cm.get(i, j) * tSolution.xm.get(i, j);
        }
    }

    return out;
}

double MscnProblem::measureKu(const MscnSolution &tSolution) {
    double out = 0;

    for (int i = 0; i < D; i++) {
        if (tSolution.xd.rowSum(i) > 0) out += ud[i];
    }

    for (int i = 0; i < F; i++) {
        if (tSolution.xf.rowSum(i) > 0) out += uf[i];
    }

    for (int i = 0; i < M; i++) {
        if (tSolution.xm.rowSum(i) > 0) out += um[i];
    }

    return out;
}

double MscnProblem::measureP(const MscnSolution &tSolution) {
    double out = 0;

    for (int i = 0; i < S; i++) {
        for (int j = 0; j < M; j++) {
            out += p[i] * tSolution.xm.get(i, j);
        }
    }

    return out;
}
bool MscnProblem::setMatrixElement(double tVal, Matrix &tMatrix, int tColumn, int tRow, int tMaxColumn, int tMaxRow){
    if(tColumn < 0 || tRow < 0 || tColumn > tMaxColumn || tRow > tMaxRow || tVal < 0)
        return MSCN_PROBLEM_FAILURE;
    tMatrix.set(tColumn, tRow, tVal);
    return MSCN_PROBLEM_SUCCESS;
}
bool MscnProblem::setVectorElement(double tVal, std::vector<double> &tVector, int tIndex, int tMaxIndex){
    if (tIndex < 0 || tIndex > tMaxIndex) return MSCN_PROBLEM_FAILURE;
    tVector[tIndex] = tVal;
    return MSCN_PROBLEM_SUCCESS;
}
std::string MscnProblem::str() {
    std::stringstream s_out;
    s_out << "D " << D << "\n";
    s_out << "F " << F << "\n";
    s_out << "M " << M << "\n";
    s_out << "S " << S << "\n";
    s_out << "sd\n";
    s_out << vectorToStr(sd) << "\n";
    s_out <<"sf\n";
    s_out << vectorToStr(sf) << "\n";
    s_out <<"sm\n";
    s_out << vectorToStr(sm) << "\n";
    s_out << "ss\n";
    s_out << vectorToStr(ss) << "\n";
    s_out << "cd\n";
    s_out << cd.str() << "\n";
    s_out << "cf\n";
    s_out << cf.str() << "\n";
    s_out << "cm\n";
    s_out << cm.str() << "\n";
    s_out << "ud\n";
    s_out << vectorToStr(ud) << "\n";
    s_out << "uf\n";
    s_out << vectorToStr(uf) << "\n";
    s_out << "um\n";
    s_out << vectorToStr(um) << "\n";
    s_out << "p\n";
    s_out << vectorToStr(p) << "\n";
    s_out << "xdminmax\n";
    s_out << matrixesToStr(xdmin, xdmax) << "\n";
    s_out << "xfminmax\n";
    s_out << matrixesToStr(xfmin, xfmax)<< "\n";;
    s_out << "xmminmax\n";
    s_out << matrixesToStr(xmmin, xmmax)<< "\n";;
    return s_out.str();
}
double MscnProblem::minRequiredVal(int tIndex, bool &tSuccess) {
    tSuccess = MSCN_PROBLEM_SUCCESS;
    if (tIndex < D * F) {
        return xdmin.getData()[tIndex];
    }
    if (tIndex < D * F + F * M) {
        tIndex -= D * F;
        return xfmin.getData()[tIndex];
    }
    if (tIndex < D * F + F * M + M * S) {
        tIndex -= D * F;
        tIndex -= F * M;
        return xmmin.getData()[tIndex];
    }
    tSuccess = MSCN_PROBLEM_FAILURE;
    return 0;
}
double MscnProblem::maxRequiredVal(int tIndex, bool &tSuccess) {
    tSuccess = MSCN_PROBLEM_SUCCESS;
    if (tIndex < D * F) {
        return xdmax.getData()[tIndex];
    }
    if (tIndex < D * F + F * M) {
        tIndex -= D * F;
        return xfmax.getData()[tIndex];
    }
    if (tIndex < D * F + F * M + M * S) {
        tIndex -= D * F;
        tIndex -= F * M;
        return xmmax.getData()[tIndex];
    }
    tSuccess = MSCN_PROBLEM_FAILURE;
    return 0;
}
bool MscnProblem::saveProblem(std::string tFilename) {
    std::ofstream file(tFilename);
    if(!file.is_open()) return MSCN_PROBLEM_FAILURE;
    file << this->str();
    file.close();
    return MSCN_PROBLEM_SUCCESS;
}
MscnProblem generateRandomProblem(int tSeed, int tD, int tF, int tM, int tS){
    CRandom rng(tSeed);
    MscnProblem problem;
    tD = std::max(1,tD);
    tF = std::max(1,tF);
    tM = std::max(1,tM);
    tS = std::max(1,tS);
    problem.setD(tD);
    problem.setF(tF);
    problem.setM(tM);
    problem.setS(tS);
    for (int i = 0; i < tD; i++){
        problem.setUdElement(i,rng.nextDouble(MAX_SINGLE_COST));
        problem.setSdElement(i,rng.nextDouble(MAX_SX));
    }
    for (int i = 0; i < tF; i++){
        problem.setUfElement(i,rng.nextDouble(MAX_SINGLE_COST));
        problem.setSfElement(i,rng.nextDouble(MAX_SX));
    }
    for (int i = 0; i < tM; i++){
        problem.setUmElement(i,rng.nextDouble(MAX_SINGLE_COST));
        problem.setSmElement(i,rng.nextDouble(MAX_SX));
    }
    for (int i = 0; i < tS; i++){
        problem.setPElement(i,rng.nextDouble(MAX_P));
        problem.setSsElement(i,rng.nextDouble(MAX_SX));
    }
    for (int i = 0; i < tD; i++){
        for (int j = 0; j < tF; j++) {
            problem.setCdElement(i,j,rng.nextDouble(MAX_COST));
        }
    }
    for (int i = 0; i < tF; i++){
        for (int j = 0; j < tM; j++){
            problem.setCfElement(i,j,rng.nextDouble(MAX_COST));
        }
    }
    for (int i = 0; i < tM; i++){
        for (int j = 0; j < tS; j++){
            problem.setCmElement(i,j,rng.nextDouble(MAX_COST));
        }
    }
    problem.xdmin.fill(0);
    problem.xfmin.fill(0);
    problem.xmmin.fill(0);
    for (int i = 0; i < tD; i++){
        for (int j = 0; j < tF; j++){
            problem.xdmax.set(j,i,std::min(problem.sd[i],problem.sf[j]));
        }
    }
    for (int i = 0; i < tF; i++){
        for (int j = 0; j < tM; j++){
            problem.xfmax.set(j,i,std::min(problem.sf[i],problem.sm[j]));
        }
    }
    for (int i = 0; i < tM; i++){
        for (int j = 0; j < tS; j++){
            problem.xmmax.set(j,i,std::min(problem.sm[i],problem.ss[j]));
        }
    }
    return problem;
}