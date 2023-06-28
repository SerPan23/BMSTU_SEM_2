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
#define ERROR_EMPTY_INPUT 1
#define ERROR_STR_LEN 2
#define ERROR_WORDS_COUNT 3
#define ERROR_WORD_LEN 4
#define ERROR_EMPTY_NEW_LINE 5

typedef char words_t[MAX_WORDS_COUNT][MAX_WORD_LEN];
typedef char string_t[MAX_STRING_LEN + 1];

int read_line(string_t s);
int split(char *s, words_t words, size_t *n);
int is_like_of_last_word(char *s, words_t words, size_t n);
int is_char_in_string_n(char *s, size_t n, char ch);
void make_word_unique_letters(char *s, char *new_word);
size_t insert_word_in_line(char *s, size_t pos, char *word);
size_t make_new_line(char *new_s, words_t words, size_t n);

#endif
