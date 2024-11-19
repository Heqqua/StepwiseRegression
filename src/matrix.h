#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

typedef std::vector<std::vector<double>> Matrix;

Matrix umat(const Matrix& A, const Matrix& B);  // Умножение матриц
Matrix omat(const Matrix& A);                   // Обращение матрицы

#endif
