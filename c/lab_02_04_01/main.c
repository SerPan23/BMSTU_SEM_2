#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define NMAX 10
#define NUMBER_OF_ARGUMENTS 1
#define ERROR_INCORRECT_N 1
#define ERROR_INCORRECT_ELEMETS_COUNT 100

typedef int arr_t[NMAX];

int input_array_by_end_feature(arr_t a, size_t *n)
{
    int tmp;
    *n = 0;
    while (scanf("%d", &tmp) == NUMBER_OF_ARGUMENTS)
    {
        if (*n == NMAX)
            return ERROR_INCORRECT_ELEMETS_COUNT;
        a[*n] = tmp;
        ++(*n);
    }

    if (*n == 0)
        return ERROR_INCORRECT_N;

    return EXIT_SUCCESS;
}

void print_arr(arr_t a, size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%d\n", a[i]);
}

void insertion_sort(arr_t a, size_t n)
{
    for (size_t i = 1; i < n; i++)
    {
        int tmp = a[i];
        int j = i;
        while (j > 0 && a[j - 1] > tmp)
        {
            a[j] = a[j - 1];
            --j;
        }
        a[j] = tmp;
    }
}


int main(void)
{
    arr_t a;
    size_t n;

    printf("Введите элементы массива: ");
    int rc = input_array_by_end_feature(a, &n);
    if (rc != EXIT_SUCCESS && rc != ERROR_INCORRECT_ELEMETS_COUNT)
        return rc;

    insertion_sort(a, n);

    printf("Полученный массив:\n");
    print_arr(a, n);

    return rc;
}
