#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../product.h"

int read_product(product_t *product, FILE *f)
{
    char tmp_name[1024] = "";

    fgets(tmp_name, 1024, f);
    tmp_name[strcspn(tmp_name, "\n")] = '\0';

    if (strlen(tmp_name) && strlen(tmp_name) > NAME_LEN)
        return 3;

    strcpy(product->name, tmp_name);

    char tmp_prod[1024] = "";

    fgets(tmp_prod, 1024, f);
    tmp_prod[strcspn(tmp_prod, "\n")] = '\0';

    if (strlen(tmp_prod) && strlen(tmp_prod) > PRODUCER_LEN)
        return 4;

    strcpy(product->producer, tmp_prod);

    char tmp[1024] = "";

    fgets(tmp, 1024, f);
    tmp[strcspn(tmp, "\n")] = '\0';
    uint32_t num = strtoul(tmp, NULL, 0);
    product->price = num;

    fgets(tmp, 1024, f);
    tmp[strcspn(tmp, "\n")] = '\0';
    num = strtoul(tmp, NULL, 0);
    product->count = num;

    return EXIT_SUCCESS;
}

int find_file_len(FILE *f, long *n)
{
    rewind(f);
    *n = 0;
    product_t tmp = { "", "", 0, 0 };
    while (!feof(f))
    {
        int rc = read_product(&tmp, f);
        if (rc == EXIT_SUCCESS)
            ++(*n);
        else
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int put_product_to_end(FILE *f, product_t product)
{
    fseek(f, 0, SEEK_END);
    char *p = product.producer + PRODUCER_LEN + 1;
    *p = '\0';
    fwrite(&product, sizeof(product_t), 1, f);
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;

    FILE *in;
    in = fopen(argv[1], "r");

    FILE *out;

    char tmp[1024];

    size_t path_len = strlen(argv[1]);

    if (path_len > 4 && argv[1][path_len - 4] == '.')
        strncpy(tmp, argv[1], path_len - 4);
    else
        strcpy(tmp, argv[1]);

    tmp[path_len - 4] = '\0';

    strcat(tmp, ".bin");
    out = fopen(tmp, "wb");

    long n;

    find_file_len(in, &n);

    product_t t = { "", "", 0, 0 };

    rewind(in);
    for (long i = 0; i < n; i++)
    {
        int rc = read_product(&t, in);
        if (rc == EXIT_SUCCESS)
        {
            // fseek(out, 0, SEEK_END);
            // fwrite(&t, sizeof(product_t), 1, out);
            put_product_to_end(out, t);
        }
        // printf("* %d\n", rc);
    }


    fclose(in);
    fclose(out);
    return 0;
}