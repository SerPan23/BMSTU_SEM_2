#include "my_string.h"

char *my_strpbrk(const char *s1, const char *s2)
{
    for (size_t i = 0; s1[i] != '\0'; i++)
        for (size_t j = 0; s2[j] != '\0'; j++)
            if (s1[i] == s2[j])
                return (char *)&s1[i];
    return NULL;
}

size_t my_strspn(const char *s1, const char *s2)
{
    size_t count = 0;
    for (size_t i = 0; s1[i] != '\0'; i++)
    {
        int flag = 0;
        for (size_t j = 0; s2[j] != '\0'; j++)
            if (s1[i] == s2[j])
                flag = 1;
        if (!flag)
            return count;       
        ++count;
    }

    return count;
}

size_t my_strcspn(const char *s1, const char *s2)
{
    size_t i = 0;

    while (s1[i] != '\0')
    {
        for (size_t j = 0; s2[j] != '\0'; j++)
            if (s1[i] == s2[j])
                return i;
        ++i;
    }

    return i;
}

char *my_strchr(const char *s, int c)
{
    size_t i = 0;
    for (; s[i] != '\0'; i++)
        if (s[i] == (char)c)
            return (char *)&s[i];

    if ((char)c == '\0')
        return (char *)&s[i];

    return NULL;
}

char *my_strrchr(const char *s, int c)
{
    size_t i = 0;
    char *p = NULL;

    for (; s[i] != '\0'; i++)
        if (s[i] == (char)c)
            p = (char *) & s[i];

    if ((char)c == '\0')
        return (char *)&s[i];

    return p;
}
