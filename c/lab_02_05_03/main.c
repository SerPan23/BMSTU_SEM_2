#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define NMAX 10
#define NUMBER_OF_ARGUMENTS 1
#define ERROR_INCORRECT_N 1
#define ERROR_INCORRECT_ELEMENT 2
#define ERROR_NO_PAIR 3

typedef int arr_t[NMAX];

int input_array_with_pointer(int *pa, int *pe)
{
    for (int *pcur = pa; pcur < pe; pcur++)
    {
        if (scanf("%d", pcur) != NUMBER_OF_ARGUMENTS)
            return ERROR_INCORRECT_ELEMENT;
    }
    return EXIT_SUCCESS;
}

int find_min_mul_of_pair(int *pa, int *pe)
{
    int *pb = pa + 1;
    int min_mul = *pa * *pb, tmp;
    pa = pb;
    pb++;
    while (pb < pe)
    {
        tmp = *pa * *pb;
        if (tmp < min_mul)
            min_mul = tmp;
        pa = pb;
        pb++;
    }
    return min_mul;
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

    if (n < 2)
        return ERROR_NO_PAIR;

    int *pa = a, *pe = a + n;

    printf("Введите элементы массива: ");
    int rc = input_array_with_pointer(pa, pe);
    if (rc != EXIT_SUCCESS)
    {
        printf("Некорректно задан элемент массива");
        return rc;
    }

    int min_mul = find_min_mul_of_pair(pa, pe);

    printf("Минимальное произведение из пар чисел массива: %d\n", min_mul);

    return EXIT_SUCCESS;
}
