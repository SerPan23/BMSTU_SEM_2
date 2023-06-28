#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>

#define LEN_MAX 10
#define ERROR_INCORRECT_ROW_LEN 1
#define ERROR_INCORRECT_COLUMN_LEN 2
#define ERROR_INCORRECT_ELEMENT 3
#define ERROR_EMPTY_ARRAY 4

typedef int arr_t[LEN_MAX * LEN_MAX];

void push_back_array(int el, arr_t a, size_t *n);
void left_shift_elemets_to_count(size_t count, arr_t a, size_t n);
void left_shift_elements(arr_t a, size_t n);

#endif
