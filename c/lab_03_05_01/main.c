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

    arr_t a;
    size_t an = 0;

    get_els_sum_digits_gt_ten(mat, n, m, a, &an);

    if (an == 0)
    {
        printf("В массиве нет элементов с суммой цифр больше десяти");
        return ERROR_EMPTY_ARRAY;
    }

    left_shift_elemets_to_count(3, a, an);
    put_els_from_array(mat, n, m, a, an);

    print_matrix(mat, n, m);

    return 0;
}
