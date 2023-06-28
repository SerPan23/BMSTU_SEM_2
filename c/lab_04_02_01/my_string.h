#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LEN 256
#define MAX_WORD_LEN 17
#define MAX_WORDS_COUNT 128
#define ERROR_EMPTY_INPUT 1
#define ERROR_STR_LEN 2
#define ERROR_WORDS_COUNT 3
#define ERROR_WORD_LEN 4
#define ERROR_NO_WORDS 5

typedef char words_t[MAX_WORDS_COUNT][MAX_WORD_LEN + 1];
typedef char string_t[MAX_STRING_LEN + 1];


int read_line(string_t s);
int is_unique(char *s, words_t words, size_t n);
int split_unique(char *s, words_t words, size_t *n);
void sort_bubble(words_t words, size_t n);
void print_words(words_t words, size_t n);

#endif
