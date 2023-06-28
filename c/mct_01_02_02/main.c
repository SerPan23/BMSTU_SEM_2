#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_MAX 1024
#define ERROR_INCORECT_N 1
#define ERROR_INCORECT_ELEMENT 2
#define ERROR_INCORECT_INSERT_NUM 3
#define ERROR_OVERFLOW_N_MAX 4
#define ERROR_NO_SQUARE 5

typedef int arr_t[N_MAX];

/*
The function for input the array.
Accepts a number as input.
*/
int input_arr(arr_t a, size_t n)
{
    for(size_t i = 0; i < n; i++)
        if (scanf("%d", &a[i]) != 1)
            return ERROR_INCORECT_ELEMENT;
    return EXIT_SUCCESS;
}

/*
The function of checking whether a number is a complete square
Accepts a number as input.
*/
int is_square(int num)
{
    int sum = 0;
    for(int i = 1; sum < num; i += 2)
        sum += i;
    return (sum == num);
}

/*
The function that removes from the array all numbers that are not
full of a square.
Accepts array and array len as input.
*/
void filter_square(arr_t a, size_t *n)
{
    size_t count = 0;
    for (size_t i = 0; i < *n; i++)
    {
        if (is_square(a[i]) == 0)
        {
            count++;
            continue;
        }
        else
            a[i - count] = a[i];
    }
    *n = *n - count;
}

/*
The function that checks whether a number is two digit.
Accepts a number as input.
*/
int is_two_digits(int num)
{
    return ((9 < abs(num)) && (abs(num) < 100));
}

/*
The function that inserts an element at a given position.
Accepts element, element position, array and array len as input.
*/
int insert_element(int element, size_t pos, arr_t a, size_t *n)
{
    if (*n + 1 >= N_MAX)
        return ERROR_OVERFLOW_N_MAX;

    size_t i = *n;
    for (; i > pos; i--)
        a[i] = a[i - 1];

    a[i] = element;
    ++*n;

    return EXIT_SUCCESS;
}

/*
The function that inserts an element after two digit number.
Accepts element, element position, array and array len as input.
*/
int insert_num_after_two_digits_element(int num, arr_t a, size_t *n)
{
    for (size_t i = 0; i < *n; i++)
    {
        if (is_two_digits(a[i]))
        {
            int rc = insert_element(num, i + 1, a, n);
            if (rc != EXIT_SUCCESS)
                return rc;
            i++;
        }
    }
    return EXIT_SUCCESS;
}

/*
The function for print the array.
Accepts a number as input.
*/
void print_arr(arr_t a, size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
}

int main(void)
{
    int num;

    printf("Enter number for insertion: ");
    if (scanf("%d", &num) != 1)
    {
        printf("Input number for insertion failed\n"); 
        return ERROR_INCORECT_INSERT_NUM;
    }

    size_t n;

    printf("Enter n: ");
    if (scanf("%zu", &n) != 1)
    {
	    printf("Input n failed\n");
        return ERROR_INCORECT_N;
    }

    arr_t a;
    printf("Enter array: ");
    int rc = input_arr(a, n);
    if (rc != EXIT_SUCCESS)
    {
	    printf("Some array element input failed\n");
	    return rc;
    }

    filter_square(a, &n);

    if (n == 0)
    {
        printf("Error no full square elements in array");
        return ERROR_NO_SQUARE;
    }

    rc = insert_num_after_two_digits_element(num, a, &n);
    if (rc != EXIT_SUCCESS)
    {
        printf("Error n overflow N_MAX\n");
        return rc;
    }

    printf("Result array: ");
    print_arr(a, n);
    printf("\n");

    return EXIT_SUCCESS;
}

