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

    printf("Введите элементы матрицы: ");
    int rc = input_matrix(mat, n, m);
    if (rc != EXIT_SUCCESS)
    {
        printf("Некорректно задан элемент матрицы"); 
        return rc;
    }

    sort_by_max_el(mat, n, m);

    print_matrix(mat, n, m);

    return 0;
}
