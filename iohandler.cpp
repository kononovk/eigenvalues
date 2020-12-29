#include <fstream>
#include <exception>
#include <iostream>
#include <cmath>
#include <sstream>

#include"iohandler.h"

double f(int k, int n, int i, int j) {
    switch(k) {
        case 1:
            return n - (i > j ? i : j) + 1;
        case 2:
            if (i == j)
                return 2;
            if (abs(i - j) == 1)
                return -1;
            return 0;
        case 3:
            if (i == j && j < n)
                return 1;
            if (j == n)
                return i;
            if (i == n)
                return j;
            return 0;
        case 4:
            return 1 / static_cast<double>(i + j - 1);
        default:
            std::cerr << "k is invalid" << std::endl;
            throw std::runtime_error("k is invalid");
    }
}

void fill_with_file(double  *a, int n, const std::string& filename) {
    std::ifstream input(filename);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            input >> a[i * n + j];
        }
    }
    if (!input) {
        std::cerr << "Unable to open or read the file" << std::endl;
        throw std::runtime_error("unable to open or read the file\"");
    }
}

void fill_with_formula(double *a, int n, int k) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i * n + j] = f(k, n, i + 1, j + 1);
        }
    }
}

void fill_matrix(double *a, int n, int k, const std::string& filename) {
    if (k == 0) {
        fill_with_file(a, n, filename);
    } else {
        fill_with_formula(a, n, k);
    }
}

double* process_input(int argc, char **argv, int& n, int& m, double& eps, int& k,  std::string& filename) {
    std::string input_str;
    for (int i = 1; i < argc; ++i) {
        input_str += std::string(argv[i]) + ' ';
    }
    std::stringstream input(input_str);
    input >> n >> m >> eps >> k;
    auto *a = new double[n * n];
    if (k == 0) {
        input >> filename;
    }
    fill_matrix(a, n, k, filename);
    return a;
}

void output(int l, int n, int m, double *matrix) {
    std::cout << '\n';
    for (int i = 0; i < l && i < m; ++i) {
        for (int j = 0; j < n && j < m; ++j) {
            printf("%10.3e", matrix[i * n + j]);
        }
        std::cout << '\n';
    }
}
