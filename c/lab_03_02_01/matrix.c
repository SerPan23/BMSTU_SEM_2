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

int sum_digits(int num)
{
    int sum = 0, tmp = abs(num);
    while (tmp > 0)
    {
        sum += tmp % 10;
        tmp /= 10;
    }
    return sum;
}

void find_min_digits_sum_el_i_j(matrix_t mat, size_t n, size_t m, size_t *min_i, size_t *min_j)
{
    *min_i = 0;
    *min_j = 0;
    int min_sum = sum_digits(mat[0][0]);
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
        {
            int tmp = sum_digits(mat[i][j]);
            if (tmp < min_sum)
            {
                min_sum = tmp;
                *min_i = i;
                *min_j = j;
            }
        }
}

void del_row_and_col(matrix_t mat, size_t *n, size_t *m, size_t del_i, size_t del_j)
{
    int row_count = 0, col_count = 0;
    for (size_t i = 0; i < *n; i++)
    {
        if (i == del_i)
        {
            row_count++;
            continue;
        }

        col_count = 0;

        for (size_t j = 0; j < *m; j++)
        {
            if (j == del_j)
            {
                col_count++;
                continue;
            }
            mat[i - row_count][j - col_count] = mat[i][j];
        }
    }
    --(*n);
    --(*m);
}
