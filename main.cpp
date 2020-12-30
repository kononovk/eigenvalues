/*
#include "iohandler.h"
#include "solution.h"
#include <chrono>
*/
#include <iostream>

#include "tridiagonal.h"

/*void print(double *m, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << m[i * n + j] << ' ';
        }
        std::cout << std::endl;
    }
}*/

int main(int argc, char **argv) {
/*    int n, m, k;
    double eps;
    std::string filename;
    auto a = process_input(argc, argv, n, m, eps, k, filename);
    output(n, n, m, a);
    auto *x = new double[n];

    auto start = std::chrono::steady_clock::now();
    solution(a, n, x, eps);
    auto finish = std::chrono::steady_clock::now();
    auto time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    std::cout << "milliseconds: " << time_taken.count() << std::endl;
    fill_matrix(a, n, k, filename);
    output(1, n, m, x);
    fill_matrix(a, n, k, filename);
    delete[] x;
    delete[] a;*/

    double matrix[] = {1, 2, 3, 4,
                       2, 6, 7, 8,
                       3, 7, 11, 12,
                       4, 8, 12, 16};
    diag::test();
    // diag::iteration(matrix, 4, diag::RotateMatrix {0, 1, 3, 4});

    // print(matrix, std::sqrt(sizeof(matrix) / sizeof(double)));

    diag::tridiagonalize(matrix, std::sqrt(sizeof(matrix) / sizeof(double)));
    diag::print(matrix, std::sqrt(sizeof(matrix) / sizeof(double)));

    return 0;
}
