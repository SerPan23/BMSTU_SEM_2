#ifndef FILE_H
#define FILE_H

#include "product.h"

#define ERROR_ARGS 53
#define ERROR_WRONG_FILEPATH_SRC 1
#define ERROR_WRONG_FILEPATH_DST 2
#define ERROR_EMPTY_FILE 3
#define ERROR_FILE_WORK 4
#define ERROR_FILE_READ 5
#define ERROR_WRONG_POS 6
#define ERROR_EMPTY_INPUT 7
#define ERROR_STR_LEN 8
#define ERROR_INPUT_PRICE 9
#define ERROR_INPUT_COUNT 10
#define ERROR_NOTHING_PRINT 11

int file_size(FILE *f, long *size);
int get_product_by_pos(FILE *f, long pos, product_t *product);
int put_product_by_pos(FILE *f, long pos, product_t product);

int sort_file(char *filepath_src, char *filepath_dst);
int print_names_end_substr(char *filepath_src, char *substr);
int read_product(product_t *product);
int add_product(char *filepath_src);

#endif
