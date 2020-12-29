#include "iohandler.h"
#include "solution.h"
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
    fill_matrix(a, n, k, filename);
    delete[] x;
    delete[] a;


    return 0;
}
