#include "array.h"

void print_arr(arr_t a, size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
}
