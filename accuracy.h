#pragma once
#include <iostream>
#include <cmath>

using namespace std;

namespace accuracy {
/// details of implementation
namespace details {
inline double matrix_trace(const double *A, int n) {
    double trace = 0;
    for (int i = 0; i < n; i++) {
        trace += A[i * n + i];
    }
    return trace;
}

inline double vector_sum(const double *X, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += X[i];
    }
    return sum;
}

inline double vector_norm(const double *X, int n) {
    double norm = 0;
    for (int i = 0; i < n; i++) {
        norm += X[i] * X[i];
    }
    return sqrt(norm);
}

inline double matrix_norm(const double *A, int n) {
    double norm = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            norm += A[i * n + j] * A[i * n + j];
        }
    }
    return sqrt(norm);
}
}

/// Accuracy
inline double trace_accuracy(double *A, double *X, int n) {
    return abs(details::matrix_trace(A, n) - details::vector_sum(X, n));
}

inline double strange_accuracy(double *A, double *X, int n) {
    return abs(details::matrix_norm(A, n) - details::vector_norm(X, n));
}
}
