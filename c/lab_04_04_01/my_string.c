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

int del_spaces(char *s, char *correct_s)
{
    size_t j = 0;

    int is_num_start = 0, is_num_end = 0;

    for (size_t i = 0; s[i] != '\0'; i++)
    {
        if (!isspace(s[i]))
        {
            is_num_start = 1;
            if (is_num_end)
                return 0;
            correct_s[j++] = s[i];
        }
        else if (is_num_start)
            is_num_end = 1;
    }
        
    correct_s[j] = '\0';
    return 1;
}

// [+-]?\d+([.]\d*)?([eE][+-]?\d+)?
int is_long_exponential_form(char *s)
{
    size_t pos = 0;

    if (s[pos] == '+' || s[pos] == '-')
        ++pos;

    int is_num_before_dot = 0;

    while (s[pos] != '.' && s[pos] != 'e' && s[pos] != 'E' && s[pos] != '\0')
    {
        if (!isdigit(s[pos++]))
            return 0;
        else
            is_num_before_dot = 1;
    }

    if (s[pos] == '.' && is_num_before_dot)
        ++pos;
    else if (!is_num_before_dot)
        return 0;
    

    while (s[pos] != 'e' && s[pos] != 'E' && s[pos] != '\0')
        if (!isdigit(s[pos++]))
            return 0;

    if (s[pos] != '\0')
        ++pos;

    if (s[pos] == '+' || s[pos] == '-')
        ++pos;

    while (s[pos] != '\0')
        if (!isdigit(s[pos++]))
            return 0;

    if (s[pos - 1] == 'e' || s[pos - 1] == 'E' || s[pos - 1] == '+' || s[pos - 1] == '-')
        return 0;

    if (pos == 1 && (s[pos] == '+' || s[pos] == '-'))
        return 0;

    return 1;
}

// [+-]?[.]\d+([eE][+-]?\d+)?)
int is_short_exponential_form(char *s)
{
    size_t pos = 0;

    if (s[pos] == '+' || s[pos] == '-')
        ++pos;

    if (s[pos++] != '.')
        return 0;

    int is_num_before_e = 0;

    while (s[pos] != 'e' && s[pos] != 'E' && s[pos] != '\0')
    {
        if (!isdigit(s[pos++]))
            return 0;
        else
            is_num_before_e = 1;
    }

    if (!is_num_before_e)
        return 0;

    if (s[pos] != '\0')
        ++pos;

    if (s[pos] == '+' || s[pos] == '-')
        ++pos;

    while (s[pos] != '\0')
        if (!isdigit(s[pos++]))
            return 0;

    if (s[pos - 1] == 'e' || s[pos - 1] == 'E' || s[pos - 1] == '+' || s[pos - 1] == '-')
        return 0;

    if (pos == 1 && (s[pos] == '+' || s[pos] == '-'))
        return 0;


    return 1;
}
