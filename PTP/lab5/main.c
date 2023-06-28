#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#ifndef N
#error NMAX is not defined
#endif

typedef int matrix_t[N][N];

unsigned long long milliseconds_now()
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
    {
        return (unsigned long long)-1;
    }
    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

void init(matrix_t mat, size_t n)
{
    srand(time(NULL));

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            mat[i][j] = rand() % 100000;
}

void sum_matrix(int alpha, matrix_t a, matrix_t b, matrix_t c, size_t n)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            c[i][j] = alpha * a[i][j] + b[i][j];
}

int main(void)
{
    matrix_t a, b, c;
    size_t n = N;

    init(a, n);
    init(b, n);

    srand(time(NULL));
    int alpha = rand() % 1000;

    unsigned long long begin, end;

    begin = milliseconds_now();

    sum_matrix(alpha, a, b, c, n);

    end = milliseconds_now();

    a[0][0] = a[0][1];
    a[0][1] = a[1][1];

    b[0][0] = b[0][1];
    b[0][1] = b[1][1];

    c[0][0] = c[0][1];
    c[0][1] = c[1][1];

    printf("%llu\n", end - begin);

    return 0;
}
