#pragma once

#include <cstdint>
#include <cmath>

namespace diag {

/// details of implementation
namespace details {
static const double EPSILON = 1e-10;

class RotateMatrix {
public:
    RotateMatrix(std::size_t i_, std::size_t j_, double x_, double y_)
            : i(i_), j(j_), x(x_), y(y_) {
        sqrt = std::sqrt(x * x + y * y);
        cos = x / sqrt;
        sin = -y / sqrt;
    }

private:
    friend void matrix_rotate(double *M,
                              std::size_t size,
                              const RotateMatrix &Q);
    friend void rotate_matrix_mul_matrix(double *M,
                                         std::size_t size,
                                         const RotateMatrix &Q);
    std::size_t i, j;
    double x, y;
    double sqrt, cos, sin;
};

/**
 * @param: M - symmetrical matrix to multiply,
 *         size - size of M
 *         Q - rotate matrix to multiply
 */
inline void rotate_matrix_mul_matrix(double *M,
                                     std::size_t size,
                                     const RotateMatrix &Q) {
    for (std::size_t k = 0; k < size; ++k) {
        double tmp1 = M[Q.i * size + k];
        double tmp2 = M[Q.j * size + k];
        M[Q.i * size + k] = tmp1 * Q.cos - tmp2 * Q.sin;
        M[Q.j * size + k] = tmp1 * Q.sin + tmp2 * Q.cos;
    }
}

/**
 * Find similar matrix for symmetrical matrix:
 *      M = Q * M * Q^T, rotates basis with Q
 * @param: M - symmetrical matrix to multiply,
 *         size - size of M
 *         Q - rotate matrix to multiply
 */
inline void matrix_rotate(double *M, std::size_t size,
                          const RotateMatrix &Q) {
    rotate_matrix_mul_matrix(M, size, Q);
    /// without using symmetrical property
    /*
    for (std::size_t k = 0; k < size; ++k) {
            double tmp1 = M[k * size + Q.i],
                    tmp2 = M[k * size + Q.j];
            M[k * size + Q.i] = tmp1 * Q.cos - tmp2 * Q.sin;
            M[k * size + Q.j] = tmp1 * Q.sin + tmp2 * Q.cos;
        }
    */
    double Mii = M[Q.i * size + Q.i];
    double Mij = M[Q.i * size + Q.j];
    double Mji = M[Q.j * size + Q.i];
    double Mjj = M[Q.j * size + Q.j];

    M[Q.i * size + Q.i] = Mii * Q.cos - Mij * Q.sin;
    M[Q.i * size + Q.j] = Mii * Q.sin + Mij * Q.cos;
    M[Q.j * size + Q.i] = Mji * Q.cos - Mjj * Q.sin;
    M[Q.j * size + Q.j] = Mji * Q.sin + Mjj * Q.cos;
    for (std::size_t k = 0; k < size; ++k) {
        M[k * size + Q.i] = M[Q.i * size + k];
        M[k * size + Q.j] = M[Q.j * size + k];
    }
}
}

/**
 * Symmetrical matrix reduction to tridiagonalize form using rotations.
 * @param: M - symmetrical matrix to tridiagonalize,
 *         size - size of matrix
 */
inline void tridiagonalize(double *M, std::size_t size) {
    for (std::size_t k = 0; k < size - 2; ++k) {
        for (std::size_t j = k + 2; j < size; ++j) {
            double sum {};
            for (std::size_t counter = k + 1; counter < j; ++counter) {
                sum += M[counter * size + k] * M[counter * size + k];
            }
            double x = std::sqrt(sum);
            double y = M[j * size + k];
            if (std::fabs(x) > details::EPSILON || std::fabs(y) > details::EPSILON) {
                details::matrix_rotate(M, size, details::RotateMatrix {k + 1, j, x, y});
            }
        }
    }
}
}