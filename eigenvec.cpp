#include "all.h"

using namespace std;

void dst_ground_eigenvec(int n, int m, double groundstate_eigenv, double *alpha,
                         double *beta, double **u, double *eigenvec)
{
    double *x = new double[n];
    Initiailize_vec(n, x);
    double *eigen = new double[n];
    Initiailize_vec(n, eigen);
    double lambda = groundstate_eigenv;
    for (int i = 0; i < n; i++)
    {
        cout << "alpha[" << i << "] = " << alpha[i] << endl;
        cout << "beta[" << i << "] =" << beta[i] << endl;
    }

    x[0] = 1.0;
    x[1] = (lambda - alpha[0]) / beta[0];
    cout << "m=" << m << endl;
    cout << "lambda = " << lambda << endl;
    for (int i = 2; i < m; i++)
    {
        x[i] = ((lambda - alpha[i - 1]) * x[i - 1] - beta[i - 2] * x[i - 2]) /
               beta[i - 1];
    }

    for (int i = 0; i < m; i++)
    {
        cblas_daxpy(n, x[i], u[i], 1, eigen, 1);
    }

    sdz(n, eigen);
    cblas_dcopy(n, eigen, 1, eigenvec, 1);
    delete[] x;
    delete[] eigen;
}