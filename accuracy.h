#pragma once
#include <iostream>
#include <cmath>

using namespace std;



/// Secondary functions (Accuracy)

inline double MatrixTrace(double *A, int n) {
    double trace = 0;
    for (int i = 0; i < n; i++) {
        trace += A[i * n + i];
    }
    return trace;
}

inline double VectorSum(double *X, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += X[i];
    }
    return sum;
}

inline double FindVectorNorm(double *X, int n) {
    double norm = 0;
    for (int i = 0; i < n; i++) {
        norm += X[i] * X[i];
    }
    return sqrt(norm);
}

inline double FindMatrixNorm(double *A, int n) {
    double norm = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            norm += A[i * n + j] * A[i * n + j];
        }
    }
    return sqrt(norm);
}

/// Output

inline void PrintMatrix(double *A, int l, int n, int m) {
    bool first_row = true;
    for (int i = 0; i < l && i < m; i++) {
        if (!first_row) {
            cout << "\n";
        }
        for (int j = 0; j < n && j < m; j++) {
            printf("%10.3e", A[i * n + j]);
        }
        first_row = false;
    }
}


/// Accuracy

inline double FindTraceAccuracy(double *A, double *X, int n) {
    return abs(MatrixTrace(A, n) - VectorSum(X, n));
}

inline double FindStrangeAccuracy(double *A, double *X, int n) {
    return abs(FindMatrixNorm(A, n) - FindVectorNorm(X, n));
}

