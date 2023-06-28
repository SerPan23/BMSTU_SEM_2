#include "file.h"

int main(int argc, char **argv)
{
    if (argc < 2)
        return ERROR_FEW_ARGS;
    if (argc > 4)
        return ERROR_A_LOT_ARGS;

    int rc = EXIT_SUCCESS;
    if (*argv[1] == 'c' && argc == 4)
        rc = fill_rand_numbers(argv[3], atoi(argv[2]));
    else if (*argv[1] == 'p' && argc == 3)
        rc = print_numbers(argv[2]);
    else if (*argv[1] == 's' && argc == 3)
        rc = sort_file(argv[2]);
    else
        rc = ERROR_WRONG_ARGS;

    return rc;
}
