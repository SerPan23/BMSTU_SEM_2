#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define LEN_MAX 10
#define ERROR_INCORRECT_ROW_LEN 1
#define ERROR_INCORRECT_COLUMN_LEN 2
#define ERROR_MATRIX_NOT_RECT 3

typedef int matrix_t[LEN_MAX][LEN_MAX];

void print_matrix(matrix_t mat, size_t n);
void fill_matrix_in_spiral(matrix_t mat, size_t n);

#endif
