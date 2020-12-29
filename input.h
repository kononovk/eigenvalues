#pragma once
#include <string>
#include <fstream>
#include <exception>
#include <iostream>
#include <cmath>
#include <sstream>
double* process_input(int argc, char **argv, int& n, int& m, double& eps, int& k,  std::string& filename);
void fill_matrix(double *a, int n, int k, const std::string& filename);
void fill_with_formula(double *a, int n, int k);
void fill_with_file(double  *a, int n, const std::string& filename);
double f(int k, int n, int i, int j);