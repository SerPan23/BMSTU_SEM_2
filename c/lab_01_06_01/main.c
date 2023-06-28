#include <stdio.h>
#include <math.h>

#define EPS 1e-8

int main(void)
{
    double xa, ya, xb, yb, xc, yc;

    printf("Введите x и y точки a: ");
    if (scanf("%lf%lf", &xa, &ya) != 2)
    {
        printf("Некорректно введены x и y точки a");
        return 1;
    }

    printf("Введите x и y точки b: ");
    if (scanf("%lf%lf", &xb, &yb) != 2)
    {
        printf("Некорректно введены x и y точки b");
        return 1;
    }

    printf("Введите x и y точки c: ");
    if (scanf("%lf%lf", &xc, &yc) != 2)
    {
        printf("Некорректно введены x и y точки c");
        return 1;
    }

    double s = 0.5 * fabs((xb - xa) * (yc - ya) - (xc - xa) * (yb - ya));

    if (s <= EPS)
    {
        printf("Треугольника не существует");
        return 1;
    }
    
    printf("Площадь: %.6lf\n", s);

    return 0;
}
