#pragma once

#include <cstdint>
#include <cmath>
#include <iostream>
#include <iomanip>

#include <vector>

namespace diag {

class RotateMatrix {
public:
    RotateMatrix(std::size_t i_, std::size_t j_, double x_, double y_)
            : i(i_), j(j_), x(x_), y(y_) {
        sqrt = std::sqrt(x * x + y * y);
        cos = x / sqrt;
        sin = -y / sqrt;
    }

private:
    friend void iteration(double *M,
                          std::size_t size,
                          const RotateMatrix &Q);
    std::size_t i, j;
    double x, y;
    double sqrt, cos, sin;
};

inline void print(double *m, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cerr << std::fixed << std::setw(5) << std::setprecision(1) << m[i * n + j] + 1e-12 << ' ';
        }
        std::cerr << std::endl;
    }
    std::cerr << "=========================================" << std::endl;
}

/**
 * @param: M - matrix to multiply
 */
inline void rotate_matrix_mul_matrix(double *M,
                                     std::size_t size,
                                     double x, double y,
                                     int i, int j) {
    double sqrt_tmp = std::sqrt(x * x + y * y),
            cos = x / sqrt_tmp,
            sin = -y / sqrt_tmp;
    for (std::size_t k = 0; k < size; ++k) {
        double tmp1 = M[i * size + k];
        double tmp2 = M[j * size + k];
        M[i * size + k] = tmp1 * cos - tmp2 * sin;
        M[j * size + k] = tmp1 * sin + tmp2 * cos;
    }
}

/// TODO: change naming
inline void iteration(double *M, std::size_t size,
                      const RotateMatrix &Q) {
    rotate_matrix_mul_matrix(M, size, Q.x, Q.y, Q.i, Q.j);
    for (std::size_t k = 0; k < size; ++k) {
        double tmp1 = M[k * size + Q.i],
                tmp2 = M[k * size + Q.j];
        M[k * size + Q.i] = tmp1 * Q.cos - tmp2 * Q.sin;
        M[k * size + Q.j] = tmp1 * Q.sin + tmp2 * Q.cos;
    }
}

inline void tridiagonalize(double *a, std::size_t n) {
    double x, y;
    for (std::size_t k = 0; k < n - 2; ++k) {
        for (std::size_t j = k + 2; j < n; ++j) {
            double sum {};
            for (std::size_t counter = k + 1; counter < j; ++counter) {
                sum += a[counter * n + k] * a[counter * n + k];
            }
            x = std::sqrt(sum);
            y = a[j * n + k];
            if (x != 0 || y != 0) {
                iteration(a, n, RotateMatrix {k + 1, j, x, y});
            }
        }
    }
    print(a, n);
}

}