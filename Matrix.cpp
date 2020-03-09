//
// Created by marceli on 15.12.19.
//

#include "Matrix.h"
#include <iostream>
Matrix::Matrix() : Matrix(MATRIX_DEF_SIZE, MATRIX_DEF_SIZE) {}

Matrix::Matrix(Matrix const &tOther) {
    columns = tOther.columns;
    rows = tOther.rows;
    data = new double[tOther.getTotalSize()];
    std::copy(tOther.data, tOther.data + tOther.getTotalSize(), data);
}

Matrix::Matrix(double *tRawData, int tColumns, int tRows) {
    columns = tColumns;
    rows = tRows;
    data = new double[tColumns * tRows];
    std::copy(tRawData, tRawData + tColumns * tRows, data);
}

Matrix::Matrix(int tColumns, int tRows) {
    columns = tColumns;
    rows = tRows;
    data = new double[tColumns * tRows];
}
void Matrix::addToAll(double tValue) {
    for (int i = 0; i < getTotalSize(); i++) {
        data[i] += tValue;
    }
}

Matrix::Matrix(int tColumns) : Matrix(tColumns, tColumns) {}

Matrix::~Matrix() {
    delete[] data;
}

Matrix & Matrix::operator=(Matrix const &tOther) {
    if(this == &tOther) return *this;
    delete[] data;
    data = new double[tOther.getTotalSize()];
    std::copy(tOther.data, tOther.data + tOther.getTotalSize(), data);
    rows = tOther.rows;
    columns = tOther.columns;
    return *this;
}

double Matrix::get(int tColumns, int tRows) const {
        return data[tColumns + tRows * columns];
}

void Matrix::set(int tColumns, int tRows, double tVal) {
    data[tColumns + tRows * columns] = tVal;
}
std::string Matrix::str() const {
    if (columns < 1 || rows < 1) return "";
    std::stringstream out;
    for (int i = 0; i <columns * rows - 1; i++) {
        out << data[i] << " ";
    }
    out << data[rows * columns -1];
    return out.str();
};
std::string Matrix::strWithEndl() const {
    if (columns < 1 || rows < 1) return "";
    std::stringstream out;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            out << data[i * columns + j] << " ";
        }
        out << "\n";
    }
    return out.str();
}
double Matrix::rowSum(int tRow) const {
    double out = 0;
    for (int i = 0; i < columns; i++) {
        out += data[tRow * columns + i];
    }

    return out;
}

double Matrix::columnSum(int tColumn) const {
    double out = 0;
    for (int i = 0; i < rows; i++) {
        out += data[i * columns + tColumn];
    }

    return out;
}

void Matrix::resize(int tColumns, int tRows) {
    if (tColumns < 0 or tRows < 0) return;

    double *new_data = new double[tRows * tColumns];

    int min_rows = std::min(rows, tRows);
    int min_columns = std::min(columns, tColumns);
    for (int i = 0; i < min_rows; i++){
        for (int j = 0; j < min_columns; j++){
            std::copy(data+i*columns, data + i * columns + min_columns, new_data + i * tColumns);
        }
    }
    columns = tColumns;
    rows = tRows;
    delete[] data;
    data = new_data;
}
void Matrix::fill(double tVal) {
    for(int i = 0; i < getTotalSize(); i++) {
        data[i] = tVal;
    }
}
Matrix loadMatrix(std::ifstream &tStream, int tColumns, int tRows) {
    Matrix matrix(tColumns, tRows);
    double* temp_data = matrix.getData();
    for(int i = 0; i < matrix.getTotalSize(); i++) {
        tStream >> temp_data[i];
    }

    return matrix;
}
void loadMinMax(std::ifstream& tStream, int tColumns, int tRows, Matrix & tMin, Matrix & tMax){
    tMin = Matrix(tColumns,tRows);
    tMax = Matrix(tColumns,tRows);
    double* temp_min_data = tMin.getData();
    double* temp_max_data = tMax.getData();
    for(int i = 0; i < tMin.getTotalSize(); i++) {
        tStream >> temp_min_data[i];
        tStream >> temp_max_data[i];
    }
}
std::vector<double> loadVector(std::ifstream &tStream, int tSize) {
    std::vector<double> vector;
    vector.resize(tSize);

    for(int i = 0; i < vector.size(); i++) {
        tStream >> vector[i];
    }
    return vector;
}
std::string vectorToStr(std::vector<double> tVector){
    if (tVector.empty()) return "";
    std::stringstream out;
    for (int i = 0; i < tVector.size() - 1; i++) {
        out << tVector[i] << " ";
    }
    out << tVector[tVector.size() - 1];
    return out.str();
}
std::string vectorsToStr(std::vector<double> tFirst, std::vector<double> tSec){
    if (tFirst.empty() || tSec.empty() || tFirst.size() != tSec.size()) return "";

    std::stringstream out;
    for (int i = 0; i < tFirst.size() - 1; i++) {
        out << tFirst[i] << " " << tSec[i] << " ";
    }
    out << tFirst[tFirst.size() - 1] << " ";
    out << tSec[tSec.size() - 1];
    return out.str();
}
std::string matrixesToStr(Matrix & tFirst, Matrix & tSec){
    if (tFirst.empty() || tSec.empty() || tFirst.getTotalSize() != tSec.getTotalSize()) return "";
    std::stringstream out;
    double* first = tFirst.getData();
    double* sec = tSec.getData();
    for (int i = 0; i < tFirst.getTotalSize() - 1; i++) {
        out << first[i] << " " << sec[i] << " ";
    }
    out << first[tFirst.getTotalSize() - 1] << " ";
    out << sec[tSec.getTotalSize() - 1];
    return out.str();
}