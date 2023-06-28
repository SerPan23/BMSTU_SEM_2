#include "my_string.h"

int main(void)
{
    string_t s;
    int rc = read_line(s);

    if (rc != EXIT_SUCCESS)
        return rc;

    words_t words;
    size_t words_n;

    rc = split(s, words, &words_n);

    if (rc == ERROR_WORD_LEN)
        return ERROR_WORD_LEN;

    if (rc == ERROR_WORDS_COUNT)
        return ERROR_WORDS_COUNT;

    string_t new_s;

    size_t pos = make_new_line(new_s, words, words_n);

    if (pos == 0)
        return ERROR_EMPTY_NEW_LINE;

    printf("Result:%s\n", new_s);

    return 0;
}
