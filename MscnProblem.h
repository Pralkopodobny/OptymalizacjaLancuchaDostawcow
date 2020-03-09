//
// Created by marceli on 15.12.19.
//

#ifndef THEBIGESTPROJECT_MSCNPROBLEM_H
#define THEBIGESTPROJECT_MSCNPROBLEM_H

#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include "Problem.h"
#include "Matrix.h"
#include "MscnSolution.h"
#include "CRandom.h"
const int MSCN_PROBLEM_TRIES = 3;
const int MSCN_PROBLEM_DEF_SIZE = 4;
const int MSCN_PROBLEM_FIXING_TRIES = 10;
const bool MSCN_PROBLEM_SUCCESS = true;
const bool MSCN_PROBLEM_FAILURE = false;
const double MAX_SX = 10000;
const double MAX_P = 100;
const double MAX_COST = 20;
const double MAX_SINGLE_COST = 100;
class MscnProblem : public Problem{
public:
    MscnProblem();
    MscnProblem(std::string t_filename, bool &tSuccess);
    ~MscnProblem() = default;

    bool setD(int tD);
    bool setF(int tF);
    bool setM(int tM);
    bool setS(int tS);
    bool setCdElement(int tD, int tF, double tVal);
    bool setCfElement(int tF, int tM, double tVal);
    bool setCmElement(int tM, int tS, double tVal);
    bool setSdElement(int tD, double tVal);
    bool setSfElement(int tF, double tVal);
    bool setSmElement(int tM, double tVal);
    bool setSsElement(int tS, double tVal);
    bool setUdElement(int tD, double tVal);
    bool setUfElement(int tF, double tVal);
    bool setUmElement(int tM, double tVal);
    bool setPElement(int tS, double tVal);

    int getD() { return D; }
    int getF() { return F; }
    int getM() { return M; }
    int getS() { return S; }
    double getCdElement(int tD, int tF) { return cd.get(F, D); }
    double getCfElement(int tF, int tM) { return cf.get(M, F); }
    double getCmElement(int tM, int tS) { return cm.get(S,M); }
    double getSdElement(int tD) { return sd[tD]; }
    double getSfElement(int tF) { return sf[tF]; }
    double getSmElement(int tM) { return sm[tM]; }
    double getSsElement(int tS) { return ss[tS]; }
    double getUdElement(int tD) { return ud[tD]; }
    double getUfElement(int tF) { return uf[tF]; }
    double getUmElement(int tM) { return um[tM]; }
    double getPElement(int tS) { return p[tS]; }
    double getMinXdElement(int tD, int tF) { return xdmin.get(tF, tD); }
    double getMinXfElement(int tF, int tM) { return xfmin.get(tM, tF); }
    double getMinXmElement(int tM, int tS) { return xmmin.get(tS, tM); }
    double getMaxXdElement(int tD, int tF) { return xdmax.get(tF, tD); }
    double getMaxXfElement(int tF, int tM) { return xfmax.get(tM, tF); }
    double getMaxXmElement(int tM, int tS) { return xmmax.get(tS, tM); }

    double minRequiredVal(int tIndex, bool &tSuccess) override;
    double maxRequiredVal(int tIndex, bool &tSuccess) override;

    int solutionSize() override { return D*F + F*M + M*S; }

    std::string str();
    double getQuality (std::vector<double> &tSolution, bool &tSuccess) override ;
    double getQuality(double *tSolution,bool &tSuccess) override;
    double getQuality(MscnSolution &tSolution, bool &tSuccess);
    double getQualityAndFix(MscnSolution &tSolution, bool &tSuccess);
    double getQualityAndFix(double *tSolution,bool &tSuccess) override;
    double getQualityAndFix(std::vector<double> &tSolution, bool &tSuccess) override;
    bool constraintsSatisfied(double *tSolution) override;
    bool constraintsSatisfied(MscnSolution &tSolution);
    bool minMaxSatisfied(MscnSolution &tSolution);
    bool minMaxSatisfiedAndFixed(MscnSolution &tSolution);
    bool minMaxSatisfiedAndFixed(double* tSolution);
    bool constraintsSatisfiedAndFixed(MscnSolution &tSolution);
    bool constraintsSatisfiedAndFixed(double* tSolution) override;
    bool saveProblem(std::string tFilename);
    friend MscnProblem generateRandomProblem(int tSeed, int tD, int tF, int tM, int tS);
private:
    int D, F, M, S;
    std::vector<double> sd, sf, sm, ss;
    Matrix cd, cf, cm;
    std::vector<double> ud, uf, um, p;

    Matrix xdmin, xfmin, xmmin;
    Matrix xdmax, xfmax, xmmax;

    bool setMatrixElement(double tVal, Matrix & tMatrix, int tColumn, int tRow, int tMaxColumn, int tMaxRow);
    bool setVectorElement(double tVal, std::vector<double> &tVector, int tIndex, int tMaxIndex);
    void loadProblem(std::string tFilename, int tTries, bool &tSuccess);
    double measureKt(const MscnSolution& tSolution);
    double measureKu(const MscnSolution& tSolution);
    double measureP(const MscnSolution& tSolution);
};
MscnProblem generateRandomProblem(int tSeed, int tD, int tF, int tM, int tS);
#endif //THEBIGESTPROJECT_MSCNPROBLEM_H
/*
 * D - ilosc dostawcow
 * F - ilosc fabryk
 * M - ilosc centrow dystrybucji (magazynow)
 * S - ilosc sklepow
 * sd - macierz mocy produkcyjnych poszczegolnych dostawcow
 * sf - macierz mocy produkcyjnych poszczegolnych fabryk
 * sm - macierz pojemnosci poszczegolnych magazynow
 * ss - macierz zapotrzebowania dla rynku poszczegolnych sklepow
 * cd - macierz kosztu wytworzenia i przewiezienia surowca od dostawcy do fabryki
 * cf - macierz kosztu wytworzenia i przewiezienia surowca z fabryki do centrum dystrybucji
 * cm - macierz kosztu przechowania towaru w magazynie i przewiezienia go do sklepu
 * ud - macierz jednorazowych kosztow korzystania z uslug dostawcy
 * uf - macierz jednorazowych kosztow korzystania z uslug fabryk
 * um - macierz jednorazowych kosztow korzystania z uslug magazynow
 * p - macierz przychodow z odsprzedania produktu w sklepie
 * xdminmax - macierz dopuszczalnych wartosci xd (z wyniku)
 * xfminmax - macierz dopuszczalnych wartosci xf (z wyniku)
 * xmminmax - macierz dopuszczalnych wartosci xm (z wyniku)
 */