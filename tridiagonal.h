#pragma once

#include <cstdint>
#include <cmath>

namespace diag {

class RotateMatrix {
public:
    RotateMatrix(std::size_t i_, std::size_t j_, double x_, double y_)
            : i(i_), j(j_), x(x_), y(y_) {
        sqrt = std::sqrt(x * x + y * y);
    }

    double cos() const {
        return x / sqrt;
    }

    double sin() const {
        return -y / sqrt;
    }

private:
    std::size_t i, j;
    double x, y;
    double sqrt;
};

/**
 * @param: M - matrix to multiply
 */
inline void rotate_matrix_mul_matrix(double *M,
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

/// TODO: change naming
inline void iteration(double *M,
                      std::size_t size,
                      double x, double y,
                      std::size_t i, std::size_t j) {
    rotate_matrix_mul_matrix(M, size, x, y, i, j);

    double sqrt_tmp = std::sqrt(x * x + y * y),
            cos = x / sqrt_tmp,
            sin = -y / sqrt_tmp;

    auto Mii = M[i * size + i], Mij = M[i * size + j],
            Mjj = M[j * size + j], Mji = M[j * size + i];
    M[i * size + i] = Mii * cos + Mij * sin;
    M[j * size + i] = Mji * cos + Mjj * sin;
    M[i * size + j] = Mii * sin - Mij * cos;
    M[j * size + j] = Mjj * sin - Mjj * cos;
}

inline void diagonalize(double *a, std::size_t n) {
    /*    i + 1
        j + 3 -> n*/
    /*
     * A1 = ... * T24 * (T23 * A * T23^t) * T24^t * ...
     */
    for (std::size_t k = 0; k < n - 2; ++k) {
        for (std::size_t i = k + 2; i <= n; ++i) {
            double x {}, y {}, sum {};
            for (std::size_t j = 1; j < i; ++j) {
                sum += a[j * n + k] * a[j * n + k];
            }
            x = sqrt(sum);
            y = a[i * n + k];
            iteration(a, n, RotateMatrix{k + 1, i, x, y});
        }
    }
}

}