#include "array.h"

void push_back_array(int el, arr_t a, size_t *n)
{
    a[*n] = el;
    ++(*n);
}

void left_shift_elements(arr_t a, size_t n)
{
    int tmp = a[0];
    for (size_t i = 1; i < n; i++)
        a[i - 1] = a[i];
    a[n - 1] = tmp;
}

void left_shift_elemets_to_count(size_t count, arr_t a, size_t n)
{
    for (size_t i = 0; i < count; i++)
        left_shift_elements(a, n);
}
