#include <stdio.h>
#include <math.h>

double s(double x, double eps)
{
    double a_n = x, result = 0.0;
    int i = 0;

    while (fabs(a_n) >= eps)
    {
        result += a_n;
        i++;
        a_n *= -x * x / (2 * i * (2 * i + 1));
    }
    return result;
}

int main(void)
{
    double x, eps;

    printf("Введите x: ");
    if (scanf("%lf", &x) != 1)
    {
        printf("Некорректно введен x");
        return 1;
    }

    printf("Введите eps: ");
    if (scanf("%lf", &eps) != 1 || eps <= 0 || eps > 1)
    {
        printf("Некорректно введен eps");
        return 1;
    }

    double s_val = s(x, eps);
    double f = sin(x);

    double absolute_accuracy = fabs(f - s_val);

    double relative_accuracy = 0.0;

    if (fabs(f) > eps)
        relative_accuracy = absolute_accuracy / fabs(f);

    printf("Значение s(x) с точность eps: %.6lf\n", s_val);
    printf("Значение f(x): %.6lf\n", f);
    printf("Абсолютная погрешность : %.6lf\n", absolute_accuracy);
    printf("Относительная погрешность : %.6lf\n", relative_accuracy);

    return 0;
}
