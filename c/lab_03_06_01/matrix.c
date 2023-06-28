#include "matrix.h"
#include <math.h>

void print_matrix(matrix_t mat, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

void fill_matrix_in_spiral(matrix_t mat, size_t n)
{
    int val = 1;
    ptrdiff_t len = n, pos = 0;
    while (val <= (int)(n * n))
    {
        for (ptrdiff_t i = pos; i < len; i++)
            mat[pos][i] = val++;

        for (ptrdiff_t i = pos + 1; i < len; i++)
            mat[i][len - 1] = val++;

        for (ptrdiff_t i = len - 2; i >= pos; i--)
            mat[len - 1][i] = val++;

        for (ptrdiff_t i = len - 2; i > pos; i--)
            mat[i][pos] = val++;

        pos++;
        len--;
    }
}
