#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define NMAX 10
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

int is_prime(int num)
{
    if (num <= 1)
        return 0;
    
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0)
            return 0;

    return 1;
}

int copy_primes(arr_t a, size_t n, arr_t primes_a, size_t *primes_n)
{
    int j = 0;
    *primes_n = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (is_prime(a[i]))
        {
            ++(*primes_n);
            primes_a[j] = a[i];
            ++j;
        }
    }

    if (*primes_n == 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
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

    arr_t primes_a;
    size_t primes_n;
    rc = copy_primes(a, n, primes_a, &primes_n);
    if (rc != EXIT_SUCCESS)
        return rc;

    printf("Полученный массив:\n");
    print_arr(primes_a, primes_n);

    return EXIT_SUCCESS;
}
