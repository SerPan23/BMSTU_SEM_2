#ifndef MATRIX_H
#define MATRIX_H

#include "array.h"

typedef int matrix_t[LEN_MAX][LEN_MAX];

int input_matrix(matrix_t mat, size_t n, size_t m);
void print_matrix(matrix_t mat, size_t n, size_t m);
void get_els_sum_digits_gt_ten(matrix_t mat, size_t n, size_t m, arr_t rst, size_t *rst_n);
void put_els_from_array(matrix_t mat, size_t n, size_t m, arr_t a, size_t an);

#endif
