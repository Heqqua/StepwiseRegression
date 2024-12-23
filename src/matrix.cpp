#include "matrix.h"
#include <stdexcept>
#include <iostream>

// Умножение матриц
Matrix umat(const Matrix& A, const Matrix& B) {
    size_t n = A.size();
    size_t m = B[0].size();
    size_t p = B.size();

    if (A[0].size() != p) {
        throw std::invalid_argument("Матрицы не совпадают по размерности");
    }

    Matrix result(n, std::vector<double>(m, 0));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            for (size_t k = 0; k < p; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

Matrix omat(const Matrix& A) {
    size_t n = A.size();
    Matrix augmented = A;

    // Дополнительная единичная матрица для обратной матрицы
    for (size_t i = 0; i < n; ++i) {
        augmented[i].resize(2 * n, 0);
        augmented[i][i + n] = 1;
    }

    // Прямой ход Гаусса
    for (size_t i = 0; i < n; ++i) {
        if (augmented[i][i] == 0) {
            // Попробуйте обменять строки
            bool swapped = false;
            for (size_t j = i + 1; j < n; ++j) {
                if (augmented[j][i] != 0) {
                    std::swap(augmented[i], augmented[j]);
                    swapped = true;
                    break;
                }
            }
            if (!swapped) {
                throw std::invalid_argument("Единичная матрица не может быть обращена");
            }
        }

        for (size_t j = i + 1; j < n; ++j) {
            double ratio = augmented[j][i] / augmented[i][i];
            for (size_t k = 0; k < 2 * n; ++k) {
                augmented[j][k] -= ratio * augmented[i][k];
            }
        }
    }

    // Обратный ход Гаусса
    for (size_t i = n - 1; i != static_cast<size_t>(-1); --i) {
        double divisor = augmented[i][i];
        for (size_t j = 0; j < 2 * n; ++j) {
            augmented[i][j] /= divisor;
        }

        for (size_t j = 0; j < i; ++j) {
            double ratio = augmented[j][i];
            for (size_t k = 0; k < 2 * n; ++k) {
                augmented[j][k] -= ratio * augmented[i][k];
            }
        }
    }

    // Извлечение обратной матрицы
    Matrix inverse(n, std::vector<double>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            inverse[i][j] = augmented[i][j + n];
        }
    }

    return inverse;
}


