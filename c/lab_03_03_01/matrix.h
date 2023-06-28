#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

#define LEN_MAX 10
#define ERROR_INCORRECT_ROW_LEN 1
#define ERROR_INCORRECT_COLUMN_LEN 2
#define ERROR_INCORRECT_ELEMENT 3

typedef int matrix_t[LEN_MAX][LEN_MAX];

int input_matrix(matrix_t mat, size_t n, size_t m);
void print_matrix(matrix_t mat, size_t n, size_t m);
int max_line_el(matrix_t mat, size_t m, size_t i);
void swap_lines(matrix_t mat, size_t m, size_t i_1, size_t i_2);
void sort_by_max_el(matrix_t mat, size_t n, size_t m);

#endif
