#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../product.h"

int file_size(FILE *f, long *size)
{
    long sz;

    if (fseek(f, 0L, SEEK_END))
        return 2;

    sz = ftell(f);
    if (sz < 0)
        return 3;

    *size = sz;

    return fseek(f, 0L, SEEK_SET);
}

int get_product_by_pos(FILE *f, long pos, product_t *product)
{
    fseek(f, pos * sizeof(product_t), SEEK_SET);
    fread(product, sizeof(product_t), 1, f);
    return EXIT_SUCCESS;
}

int fprint_product(product_t p, FILE *f)
{
    fprintf(f, "%s\n%s\n%" PRIu32 "\n%" PRIu32 "\n",
    p.name, p.producer, p.price, p.count);
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;
    FILE *in;
    in = fopen(argv[1], "rb");

    FILE *out;
    char tmp[1024];

    size_t path_len = strlen(argv[1]);

    if (path_len > 4 && argv[1][path_len - 4] == '.')
        strncpy(tmp, argv[1], path_len - 4);
    else
        strcpy(tmp, argv[1]);

    tmp[path_len - 4] = '\0';

    strcat(tmp, "_b.txt");
    out = fopen(tmp, "w");

    if (out == NULL)
        printf("out NULL (%s)\n", tmp);

    long size;
    int rc = file_size(in, &size);

    if (rc != 0)
    {
        fclose(in);
        return rc;
    }

    size /= sizeof(product_t);

    product_t t = { "", "", 0, 0 };

    for (long i = 0; i < size; i++)
    {
        get_product_by_pos(in, i, &t);
        fprint_product(t, out);
    }

    fclose(in);
    fclose(out);
    return 0;
}