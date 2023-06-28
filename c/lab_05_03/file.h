#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

#define ERROR_FEW_ARGS 1
#define ERROR_A_LOT_ARGS 2
#define ERROR_WRONG_ARGS 3
#define ERROR_WRONG_FILEPATH 4
#define ERROR_EMPTY_FILE 5
#define ERROR_FILE_WORK 6
#define ERROR_FILE_READ 7
#define ERROR_WRONG_POS 8

int file_size(FILE *f, long *size);
int fill_rand_numbers(char *filepath, long num_counts);
int print_numbers(char *filepath);
int sort_file(char *filepath);
int get_number_by_pos(FILE *f, long pos, int *num);
int put_number_by_pos(FILE *f, long pos, int num);

#endif
