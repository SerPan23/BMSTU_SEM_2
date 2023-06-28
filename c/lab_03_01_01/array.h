#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>

#define LEN_MAX 10
#define ERROR_INCORRECT_ROW_LEN 1
#define ERROR_INCORRECT_COLUMN_LEN 2
#define ERROR_INCORRECT_ELEMENT 3

typedef int arr_t[LEN_MAX];

void print_arr(arr_t a, size_t n);

#endif
