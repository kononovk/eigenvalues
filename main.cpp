
#include "iohandler.h"
#include "solution.h"
#include "accuracy.h"

#include <chrono>
#include <iostream>


int main(int argc, char **argv) {
    int n, m, k;
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
    std::cout << "trace accuracy = " << std::scientific << FindTraceAccuracy(a, x, n) << std::endl;
    std::cout << "strange accuracy = " << std::scientific << FindStrangeAccuracy(a, x, n) << std::endl;
    delete[] x;
    delete[] a;
    return 0;
}
