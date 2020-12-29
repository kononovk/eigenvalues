#pragma once

#include <cstdint>
#include <cmath>

namespace diag {
/**
 * @param: T - rotate matrix
 */
inline void rotate_matrix_mul_matrix(double *T,
                                 double *M,
                                 std::size_t size,
                                 double x, double y,
                                 int i, int j) {
    /// matrix mul vector
    double sqrt_tmp = std::sqrt(x * x + y * y),
            cos = x / sqrt_tmp,
            sin = -y / sqrt_tmp;
    for (std::size_t k = 0; k < size; ++k) {
        double tmp1 = M[k * size + i],
                tmp2 = M[k * size + j];
        M[k * size + i] = tmp1 * cos - tmp2 * sin;
        M[k * size + j] = tmp1 * sin + tmp2 * cos;
    }
}

/// TODO change naming
inline void govno_function(double *M,
                           double x, double y,
                           std::size_t i, std::size_t j) {

}

inline void diagonal(double *a) {

}

}