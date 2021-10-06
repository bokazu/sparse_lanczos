#include "all.h"

using namespace std;

void make_dns_mat(int n)
{
    double *A = new double[n * n];
    double mtmp;

    FILE *file;
    file = fopen("../sample/dns_sample1.txt", "w");
    if (file == NULL)
    {
        // fopen失敗
        // streamにstdout指定なので実質printfと同じ
        fprintf(stdout, "fopen error fp[%p]\n", file);
    }

    srand(time(NULL));
    for (int row_num = 0; row_num < n; ++row_num)
    {
        for (int col_num = row_num; col_num < n; ++col_num)
        {
            mtmp = (double)rand() / RAND_MAX;
            A[col_num + n * row_num] = mtmp;
            if (col_num != row_num)
            {
                A[row_num + n * col_num] = mtmp;
            }
        }
    }

    for (int row_num = 0; row_num < n; row_num++)
    {
        for (int col_num = 0; col_num < n; col_num++)
        {
            fprintf(file, "%2.10f ", A[n * row_num + col_num]);
        }
        fprintf(file, "\n");
    }
    delete[] A;
}