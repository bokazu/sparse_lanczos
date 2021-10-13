#define _CRT_SECURE_NO_WARNINGS /*fopen関数を呼び出すためのstdio.hをincludeする前にこれが必要。*/
#include "all.h"

using namespace std;

lapack_int LAPACKE_dsyev(int matrix_layout, char jobz, char uplo, lapack_int n,
                         double *a, lapack_int lda, double *w);

lapack_int LAPACKE_dstev(int matrix_order, char jobz, lapack_int n, double *d,
                         double *e, double *z, lapack_int ldz);

int main()
{
    int n, elements;
    // Setting Matrix(Column Major)
    /**************************Get COO DATA*******************************/
    string coo_filename("sample/coo_sample1.txt");
    ifstream coo_file(coo_filename);
    if (!coo_file.is_open())
    {
        cerr << "Could not open the file - '" << coo_filename << "'" << endl;
        return EXIT_FAILURE;
    }

    get_matrix_size(coo_filename, n, elements);

    int *row = new int[elements];
    int *col = new int[elements];
    double *val = new double[elements];

    // get data
    input_coo_data(coo_filename, elements, row, col, val);
    coo_file.close();
    /**********************************************************************/

    /****************************Get DNS DATA******************************/
    double *A = new double[n * n];
    string dns_filename("sample/dns_sample1.txt");
    ifstream dns_file(dns_filename);
    if (!dns_file.is_open())
    {
        cerr << "Could not open the file - '" << dns_filename << "'" << endl;
        return EXIT_FAILURE;
    }
    input_dns_data(dns_filename, n, A);
    // printmat_d(n, A);
    // printf("\n");
    dns_file.close();
    /*********************************************************************/

    double *eigen_value = new double[n];
    double *lw = new double[n];

    FILE *output_file, *lapack_file;
    output_file = fopen("output1.txt", "w");
    lapack_file = fopen("lapack_output1.txt", "w");
    if (output_file == NULL)
    {
        // fopen失敗
        // streamにstdout指定なので実質printfと同じ
        fprintf(stdout, "fopen error fp[%p]\n", output_file);
        return -1;
    }
    if (lapack_file == NULL)
    {
        // fopen失敗
        // streamにstdout指定なので実質printfと同じ
        fprintf(stdout, "fopen error fp[%p]\n", output_file);
        return -1;
    }

    /**************************Lanczos法使用&lapackで対角化***************************/
    sparse_lanczos(output_file, lapack_file, n, elements, row, col, val,
                   eigen_value);

    /********************行列そのものをlapackeに投げる。*****************/
    // printmat_d(n, A);
    LAPACKE_dsyev(LAPACK_COL_MAJOR, 'V', 'U', n, A, n, lw);
    fprintf(lapack_file, "LAPACKE's ANSWER\n");
    fprintf(lapack_file, "LAPACKE's eigen value = \n");
    fprintvec_d(lapack_file, n, lw);

    fprintf(lapack_file, "LAPACKE's eingen vector of groundstate\n");
    fprintmat_d(lapack_file, n, A);

    // fprintf(lapack_file, "LAPACKE's ANSWER\n");
    // fprintf(lapack_file, "eigen value = \n");
    // fprintvec_d(lapack_file, n, lw);

    //メモリの開放
    delete[] A;
    delete[] row;
    delete[] col;
    delete[] val;
    delete[] eigen_value;
    delete[] lw;
    fclose(output_file);
    fclose(lapack_file);
}