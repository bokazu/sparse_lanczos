#include "all.h"
using namespace std;

void Initiailize_vec(int n, double *vec)
{
    for (int i = 0; i < n; i++)
    {
        vec[i] = 0.0;
    }
}

void Initiailize_vec(int n, int *vec)
{
    for (int i = 0; i < n; i++)
    {
        vec[i] = 0;
    }
}