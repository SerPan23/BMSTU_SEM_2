#include "my_string.h"

int main(void)
{
    string_t s;
    int rc = read_line(s);

    if (rc == ERROR_EMPTY_INPUT)
    {
        printf("NO\n");
        return 0;
    }

    if (rc != EXIT_SUCCESS)
        return rc;
    

    string_t correct_s;
    rc = del_spaces(s, correct_s);

    if (!rc)
    {
        printf("NO\n");
        return 0;
    }

    if (is_long_exponential_form(correct_s) || is_short_exponential_form(correct_s))
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}
