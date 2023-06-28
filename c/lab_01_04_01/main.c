#include <stdio.h>

int main(void)
{
    int apart_number;

    printf("Введите номер квартиры: ");
    if (scanf("%d", &apart_number) != 1 || apart_number <= 0)
    {
        printf("Некорректно введен номер квартиры");
        return 1;
    }

    int entrance = 1, floor = 1;

    if (apart_number % 36 == 0)
        entrance = apart_number / 36;
    else if (apart_number > 36)
        entrance = apart_number / 36 + 1;

    if (apart_number > 4)
    {
        if (apart_number % 36 == 0)
            floor = 9;
        else if (apart_number % 4 != 0)
            floor = (apart_number % 36) / 4 + 1;
        else
            floor = (apart_number % 36) / 4;
    }

    printf("Подъезд: %d\n", entrance);
    printf("Этаж: %d\n", floor);

    return 0;
}
