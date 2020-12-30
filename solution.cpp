#include "solution.h"
#include "tridiagonal.h"


int number_of_sign_changes(const double *a, int n, double lambda) {
    int res = 0;
    double li = a[0] - lambda;
    for (int i = 1; i < n; ++i) {
        double ui = a[(i - 1) * n + i] / li;
        double lambda_i = a[i * n + i - 1];
        if (li < 0) {
            res++;
        }
        li = a[i * n + i] - lambda_i * ui - lambda;
    }
    return res;
}


void solution(double *a, int n, double *x, double eps) {
    diag::tridiagonalize(a, n);
    double a_inf = 0;
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < n; ++j) {
            sum += fabs(a[i * n + j]);
        }
        a_inf = a_inf > sum ? a_inf : sum;
    }

    int k = 0;
    double ai = -a_inf, bi = a_inf;
    while (bi - ai > eps) {
        double ci_plus_1 = (ai + bi) / 2;
        if (number_of_sign_changes(a, n, ci_plus_1) < k + 1) {
            ai = ci_plus_1;
        } else {
            bi = ci_plus_1;
        }
    }
    x[k] = (ai + bi) / 2;
}