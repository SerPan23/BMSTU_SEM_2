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
    num = abs(num);
    int sum = 0;
    while (num > 0)
    {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

void get_els_sum_digits_gt_ten(matrix_t mat, size_t n, size_t m, arr_t rst, size_t *rst_n)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
        {
            int tmp = sum_digits(mat[i][j]);
            if (tmp > 10)
                push_back_array(mat[i][j], rst, rst_n);
        }
}

void put_els_from_array(matrix_t mat, size_t n, size_t m, arr_t a, size_t an)
{
    size_t a_i = 0;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
        {
            int tmp = sum_digits(mat[i][j]);
            if (tmp > 10 && a_i < an)
            {
                mat[i][j] = a[a_i];
                ++a_i;
            }
            if (a_i >= an)
                return;
        }
}
