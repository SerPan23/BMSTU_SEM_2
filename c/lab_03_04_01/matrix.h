#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

#define LEN_MAX 10
#define ERROR_INCORRECT_ROW_LEN 1
#define ERROR_INCORRECT_COLUMN_LEN 2
#define ERROR_INCORRECT_ELEMENT 3
#define ERROR_MATRIX_NOT_RECT 4

typedef int matrix_t[LEN_MAX][LEN_MAX];

int input_matrix(matrix_t mat, size_t n);
void print_matrix(matrix_t mat, size_t n);
void flip_el_in_hourglass(matrix_t mat, size_t n);

#endif
