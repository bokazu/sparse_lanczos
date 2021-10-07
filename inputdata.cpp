#include "all.h"

using namespace std;

void input_coo_data(string filename, int elements, int *row, int *col,
                    double *val)
{
    int row_n, col_n, n;
    ifstream sample_file(filename);
    if (!sample_file.is_open())
    {
        cerr << "Could not open the file - '" << filename << "'" << endl;
        exit(EXIT_FAILURE);
    }
    sample_file >> row_n >> col_n >> n;

    for (int i = 0; i < elements; i++)
    {
        sample_file >> row[i] >> col[i] >> val[i];
        // cout << "row[" << i << "] = " << row[i] << endl;
        // cout << "col[" << i << "] = " << col[i] << endl;
        // cout << "val[" << i << "] = " << val[i] << endl;
    }
}

void input_dns_data(string filename, int n, double *A)
{
    ifstream sample_file(filename);
    if (!sample_file.is_open())
    {
        cerr << "Could not open the file - '" << filename << "'" << endl;
        exit(EXIT_FAILURE);
    }

    int num = 0;
    double number;
    while (sample_file >> number)
    {
        A[num] = number;
        num++;
    }
    sample_file.close();
}

void get_matrix_size(string filename, int &n, int &elements)
{
    int row_n, col_n;
    ifstream sample_file(filename);
    if (!sample_file.is_open())
    {
        cerr << "Could not open the file - '" << filename << "'" << endl;
        exit(EXIT_FAILURE);
    }
    sample_file >> n >> col_n >> elements;
}