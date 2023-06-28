#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_X_FAILED 1
#define INPUT_EPS_FAILED 2


double f(double x)
{
    return cos(asin(x));
}

double get_sum(double x, double eps)
{
    double sum = 0.0;
    int i = 3;
    double a = -x/216;
    while (fabs(a) > eps)
    {
        sum += a;
        i++;
        a *= ((2 * i + 1) * x) / ((i + 1) * (2 * i + 3));
    }
    return sum;
}


int main(void)
{
    double x;

    printf("Enter x: ");
    if (scanf("%lf", &x) != 1)
    {
        printf("Input failed\n");
        return INPUT_X_FAILED;
    }

    double eps;

    printf("Enter eps: ");
    if (scanf("%lf", &eps) != 1)
    {
        printf("Input eps failed\n");
	    return INPUT_EPS_FAILED;
    }

    double sum = get_sum(x, eps);

    double val_f_x = f(x);

    printf("Sum value = %e\n", sum);
    printf("f(x) value = %+.5lf\n", val_f_x);

    return EXIT_SUCCESS;
}

