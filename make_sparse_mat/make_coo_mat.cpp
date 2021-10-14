#include "all.h"
using namespace std;

int main()
{
    int n = 1000;
    int *col = new int[n * n];
    int *row = new int[n * n];
    double *val = new double[n * n];
    double *A = new double[n * n];
    int index = 0;
    double mtmp;
    double prob = 0.3;

    FILE *coo_file, *dns_file;
    coo_file = fopen("../sample/coo_sample5.txt", "w");
    if (coo_file == NULL)
    {
        // fopen失敗
        // streamにstdout指定なので実質printfと同じ
        fprintf(stdout, "fopen error fp[%p]\n", coo_file);
    }

    dns_file = fopen("../sample/dns_sample5.txt", "w");
    if (dns_file == NULL)
    {
        // fopen失敗
        // streamにstdout指定なので実質printfと同じ
        fprintf(stdout, "fopen error fp[%p]\n", dns_file);
    }

    // make sparse matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            mtmp = (double)rand() / RAND_MAX;
            if (mtmp < prob)
            {
                row[index] = i;
                col[index] = j;
                val[index] = 1.0;
                A[n * i + j] = 1.0;
                index++;
                //対称成分も格納する
                if (i != j)
                {
                    row[index] = j;
                    col[index] = i;
                    val[index] = 1.0;
                    A[n * j + i] = 1.0;
                    index++;
                }
            }
        }
    }

    // output to file coo_sample1.txt
    fprintf(coo_file, "%d %d %d\n", n, n, index);
    for (int i = 0; i < index; ++i)
    {
        fprintf(coo_file, "%d %d %1.5f\n", row[i], col[i], val[i]);
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            fprintf(dns_file, "%1.5f ", A[n * i + j]);
        }
        fprintf(dns_file, "\n");
    }
    delete[] row;
    delete[] col;
    delete[] val;
    delete[] A;
}