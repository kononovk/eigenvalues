#pragma once

#include <cstdint>
#include <cmath>
#include <iostream>
#include <iomanip>

namespace diag {

class RotateMatrix {
public:
    RotateMatrix(std::size_t i_, std::size_t j_, double x_, double y_)
            : i(i_), j(j_), x(x_), y(y_) {
        sqrt = std::sqrt(x * x + y * y);
        cos = x / sqrt;
        sin = -y / sqrt;
    }

    void print() const {
        std::cout << i << ' ' << j << ' ' << x << ' ' << y << std::endl;
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
            std::cerr << std::fixed << std::setw(5) << std::setprecision(1) << m[i * n + j] << ' ';
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

    /*auto Mii = M[Q.i * size + Q.i], Mij = M[Q.i * size + Q.j],
            Mjj = M[Q.j * size + Q.j], Mji = M[Q.j * size + Q.i];
        2.2 6 7.4 8.8
        0.4 2 1.8 1.6
        3 7 11 12
        4 8 12 16

         3/5 -4/5
         4/5 3/5
                  1
                     1
    */
    // print(M, size);
    for (std::size_t k = 0; k < size; ++k) {
        double tmp1 = M[k * size + Q.i],
                tmp2 = M[k * size + Q.j];
        M[k * size + Q.i] = tmp1 * Q.cos - tmp2 * Q.sin;
        M[k * size + Q.j] = tmp1 * Q.sin + tmp2 * Q.cos;
    }
    // print(M, size);
}

inline void test() {
    double a[] {1, 2, 3, 4,
                2, 6, 7, 8,
                3, 7, 11, 12,
                4, 8, 12, 16};
    // rotate_matrix_mul_matrix(a, 4, 3, 4, 0, 1);
    iteration(a, 4, RotateMatrix {0, 1, 3, 4});
    // print(a, 4);
}

inline void tridiagonalize(double *a, std::size_t n) {
    for (std::size_t k = 0; k < n - 2; ++k) {
        // T12 T13 T14 ... T15
        for (std::size_t j = k + 2; j < n; ++j) {
            double sum {};
            for (std::size_t counter = k + 1; counter < j; ++counter) {
                sum += a[counter * n + k] * a[counter * n + k];
            }
            double x = {sqrt(sum)};
            double y = {a[j * n + k]};
            iteration(a, n, RotateMatrix {k + 1, j, x, y});
        }
    }
}

}