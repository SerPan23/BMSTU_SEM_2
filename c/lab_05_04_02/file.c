#include "file.h"

int file_size(FILE *f, long *size)
{
    long sz;

    if (fseek(f, 0L, SEEK_END))
        return ERROR_FILE_WORK;

    sz = ftell(f);
    if (sz < 0)
        return ERROR_FILE_WORK;

    if (sz == 0)
        return ERROR_EMPTY_FILE;

    if (sz % sizeof(product_t) != 0)
        return ERROR_FILE_READ;

    *size = sz;

    return fseek(f, 0L, SEEK_SET);
}

int get_product_by_pos(FILE *f, long pos, product_t *product)
{
    fseek(f, pos * sizeof(product_t), SEEK_SET);
    fread(product, sizeof(product_t), 1, f);
    return EXIT_SUCCESS;
}

int put_product_by_pos(FILE *f, long pos, product_t product)
{
    fseek(f, pos * sizeof(product_t), SEEK_SET);

    char *p = product.producer + PRODUCER_LEN + 1;
    *p = '\0';

    fwrite(&product, sizeof(product_t), 1, f);
    return EXIT_SUCCESS;
}

int copy_file(char *filepath_src, char *filepath_dst)
{
    FILE *f;
    f = fopen(filepath_src, "rb");

    if (f == NULL)
        return ERROR_WRONG_FILEPATH_SRC;

    FILE *out;
    out = fopen(filepath_dst, "wb");

    if (out == NULL)
    {
        fclose(f);
        return ERROR_WRONG_FILEPATH_DST;
    }

    long size;
    int rc = file_size(f, &size);

    if (rc != 0)
    {
        fclose(f);
        fclose(out);
        return ERROR_FILE_WORK;
    }

    size /= sizeof(product_t);

    for (long i = 0; i < size; i++)
    {
        product_t p = { "", "", 0, 0 };
        get_product_by_pos(f, i, &p);
        put_product_by_pos(out, i, p);
    }
    fclose(f);
    fclose(out);

    return EXIT_SUCCESS;
}

int sort_file(char *filepath_src, char *filepath_dst)
{
    int rc = copy_file(filepath_src, filepath_dst);

    if (rc != EXIT_SUCCESS)
        return rc;

    FILE *f;
    f = fopen(filepath_dst, "r+b");

    if (f == NULL)
        return ERROR_WRONG_FILEPATH_DST;

    long size;
    rc = file_size(f, &size);

    if (rc != 0)
    {
        fclose(f);
        return ERROR_FILE_WORK;
    }

    size /= sizeof(product_t);

    for (long i = 0; i < size; i++)
        for (long j = 0; j < size - 1 - i; j++)
        {
            product_t p1 = { "", "", 0, 0 }, p2 = { "", "", 0, 0 };
            get_product_by_pos(f, j, &p1);
            get_product_by_pos(f, j + 1, &p2);
            if ((p1.price < p2.price) || (p1.price == p2.price && p1.count < p2.count))
            {
                put_product_by_pos(f, j, p2);
                put_product_by_pos(f, j + 1, p1);
            }
        }
    fclose(f);
    return EXIT_SUCCESS;
}

int print_product(product_t p)
{
    printf("%s\n%s\n%" PRIu32 "\n%" PRIu32 "\n",
    p.name, p.producer, p.price, p.count);
    return EXIT_SUCCESS;
}

int print_names_end_substr(char *filepath_src, char *substr)
{
    FILE *f;
    f = fopen(filepath_src, "rb");

    if (f == NULL)
        return ERROR_WRONG_FILEPATH_SRC;

    long size;
    int rc = file_size(f, &size);

    if (rc != 0)
    {
        fclose(f);
        return ERROR_FILE_WORK;
    }

    size /= sizeof(product_t);

    long count = 0;

    for (long i = 0; i < size; i++)
    {
        product_t p = { "", "", 0, 0 };
        get_product_by_pos(f, i, &p);
        char *str = strstr(p.name, substr);
        if (str != NULL && (size_t) (str - p.name) == strlen(p.name) - strlen(substr))
        {
            print_product(p);
            count++;
        }
    }

    fclose(f);

    if (count == 0)
        return ERROR_NOTHING_PRINT;

    return EXIT_SUCCESS;
}

int read_product(product_t *product)
{
    char tmp_name[NAME_LEN + 2] = "";

    if (fgets(tmp_name, NAME_LEN + 2, stdin) == NULL)
        return ERROR_EMPTY_INPUT;

    tmp_name[strcspn(tmp_name, "\n")] = '\0';

    if (strlen(tmp_name) && strlen(tmp_name) > NAME_LEN)
        return ERROR_STR_LEN;

    strncpy(product->name, tmp_name, NAME_LEN + 1);

    char tmp_prod[PRODUCER_LEN + 2] = "";

    if (fgets(tmp_prod, PRODUCER_LEN + 2, stdin) == NULL)
        return ERROR_EMPTY_INPUT;

    tmp_prod[strcspn(tmp_prod, "\n")] = '\0';

    if (strlen(tmp_prod) && strlen(tmp_prod) > PRODUCER_LEN)
        return ERROR_STR_LEN;

    strncpy(product->producer, tmp_prod, PRODUCER_LEN + 1);

    uint32_t tmp;

    if (scanf("%" SCNu32, &tmp) != 1)
        return ERROR_INPUT_PRICE;

    product->price = tmp;

    if (scanf("%" SCNu32, &tmp) != 1)
        return ERROR_INPUT_COUNT;

    product->count = tmp;

    return EXIT_SUCCESS;
}

int add_product(char *filepath_src)
{
    FILE *f;
    f = fopen(filepath_src, "r+b");

    if (f == NULL)
        return ERROR_WRONG_FILEPATH_SRC;

    long size;
    int rc = file_size(f, &size);

    if (rc != 0)
    {
        fclose(f);
        return ERROR_FILE_WORK;
    }

    size /= sizeof(product_t);

    product_t p = { "", "", 0, 0 };
    rc = read_product(&p);

    if (rc != EXIT_SUCCESS)
    {
        fclose(f);
        return rc;
    }

    long pos = size;

    for (long i = size - 1; i >= 0; i--)
    {
        product_t tmp = { "", "", 0, 0 };
        get_product_by_pos(f, i, &tmp);
        printf("[%ld / %ld] %d < %d (pos = %ld)\n", i, size, tmp.price, p.price, pos);
        if ((tmp.price < p.price) || (tmp.price == p.price && tmp.count < p.count))
            pos = i;
    }

    for (long i = size - 1; i >= pos; i--)
    {
        product_t tmp = { "", "", 0, 0 };
        get_product_by_pos(f, i, &tmp);
        put_product_by_pos(f, i + 1, tmp);
    }
    put_product_by_pos(f, pos, p);

    fclose(f);
    return EXIT_SUCCESS;
}
