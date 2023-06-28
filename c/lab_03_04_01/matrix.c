#include "matrix.h"
#include <math.h>

int input_matrix(matrix_t mat, size_t n)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            if (scanf("%d", &mat[i][j]) != 1)
                return ERROR_INCORRECT_ELEMENT;

    return EXIT_SUCCESS;
}

void print_matrix(matrix_t mat, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

void flip_el_in_hourglass(matrix_t mat, size_t n)
{
    for (size_t i = 0; i < n / 2; i++)
        for (size_t j = i; j < n - i; j++)
        {
            int tmp = mat[i][j];
            mat[i][j] = mat[n - 1 - i][j];
            mat[n - 1 - i][j] = tmp;
        }
}
