#ifndef MATRIX_H
#define MATRIX_H

#include "array.h"

typedef int matrix_t[LEN_MAX][LEN_MAX];

int input_matrix(matrix_t mat, size_t n, size_t m);
int is_symmetrical(arr_t line, size_t n);
void make_result_array(matrix_t mat, size_t n, size_t m, arr_t rst);

#endif
