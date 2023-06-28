#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-8

#define ERROR_FEW_ARGS 1
#define ERROR_A_LOT_ARGS 2
#define ERROR_WRONG_FILEPATH 3
#define ERROR_WRONG_FILE_DATA 4
#define ERROR_EMPTY_FILE 5

int find_file_len(FILE *f, long *n);
int find_mean(FILE *f, long n, double *avg);
int calc_variance(FILE *f, long n, double avg, double *variance);
int is_obey_three_sigma_rule(FILE *f, long n, double avg, double variance);

#endif
