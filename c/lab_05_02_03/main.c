#include "file.h"

int main(int argc, char **argv)
{
    if (argc < 2)
        return ERROR_FEW_ARGS;
    if (argc > 2)
        return ERROR_A_LOT_ARGS;

    FILE *f;

    f = fopen(argv[1], "r");

    if (f == NULL)
        return ERROR_WRONG_FILEPATH;

    long n;

    int rc = find_file_len(f, &n);

    if (rc != EXIT_SUCCESS)
        return rc;

    double avg;

    rc = find_mean(f, n, &avg);

    if (rc != EXIT_SUCCESS)
        return rc;

    double variance;

    rc = calc_variance(f, n, avg, &variance);

    if (rc != EXIT_SUCCESS)
        return rc;

    int result = is_obey_three_sigma_rule(f, n, avg, variance);

    printf("%d\n", result);

    return 0;
}
