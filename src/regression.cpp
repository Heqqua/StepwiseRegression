#include "regression.h"
#include "matrix.h"
#include <cmath>
#include <stdexcept>

std::vector<double> performRegression(const std::vector<double>& x, const std::vector<double>& y, int M) {
    size_t N = x.size();
    if (y.size() != N) {
        throw std::invalid_argument("Vectors x and y must have the same length.");
    }

    // Формирование матрицы X (для степенных полиномов)
    Matrix X(N, std::vector<double>(M + 1));
    for (size_t i = 0; i < N; ++i) {
        for (int j = 0; j <= M; ++j) {
            X[i][j] = std::pow(x[i], j);
        }
    }

    // Матрица Y
    Matrix Y(N, std::vector<double>(1));
    for (size_t i = 0; i < N; ++i) {
        Y[i][0] = y[i];
    }

    // Нахождение обратной матрицы для X^T * X
    Matrix XT = omat(X);  // Обращаем X
    Matrix XTX = umat(XT, X);  // Умножаем X^T * X
    Matrix XTX_inv = omat(XTX);  // Обратная матрица для X^T * X

    // Нахождение коэффициентов полинома
    Matrix B = umat(XTX_inv, umat(XT, Y));  // Коэффициенты полинома

    // Сборка результата
    std::vector<double> coefficients(M + 1);
    for (int i = 0; i <= M; ++i) {
        coefficients[i] = B[i][0];
    }

    return coefficients;
}

