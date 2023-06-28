#include "my_string.h"
#include <string.h>

int main(void)
{
    size_t failed_count = 0;

    {
        char *s1[] = { "lorem ipsum dolor", "lorem ipsum dolor", "", "" };
        char *s2[] = { "abcde", "!", "asfda", "" };

        size_t tests_n;

        if (sizeof(s1) / sizeof(char *) <= sizeof(s2) / sizeof(char *))
            tests_n = sizeof(s1) / sizeof(char *);
        else
            tests_n = sizeof(s2) / sizeof(char *);

        for (size_t i = 0; i < tests_n; i++)
            if (my_strpbrk(s1[i], s2[i]) != strpbrk(s1[i], s2[i]))
                ++failed_count;
    }

    {
        char *s1[] = { "lorem ipsum dolor", "lorem ipsum dolor", "lorem ipsum dolor", "", "" };
        char *s2[] = { "lorem", "lorem ipsum dolor", "!", "", "fdsa" };

        size_t tests_n;

        if (sizeof(s1) / sizeof(char *) <= sizeof(s2) / sizeof(char *))
            tests_n = sizeof(s1) / sizeof(char *);
        else
            tests_n = sizeof(s2) / sizeof(char *);

        for (size_t i = 0; i < tests_n; i++)
            if (my_strspn(s1[i], s2[i]) != strspn(s1[i], s2[i]))
                ++failed_count;
    }

    {
        char *s1[] = { "lorem ipsum dolor", "lorem ipsum dolor", "", "abc" };
        char *s2[] = { "abcde", "!", "", "123" };

        size_t tests_n;

        if (sizeof(s1) / sizeof(char *) <= sizeof(s2) / sizeof(char *))
            tests_n = sizeof(s1) / sizeof(char *);
        else
            tests_n = sizeof(s2) / sizeof(char *);

        for (size_t i = 0; i < tests_n; i++)
            if (my_strcspn(s1[i], s2[i]) != strcspn(s1[i], s2[i]))
                ++failed_count;
    }

    {
        char *s[] = { "lorem ipsum dolor", "lorem ipsum dolor", "", "aaaaaab", "ab" };
        char chs[] = { 'r', '!', '?', 'b', 'a' };

        size_t tests_n;

        if (sizeof(s) / sizeof(char *) <= sizeof(chs) / sizeof(char))
            tests_n = sizeof(s) / sizeof(char *);
        else
            tests_n = sizeof(chs) / sizeof(char);

        for (size_t i = 0; i < tests_n; i++)
            if (my_strchr(s[i], chs[i]) != strchr(s[i], chs[i]))
                ++failed_count;
    }

    {
        char *s[] = { "lorem ipsum dolor", "lorem ipsum dolor", "", "abaabaaaba", "abaaba" };
        char chs[] = { 'r', '!', '?', 'b', 'a' };

        size_t tests_n;

        if (sizeof(s) / sizeof(char *) <= sizeof(chs) / sizeof(char))
            tests_n = sizeof(s) / sizeof(char *);
        else
            tests_n = sizeof(chs) / sizeof(char);

        for (size_t i = 0; i < tests_n; i++)
            if (my_strrchr(s[i], chs[i]) != strrchr(s[i], chs[i]))
                ++failed_count;
    }

    printf("%zu\n", failed_count);
    return failed_count;
}
