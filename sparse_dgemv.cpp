#include "all.h"

using namespace std;

void sparse_dgemv(int n, int elements, double *v, int *row, int *col,
                  double *val, double *u)
{
    int row_num, col_num;
    for (int i = 0; i < elements; i++)
    {
        row_num = row[i];
        col_num = col[i];
        v[row_num] += val[i] * u[col_num];
    }
}