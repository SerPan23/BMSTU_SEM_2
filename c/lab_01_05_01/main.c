#include <stdio.h>

int get_quotient_and_remainder(int a, int d, int *r)
{
    int q = 0;
    *r = a;

    while (*r >= d)
    {
        *r -= d;
        ++q;
    }
    return q;
}

int main(void)
{
    int a, d;

    printf("Введите первое число: ");
    if (scanf("%d", &a) != 1 || a <= 0)
    {
        printf("Некорректно введено первое число");
        return 1;
    }

    printf("Введите второе число: ");
    if (scanf("%d", &d) != 1 || d <= 0)
    {
        printf("Некорректно введено второе число");
        return 1;
    }

    int r;
    int q = get_quotient_and_remainder(a, d, &r);

    printf("Частное: %d\nОстаток: %d\n", q, r);

    return 0;
}
