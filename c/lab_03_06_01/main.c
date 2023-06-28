#include "matrix.h"

int main(void)
{
    size_t n, m;
    matrix_t mat;

    printf("Введите количество строк матрицы: ");
    if (scanf("%zu", &n) != 1 || n == 0 || n > LEN_MAX)
    {
        printf("Некорректно задано количество строк матрицы");
        return ERROR_INCORRECT_ROW_LEN;
    }

    printf("Введите количество столбцов матрицы: ");
    if (scanf("%zu", &m) != 1 || m == 0 || m > LEN_MAX)
    {
        printf("Некорректно задано количество столбцов матрицы");
        return ERROR_INCORRECT_COLUMN_LEN;
    }

    if (n != m)
    {
        printf("Количество столбцов не совпадает с количеством строк");
        return ERROR_MATRIX_NOT_RECT;
    }

    fill_matrix_in_spiral(mat, n);

    print_matrix(mat, n);

    return 0;
}
