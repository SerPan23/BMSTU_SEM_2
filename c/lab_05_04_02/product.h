#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define NAME_LEN 30
#define PRODUCER_LEN 15

typedef struct
{
    char name[NAME_LEN + 1];
    char producer[PRODUCER_LEN + 1];
    uint32_t price;
    uint32_t count;
} product_t;

#endif
