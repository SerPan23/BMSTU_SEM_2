#include "my_string.h"

int main(void)
{
    string_t s;
    int rc = read_line(s);

    if (rc != EXIT_SUCCESS)
        return rc;

    words_t words;
    size_t words_n;

    rc = split_unique(s, words, &words_n);

    if (rc == ERROR_WORD_LEN)
        return ERROR_WORD_LEN;

    if (rc == ERROR_WORDS_COUNT)
        return ERROR_WORDS_COUNT;

    if (words_n == 0)
        return ERROR_NO_WORDS;

    sort_bubble(words, words_n);

    printf("Result:");
    print_words(words, words_n);
    printf("\n");

    return 0;
}
