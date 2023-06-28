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

int split(char *s, words_t words, size_t *n)
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
                if ((*n) < MAX_WORDS_COUNT)
                    strcpy(words[(*n)++], word);
                else
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
    if ((*n) < MAX_WORDS_COUNT && i != 0)
        strcpy(words[(*n)++], word);
    else if ((*n) >= MAX_WORDS_COUNT && i != 0)
        return ERROR_WORDS_COUNT;
    
    return 0;
}

int is_like_of_last_word(char *s, words_t words, size_t n)
{
    return (strcmp(s, words[n - 1]) == 0);
}

int is_char_in_string_n(char *s, size_t n, char ch)
{
    for (size_t i = 0; i < n; i++)
        if (s[i] == ch)
            return 1;
    return 0;
}

void make_word_unique_letters(char *s, char *new_word)
{
    size_t i = 0, j = 0;
    while (s[i] != '\0')
    {
        if (!is_char_in_string_n(new_word, j, s[i]))
            new_word[j++] = s[i];
        ++i;
    }
    new_word[j] = '\0';
}

size_t insert_word_in_line(char *s, size_t pos, char *word)
{
    size_t j = pos;

    for (size_t i = 0; word[i] != '\0'; i++)
        s[j++] = word[i];
    
    s[j] = '\0';

    return j;
}

size_t make_new_line(char *new_s, words_t words, size_t n)
{
    size_t pos = 0;

    for (ptrdiff_t i = n - 2; i >= 0; i--)
        if (!is_like_of_last_word(words[i], words, n))
        {
            pos = insert_word_in_line(new_s, pos, " ");
            char new_word[MAX_WORD_LEN];
            make_word_unique_letters(words[i], new_word);
            pos = insert_word_in_line(new_s, pos, new_word);
        }
    return pos;
}
