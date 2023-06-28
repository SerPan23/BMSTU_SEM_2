#include "matrix.h"
#include <math.h>

int input_matrix(matrix_t mat, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            if (scanf("%d", &mat[i][j]) != 1)
                return ERROR_INCORRECT_ELEMENT;

    return EXIT_SUCCESS;
}

void print_matrix(matrix_t mat, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

int max_line_el(matrix_t mat, size_t m, size_t i)
{
    int max_el = mat[i][0];
    for (size_t j = 1; j < m; j++)
        if (max_el < mat[i][j])
            max_el = mat[i][j];
    
    return max_el;
}

void swap_lines(matrix_t mat, size_t m, size_t i_1, size_t i_2)
{
    for (size_t j = 0; j < m; j++)
    {
        int tmp = mat[i_1][j];
        mat[i_1][j] = mat[i_2][j];
        mat[i_2][j] = tmp;
    }
}

void sort_by_max_el(matrix_t mat, size_t n, size_t m)
{
    for (size_t j = 0; j < n; j++)
    {
        int flag = 0;
        for (size_t i = 0; i < n - 1 - j; i++)
            if (max_line_el(mat, m, i) < max_line_el(mat, m, i + 1))
            {
                swap_lines(mat, m, i, i + 1);
                flag = 1;
            }
        if (flag == 0)
            break;
    }
}
