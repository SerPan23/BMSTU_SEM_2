#include "my_string.h"

int read_line(string_t s)
{
    char tmp_string[MAX_STRING_LEN + 2];

    if (fgets(tmp_string, MAX_STRING_LEN + 2, stdin) == NULL)
        return ERROR_EMPTY_INPUT;

    tmp_string[strcspn(tmp_string, "\n")] = '\0';

    if (strlen(tmp_string) && strlen(tmp_string) > MAX_STRING_LEN)
        return ERROR_STR_LEN;

    strncpy(s, tmp_string, MAX_STRING_LEN + 1);

    return EXIT_SUCCESS;
}

int is_unique(char *s, words_t words, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        if (strcmp(s, words[i]) == 0)
            return 0;
    }
    return 1;
}

int split_unique(char *s, words_t words, size_t *n)
{
    *n = 0;
    char word[MAX_WORD_LEN];
    size_t i = 0;

    for (size_t j = 0; s[j] != '\0'; j++)
    {
        if (ispunct(s[j]) || isspace(s[j]))
        {
            if (i != 0)
            {
                word[i] = '\0';
                if ((*n) < MAX_WORDS_COUNT && is_unique(word, words, *n))
                    strcpy(words[(*n)++], word);
                else if ((*n) >= MAX_WORDS_COUNT)
                    return ERROR_WORDS_COUNT;
            }
            i = 0;
        }
        else
        {
            if (i + 1 == MAX_WORD_LEN)
                return ERROR_WORD_LEN;
            word[i++] = s[j];
        }
    }

    if (i == MAX_WORD_LEN)
        return ERROR_WORD_LEN;

    word[i] = '\0';
    if (i != 0 && (*n) < MAX_WORDS_COUNT && is_unique(word, words, *n))
        strcpy(words[(*n)++], word);
    else if (i != 0 && (*n) >= MAX_WORDS_COUNT)
        return ERROR_WORDS_COUNT;

    return 0;
}

void sort_bubble(words_t words, size_t n)
{
    char tmp[MAX_WORD_LEN];

    for (size_t i = 0; i < n; i++)
    {
        int flag = 1;
        for (size_t j = 0; j < n - 1 - i; j++)
            if (strcmp(words[j], words[j + 1]) > 0)
            {
                strcpy(tmp, words[j]);
                strcpy(words[j], words[j + 1]);
                strcpy(words[j + 1], tmp);

                flag = 0;
            }
        if (flag)
            break;
    }
}

void print_words(words_t words, size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf(" %s", words[i]);
}
