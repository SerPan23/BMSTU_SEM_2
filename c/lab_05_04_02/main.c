#include "file.h"

int main(int argc, char **argv)
{
    if (argc < 2)
        return ERROR_ARGS;
    if (argc > 4)
        return ERROR_ARGS;

    int rc = EXIT_SUCCESS;

    if (strcmp(argv[1], "sb") == 0 && argc == 4)
        rc = sort_file(argv[2], argv[3]);
    else if (strcmp(argv[1], "fb") == 0 && argc == 4)
        rc = print_names_end_substr(argv[2], argv[3]);
    else if (strcmp(argv[1], "ab") == 0 && argc == 3)
        rc = add_product(argv[2]);
    else
        rc = ERROR_ARGS;

    return rc;
}
