#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#ifndef N
#error NMAX is not defined
#endif

#ifndef IS_SORTED
#error is_sorted is not defined
#endif

typedef int arr_t[N];

unsigned long long milliseconds_now()
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
    {
        return (unsigned long long)-1;
    }
    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

void init_sorted(arr_t a, size_t n)
{
    for (size_t i = 0; i < n; i++)
        a[i] = i;
}

void init(arr_t a, size_t n)
{
    srand(time(NULL));

    for (size_t i = 0; i < n; i++)
        a[i] = rand();
}

void insertion_sort(int *pa, int *pe)
{
    int *pi = pa + 1;
    for (; pi < pe; pi++)
    {
        int tmp = *pi;
        int *pj = pi;
        while (pj > pa && *(pj - 1) > tmp)
        {
            *pj = *(pj - 1);
            --pj;
        }
        *pj = tmp;
    }
}

int main(void)
{
    arr_t a;
    size_t n = N;

    int is_sorted = IS_SORTED;

    if (is_sorted)
            init_sorted(a, n);
    else
        init(a, n);

    int *pa = a, *pe = pa + n;

    unsigned long long begin, end;

    begin = milliseconds_now();

    insertion_sort(pa, pe);

    end = milliseconds_now();

    a[0] = a[1];
    a[1] = 1234;

    printf("%llu\n", end - begin);

    return 0;
}
