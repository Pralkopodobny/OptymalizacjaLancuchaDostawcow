//
// Created by marceli on 15.12.19.
//

#ifndef THEBIGESTPROJECT_MATRIX_H
#define THEBIGESTPROJECT_MATRIX_H

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
const int MATRIX_DEF_SIZE = 4;
const int MAX_SIZE = 1000;

class Matrix {
public:
    Matrix();
    Matrix(Matrix const &tOther);
    Matrix(double* tRawData, int tColumns, int tRows);
    Matrix(int tColumns, int tRows);
    Matrix(int tColumns);
    ~Matrix();
    Matrix & operator=(Matrix const &tOther);
    bool empty() { return getTotalSize() == 0; }
    double get(int tColumns, int tRows) const;
    void set(int tColumns, int tRows, double tVal);
    std::string str() const;
    std::string strWithEndl() const;
    double* getData(){return data;};
    int getTotalSize() const {return columns * rows;};
    double rowSum(int tRow) const;
    double columnSum(int tColumn) const;
    void resize(int tColumns, int tRows);
    void fill(double tVal);
    int getRows() { return rows; }
    int getColumns() { return columns; }
    void addToAll(double tValue);
private:
    int rows;
    int columns;
    double* data;
};

Matrix loadMatrix(std::ifstream& tStream, int tColumns, int tRows);
void loadMinMax(std::ifstream& tStream, int tColumns, int tRows, Matrix & tMin, Matrix & tMax);
std::vector<double> loadVector(std::ifstream& tStream, int tSize);
std::string vectorToStr(std::vector<double> tVector);
std::string vectorsToStr(std::vector<double> tFirst, std::vector<double> tSec);
std::string matrixesToStr(Matrix & tFirst, Matrix & tSec);
#endif //THEBIGESTPROJECT_MATRIX_H
