#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

#define LEN_MAX 10
#define ERROR_INCORRECT_ROW_LEN 1
#define ERROR_INCORRECT_COLUMN_LEN 2
#define ERROR_INCORRECT_ELEMENT 3
#define ERROR_EMPTY_RESULT 4

typedef int matrix_t[LEN_MAX][LEN_MAX];

int input_matrix(matrix_t mat, size_t n, size_t m);
void print_matrix(matrix_t mat, size_t n, size_t m);
void find_min_digits_sum_el_i_j(matrix_t mat, size_t n, size_t m, size_t *min_i, size_t *min_j);
void del_row_and_col(matrix_t mat, size_t *n, size_t *m, size_t del_i, size_t del_j);

#endif
