#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define NMAX 20
#define USER_NMAX 10
#define NUMBER_OF_ARGUMENTS 1
#define ERROR_INCORRECT_N 1
#define ERROR_INCORRECT_ELEMENT 2

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

int count_multiples_of_three(arr_t a, size_t n)
{
    int count = 0; 
    for (size_t i = 0; i < n; i++)
        if (a[i] % 3 == 0)
            ++count;
    return count;
}

void get_n_fibonacci(arr_t fibs, size_t n)
{
    fibs[0] = 0;
    fibs[1] = 1;
    for (size_t i = 2; i <= n; i++)
        fibs[i] = fibs[i - 2] + fibs[i - 1];
}

void add_fibonacci_in_arr(arr_t a, size_t n, size_t *new_n)
{
    int count_mult_of_three = count_multiples_of_three(a, n);
    arr_t fibs;
    get_n_fibonacci(fibs, count_mult_of_three);

    *new_n = n + count_mult_of_three;

    int end_ind = n - 1 + count_mult_of_three;
    int fibs_ind = count_mult_of_three - 1;
    for (size_t i = 0; i < n; i++)
    {
        if (a[n - 1 - i] % 3 == 0)
        {
            a[end_ind] = fibs[fibs_ind];
            a[end_ind - 1] = a[n - 1 - i];
            end_ind -= 2;
            --fibs_ind;
        }
        else
        {
            a[end_ind] = a[n - 1 - i];
            --end_ind;
        }
    }
}

void print_arr(arr_t a, size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%d\n", a[i]);
}


int main(void)
{
    arr_t a;
    size_t n;

    printf("Введите количество элементов массива: ");
    if (scanf("%zu", &n) != NUMBER_OF_ARGUMENTS || n == 0 || n > USER_NMAX)
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

    size_t new_n;
    add_fibonacci_in_arr(a, n, &new_n);

    printf("Полученный массив:\n");
    print_arr(a, new_n);

    return EXIT_SUCCESS;
}
