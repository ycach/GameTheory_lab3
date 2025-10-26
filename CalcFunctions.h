#ifndef CALCFUNCTIONS_H
#define CALCFUNCTIONS_H

#include <vector>
#include "MatrixData/Matrix.h"

namespace CalcFunc {

const double ACCURACY = 1e-9;

enum Optium{
    Lower,
    Upper
};

struct X_Points_Dense{
    X_Points_Dense(int points = 500){
        x_dense = std::vector<double>(points);
        for (int i = 0; i < points; ++i) {
            x_dense[i] = static_cast<double>(i) / (points - 1);
        }
    }

    std::vector<double> x_dense;
};

struct Point{
    Point(double x, double y) : X(x), Y(y) {}
    Point() : X(0.0), Y(0.0) {}

    double X;
    double Y;
};

std::vector<std::pair<double, double>> GetEquationCoefficients(Matrix<double> &data);
std::vector<double> GetLowerEnvelope(Matrix<double> &data, X_Points_Dense points);
std::vector<double> GetUpperEnvelope(Matrix<double> &data, X_Points_Dense points);
Point GetOptium(CalcFunc::Optium optium, std::vector<double> envelope, CalcFunc::X_Points_Dense points);

double Acrosing2x2(Matrix<double> &matrix);
std::pair<std::vector<double>, double> SolveGame2x2(Matrix<double> &matrix, double det);
double GetNu(std::pair<std::vector<double>, double> solve);
std::pair<double, double> GetX_star(std::pair<std::vector<double>, double> solve);
std::pair<double, double> GetY_star(std::pair<std::vector<double>, double> solve);


}
#endif // CALCFUNCTIONS_H
