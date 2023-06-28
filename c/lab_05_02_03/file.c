#include "file.h"

int find_file_len(FILE *f, long *n)
{
    rewind(f);
    *n = 0;
    double tmp;
    while (!feof(f))
    {
        if (fscanf(f, "%lf", &tmp) == 1)
            ++(*n);
        else
        {
            if (*n == 0)
                return ERROR_EMPTY_FILE;
            return ERROR_WRONG_FILE_DATA;
        }
    }
    return EXIT_SUCCESS;
}

int find_mean(FILE *f, long n, double *avg)
{
    rewind(f);
    double sum = 0, tmp;

    for (long i = 0; i < n; i++)
        if (fscanf(f, "%lf", &tmp) == 1)
            sum += tmp;

    *avg = sum / n;
    return EXIT_SUCCESS;
}

int calc_variance(FILE *f, long n, double avg, double *variance)
{
    rewind(f);
    double sum = 0, tmp;

    for (long i = 0; i < n; i++)
        if (fscanf(f, "%lf", &tmp) == 1)
        {
            tmp -= avg;
            sum += tmp * tmp;
        }
    *variance = sqrt(sum / n);
    return EXIT_SUCCESS;
}

int is_obey_three_sigma_rule(FILE *f, long n, double avg, double variance)
{
    if (fabs(variance) < EPS)
        return 0;

    rewind(f);
    double tmp;
    int count = 0;

    for (long i = 0; i < n; i++)
        if (fscanf(f, "%lf", &tmp) == 1)
            if (avg - 3 * variance <= tmp && tmp <= avg + 3 * variance)
                count++;

    if (count * 100.0 / n < 99.73)
        return 0;
    
    return 1;
}
