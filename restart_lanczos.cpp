#include "all.h"

using namespace std;

lapack_int LAPACKE_dstev(int matrix_order, char jobz, lapack_int n, double *d,
                         double *e, double *z, lapack_int ldz);

void restart_lanczos(FILE *file, FILE *file_lapack, int n, int elements,
                     double **u, int *row, int *col, double *val,
                     double *eigen_value, double *v, double *alpha,
                     double *beta, double *eigenv_even, double *eigenv_odd,
                     double *eigenvec_even, double *eigenvec_odd,
                     double *eigenvec_ans, double *d, double *e)
{
    fprintf(file, "\n\n");
    fprintf(file, "Restart Lanczos\n");
    fprintf(file_lapack, "\n\n");
    fprintf(file_lapack, "restart Lanczos\n");
    // setting Initial vector & standarbilization
    for (int i = 0; i < n; i++)
    {
        Initiailize_vec(n, u[i]);
    }

    cblas_dcopy(n, eigenvec_ans, 1, u[0], 1);

    Initiailize_vec(n, eigen_value);
    Initiailize_vec(n, eigenv_even);
    Initiailize_vec(n, eigenv_odd);
    Initiailize_vec(n, eigenvec_even);
    Initiailize_vec(n, eigenvec_odd);
    Initiailize_vec(n, alpha);
    Initiailize_vec(n, beta);
    Initiailize_vec(n, eigenvec_ans);
    Initiailize_vec(n, d);
    Initiailize_vec(n, e);

    double beta_pow2 = 0;
    double eps = 1.0;
    int check = 1;  //"1" means eps > 1.0e-16. "0" means eps < 1.0e-16
    bool checker = true;
    int count = 0;

    for (int k = 0; k < n; k++)
    {
        Initiailize_vec(n, v);
        if (checker)
        {
            if (k == n - 1)
            {
                // calculate v[i] = Au0(k)
                sparse_dgemv(n, elements, v, row, col, val, u[k]);
                // calculate alpha & beta
                alpha[k] = cblas_ddot(n, v, 1, u[k], 1);
            }
            else
            {
                // calculate v[i] = Au0(k)
                sparse_dgemv(n, elements, v, row, col, val, u[k]);
                if (k == 0)
                {
                    alpha[k] = cblas_ddot(n, v, 1, u[k], 1);
                    cblas_daxpy(n, -alpha[k], u[k], 1, v, 1);
                    beta[k] = cblas_dnrm2(n, v, 1);
                    cblas_dscal(n, 1 / beta[k], v, 1);
                    cblas_dcopy(n, v, 1, u[k + 1], 1);
                    gso(n, k, u);
                    sdz(n, u[k + 1]);
                }
                else
                {
                    alpha[k] = cblas_ddot(n, v, 1, u[k], 1);
                    cblas_daxpy(n, -beta[k - 1], u[k - 1], 1, v, 1);
                    cblas_daxpy(n, -alpha[k], u[k], 1, v, 1);
                    beta[k] = cblas_dnrm2(n, v, 1);
                    cblas_dscal(n, 1 / beta[k], v, 1);
                    cblas_dcopy(n, v, 1, u[k + 1], 1);
                    gso(n, k, u);
                    sdz(n, u[k + 1]);
                }
            }

            // calculate eigenvalue of A(k)
            cblas_dcopy(n, alpha, 1, d, 1);
            cblas_dcopy(n, beta, 1, e, 1);
            if (k % 2 == 0)
            {
                if (k == n - 1)
                {
                    LAPACKE_dstev(LAPACK_ROW_MAJOR, 'N', n, d, e, eigenvec_even,
                                  n);
                    cblas_dcopy(n, d, 1, eigenv_even, 1);
                }
                else
                {
                    LAPACKE_dstev(LAPACK_ROW_MAJOR, 'N', k + 2, d, e,
                                  eigenvec_even, k + 2);
                    cblas_dcopy(n, d, 1, eigenv_even, 1);
                }
            }
            else
            {
                if (k == n - 1)
                {
                    LAPACKE_dstev(LAPACK_ROW_MAJOR, 'N', n, d, e, eigenvec_odd,
                                  n);
                    cblas_dcopy(n, d, 1, eigenv_odd, 1);
                }
                else
                {
                    LAPACKE_dstev(LAPACK_ROW_MAJOR, 'N', k + 2, d, e,
                                  eigenvec_odd, k + 2);
                    cblas_dcopy(n, d, 1, eigenv_odd, 1);
                }
            }

            // check errors each eigenvalue of groundstates
            if (k > 0)
            {
                eps = abs(eigenv_even[0] - eigenv_odd[0]);
                if (eps > 1.0e-15)
                {
                    checker = true;
                }
                else if (eps < 1.0e-15)
                {
                    checker = false;
                    cout << "break at count = " << k << endl;
                }
            }
            cout << "count = " << k << endl;
        }
        else
        {
            cout << "break at" << k << endl;
            break;
        }
        count = k;
    }
    if (count % 2 == 0)
    {
        cblas_dcopy(n, eigenv_even, 1, eigen_value, 1);
    }
    else
    {
        cblas_dcopy(n, eigenv_odd, 1, eigen_value, 1);
    }

    printf("re eigen value = \n");
    printvec_d(n, eigen_value);
    fprintf(file, "\n");
    fprintf(file, "\n");
    fprintf(file, "count = \n");
    fprintf(file, "%d\n", count);
    fprintf(file, "\n");
    fprintf(file, "\n");
    fprintf(file, "re eigen value = \n");
    fprintvec_d(file, n, eigen_value);
    cout << "count = " << count << endl;
    if (count == n - 1)
    {
        dst_ground_eigenvec(n, count + 1, eigen_value[0], alpha, beta, u,
                            eigenvec_ans);
    }
    else if (count < n - 1)
    {
        dst_ground_eigenvec(n, count + 1, eigen_value[0], alpha, beta, u,
                            eigenvec_ans);
    }

    fprintf(file, "re eigen vector\n");
    fprintvec_d(file, n, eigenvec_ans);
}