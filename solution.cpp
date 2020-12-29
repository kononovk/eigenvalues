#include "solution.h"
void diagonal(double *a) {
    
}
int S(double *a, double lambda) {
    diagonal(a);
}
void solution(double *a, int n, double *x, double eps) {
    double a_inf = 0;
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < n; ++j) {
            sum += fabs(a[i* n + j]);
        }
        a_inf = a_inf > sum ? a_inf : sum;
    }

    int k = 0;
    double ai = -a_inf, bi = a_inf;
    while (bi - ai > eps) {
        double ci_plus_1 = (ai + bi) / 2;
        if (S(a, ci_plus_1) < k + 1) {
            ai = ci_plus_1;
        }
        else {
            bi = ci_plus_1;
        }
    }
    x[k] = (ai + bi) / 2;

}