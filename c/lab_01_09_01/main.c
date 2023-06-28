#include <stdio.h>
#include <math.h>

int main(void)
{
    double x, g = 0.0;

    printf("Введите x: ");
    if (scanf("%lf", &x) != 1 || x < 0)
    {
        printf("Некорректно введен x");
        return 1;
    }
    
    int i = 1;

    while (x >= 0)
    {
        g += sqrt(x / i);

        i++;

        printf("Введите x: ");
        if (scanf("%lf", &x) != 1)
        {
            printf("Некорректно введен x");
            return 1;
        }
    }

    
    g = sin(g);

    printf("Значение g(x): %.6lf\n", g);

    return 0;
}
