#include "CalcFunctions.h"
#include <limits>


std::vector<std::pair<double, double>> CalcFunc::GetEquationCoefficients(Matrix<double> &data){

    if(data.GetRowsCount() != 2){
        data.Transpose();
    }

    if(data.GetRowsCount() != 2){
        return std::vector<std::pair<double, double>>();
    }


    size_t n = data.GetColumnsCount();
    std::vector<std::pair<double, double>> coeffs;
    coeffs.reserve(n);

    for (size_t i = 0; i < n; ++i) {
        double y0 = data[0][i];
        double y1 = data[1][i];

        double b = y0;
        double k = y1 - y0;

        coeffs.emplace_back(k, b);
    }

    return coeffs;

}

std::vector<double> CalcFunc::GetLowerEnvelope(Matrix<double>& data, CalcFunc::X_Points_Dense points){
    if(data.GetRowsCount() != 2){
        data.Transpose();
    }

    if(data.GetRowsCount() != 2){
        return std::vector<double>();
    }


    std::vector<double> lower_envelope(points.x_dense.size(), std::numeric_limits<double>::max());
    for (int i = 0; i < data.GetColumnsCount(); i++) {
        double a0 = data[0][i];
        double a1 = data[1][i];
        for (int j = 0; j < points.x_dense.size(); j++) {
            double y = a0 + (a1 - a0) * points.x_dense[j];
            if (y < lower_envelope[j]) {
                lower_envelope[j] = y;
            }
        }
    }

    return lower_envelope;

}

std::vector<double> CalcFunc::GetUpperEnvelope(Matrix<double> &data, CalcFunc::X_Points_Dense points){
    if(data.GetRowsCount() != 2){
        data.Transpose();
    }

    if(data.GetRowsCount() != 2){
        return std::vector<double>();
    }

    std::vector<double> upper_envelope(points.x_dense.size(), std::numeric_limits<double>::lowest());
    for (int i = 0; i < data.GetRowsCount(); i++) {
        double a0 = data[0][i];
        double a1 = data[1][i];
        for (int j = 0; j < points.x_dense.size(); ++j) {
            double y = a0 + (a1 - a0) * points.x_dense[j];
            if (y > upper_envelope[j]) {
                upper_envelope[j] = y;
            }
        }
    }

    return upper_envelope;

}

CalcFunc::Point CalcFunc::GetOptium(CalcFunc::Optium optium, std::vector<double> envelope, CalcFunc::X_Points_Dense points){
    double nu, optium_x;
    if(optium == CalcFunc::Optium::Lower){
        auto max_it = std::max_element(envelope.begin(), envelope.end());
        nu = *max_it;
        optium_x = points.x_dense[std::distance(envelope.begin(), max_it)];
    }
    else{
        auto min_it = std::min_element(envelope.begin(), envelope.end());
        nu = *min_it;
        optium_x = points.x_dense[std::distance(envelope.begin(), min_it)];
    }
    return CalcFunc::Point(optium_x, nu);

}

double CalcFunc::Acrosing2x2(Matrix<double> &matrix){
    if(matrix.GetColumnsCount() != 2 && matrix.GetRowsCount() != 2){
        return 0.0;
    }

    return (matrix[0][0]+ matrix[1][1]) - (matrix[0][1]+matrix[1][0]);
}

std::pair<std::vector<double>, double> CalcFunc::SolveGame2x2(Matrix<double> &matrix, double det){

    double p1 = (matrix[1][1] - matrix[1][0]) / det;
    double p2 = 1.0 - p1;

    double q1 =  (matrix[1][1] - matrix[0][1]) / det;
    double q2 = 1.0 - q1;

    double nu = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) / det;

    return std::pair<std::vector<double>, double>(std::vector<double>({p1, p2, q1, q2}), nu);
}

double CalcFunc::GetNu(std::pair<std::vector<double>, double> solve){
    return solve.second;
}

std::pair<double, double> CalcFunc::GetX_star(std::pair<std::vector<double>, double> solve){
    return std::pair<double, double>(solve.first[0], solve.first[1]);

}
std::pair<double, double> CalcFunc::GetY_star(std::pair<std::vector<double>, double> solve){
    return std::pair<double, double>(solve.first[2], solve.first[3]);
}
