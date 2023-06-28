#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

#define MAX_STRING_LEN 256
#define MAX_WORD_LEN 17
#define MAX_WORDS_COUNT 128
#define ERROR_STR_LEN 1
#define ERROR_EMPTY_INPUT 2

typedef char words_t[MAX_WORDS_COUNT][MAX_WORD_LEN + 1];
typedef char string_t[MAX_STRING_LEN + 1];

int read_line(string_t s);
int del_spaces(char *s, char *correct_s);
int is_long_exponential_form(char *s);
int is_short_exponential_form(char *s);

#endif
