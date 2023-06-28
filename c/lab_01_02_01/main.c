#include <stdio.h>
#include <math.h>

#define EPS 1e-8
#define PI acos(-1.0)


int main(void)
{
    double a, b, f;

    printf("Введите величину основания a: ");
    if (scanf("%lf", &a) != 1 || a <= 0)
    {
        printf("Некорректно задано основание a");
        return 1;
    }

    printf("Введите величину основания b: ");
    if (scanf("%lf", &b) != 1 || b <= 0)
    {
        printf("Некорректно задано основание");
        return 1;
    }

    printf("Введите угол при большем основании (в градусах): ");
    if (scanf("%lf", &f) != 1 || f <= 0)
    {
        printf("Некорректно задан угол при большем основании");
        return 1;
    }

    double s = 0.0;

    if (fabs(f - 90.0) <= EPS)
        s = a * b;
    else
    {

        if (a > b)
        {
            double t = a;
            a = b;
            b = t;
        }

        s = 1.0 / 4.0 * (b - a) * (a + b) * tan(f * PI / 180.0);
    }

    printf("Площадь: %.6lf\n", s);

    return 0;
}
