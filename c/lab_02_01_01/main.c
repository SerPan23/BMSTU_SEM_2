#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define NMAX 10
#define NUMBER_OF_ARGUMENTS 1
#define ERROR_INCORRECT_N 1
#define ERROR_INCORRECT_ELEMENT 2
#define ERROR_NO_ODD 3

typedef int arr_t[NMAX];

int input_array(arr_t a, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        if (scanf("%d", &a[i]) != NUMBER_OF_ARGUMENTS)
            return ERROR_INCORRECT_ELEMENT;
    }
    return EXIT_SUCCESS;
}

int product_of_odd(arr_t a, size_t n, int *prod)
{
    *prod = 1;
    int count_odd = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (a[i] % 2 != 0)
        {
            *prod *= a[i];
            ++count_odd;
        }
    }

    if (count_odd == 0)
        return ERROR_NO_ODD;

    return EXIT_SUCCESS;
}

int main(void)
{
    arr_t a;
    size_t n;

    printf("Введите количество элементов массива: ");
    if (scanf("%zu", &n) != NUMBER_OF_ARGUMENTS || n == 0 || n > NMAX)
    {
        printf("Некорректно задано количество элементов массива");
        return ERROR_INCORRECT_N;
    }

    printf("Введите элементы массива: ");
    int rc = input_array(a, n);
    if (rc != EXIT_SUCCESS)
    {
        printf("Некорректно задан элемент массива");
        return rc;
    }

    int prod;
    rc = product_of_odd(a, n, &prod);
    if (rc != EXIT_SUCCESS)
    {
        printf("Не найден ни один нечетный элемент");
        return rc;
    }

    printf("Произведение нечётных элементов массива: %d\n", prod);

    return EXIT_SUCCESS;
}
