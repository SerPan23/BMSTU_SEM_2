#include <stdio.h>
#include <stdint.h>

#define BYTE_SIZE (uint32_t)255
#define FIRST_BYTE_POS 24
#define SECOND_BYTE_POS 16
#define THIRD_BYTE_POS 8
#define FOURTH_BYTE_POS 0
#define INIT_MASK (uint32_t)1 << 31


uint32_t pack_bytes(uint32_t byte_1, uint32_t byte_2, uint32_t byte_3, uint32_t byte_4)
{
    uint32_t first_part = (byte_1 & BYTE_SIZE) << FIRST_BYTE_POS;
    uint32_t second_part = (byte_2 & BYTE_SIZE) << SECOND_BYTE_POS;
    uint32_t third_part = (byte_3 & BYTE_SIZE) << THIRD_BYTE_POS;
    uint32_t forth_part = byte_4 & BYTE_SIZE;

    return first_part + second_part + third_part + forth_part;
}

uint32_t unpack_byte(uint32_t packed_num, int byte_pos)
{
    if (byte_pos == 1)
        byte_pos = FIRST_BYTE_POS;
    else if (byte_pos == 2)
        byte_pos = SECOND_BYTE_POS;
    else if (byte_pos == 3)
        byte_pos = THIRD_BYTE_POS;
    else
        byte_pos = FOURTH_BYTE_POS;

    return (packed_num & (BYTE_SIZE << byte_pos)) >> byte_pos;
}

void print_in_bin(uint32_t packed_num)
{
    uint32_t mask = INIT_MASK;

    while (mask)
    {
        if (packed_num & mask)
            printf("1");
        else
            printf("0");

        mask >>= 1;
    }
}

int main(void)
{
    int byte_1, byte_2, byte_3, byte_4;

    printf("Введите первый байт: ");
    if (scanf("%d", &byte_1) != 1 || byte_1 < 0)
    {
        printf("Error: Некорректно введен первый байт");
        return 1;
    }

    printf("Введите второй байт: ");
    if (scanf("%d", &byte_2) != 1 || byte_2 < 0)
    {
        printf("Error: Некорректно введен второй байт");
        return 1;
    }

    printf("Введите третий байт: ");
    if (scanf("%d", &byte_3) != 1 || byte_3 < 0)
    {
        printf("Error: Некорректно введен третий байт");
        return 1;
    }

    printf("Введите четвертый байт: ");
    if (scanf("%d", &byte_4) != 1 || byte_4 < 0)
    {
        printf("Error: Некорректно введен четвертый байт");
        return 1;
    }

    uint32_t packed_num = pack_bytes((uint32_t)byte_1, (uint32_t)byte_2, (uint32_t)byte_3, (uint32_t)byte_4);

    uint32_t unpack_byte_1, unpack_byte_2, unpack_byte_3, unpack_byte_4;

    unpack_byte_1 = unpack_byte(packed_num, 1);
    unpack_byte_2 = unpack_byte(packed_num, 2);
    unpack_byte_3 = unpack_byte(packed_num, 3);
    unpack_byte_4 = unpack_byte(packed_num, 4);

    printf("Result: ");
    print_in_bin(packed_num);
    printf(" %u %u %u %u\n", unpack_byte_1, unpack_byte_2, unpack_byte_3, unpack_byte_4);

    return 0;
}
