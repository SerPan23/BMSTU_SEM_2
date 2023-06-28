#include "matrix.h"

int input_matrix(matrix_t mat, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            if (scanf("%d", &mat[i][j]) != 1)
                return ERROR_INCORRECT_ELEMENT;

    return EXIT_SUCCESS;
}

int is_symmetrical(arr_t line, size_t n)
{
    for (size_t i = 0; i < n / 2; i++)
        if (line[i] != line[n - 1 - i])
            return 0;
    return 1;
}

void make_result_array(matrix_t mat, size_t n, size_t m, arr_t rst)
{
    for (size_t k = 0; k < n; k++)
        rst[k] = is_symmetrical(mat[k], m);
}
