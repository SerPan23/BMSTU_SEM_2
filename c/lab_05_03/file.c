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

    if (sz % sizeof(int32_t) != 0)
        return ERROR_FILE_READ;

    *size = sz;

    return fseek(f, 0L, SEEK_SET);
}

int get_number_by_pos(FILE *f, long pos, int32_t *num)
{
    fseek(f, pos * sizeof(int32_t), SEEK_SET);
    fread(num, sizeof(int32_t), 1, f);
    return EXIT_SUCCESS;
}

int put_number_by_pos(FILE *f, long pos, int32_t num)
{
    fseek(f, pos * sizeof(int32_t), SEEK_SET);
    fwrite(&num, sizeof(int32_t), 1, f);
    return EXIT_SUCCESS;
}

int fill_rand_numbers(char *filepath, long num_counts)
{
    FILE *f;
    f = fopen(filepath, "wb");

    if (f == NULL)
        return ERROR_WRONG_FILEPATH;

    srand(time(NULL));

    for (long i = 0; i < num_counts; i++)
    {
        int32_t tmp = rand() % 10000;
        put_number_by_pos(f, i, tmp);
    }

    fclose(f);
    return EXIT_SUCCESS;
}

int print_numbers(char *filepath)
{
    FILE *f;
    f = fopen(filepath, "rb");

    if (f == NULL)
        return ERROR_WRONG_FILEPATH;

    long size;
    int rc = file_size(f, &size);

    if (rc != 0)
    {
        fclose(f);
        return ERROR_FILE_WORK;
    }

    size /= sizeof(int32_t);

    int32_t tmp;

    for (long i = 0; i < size; i++)
    {
        get_number_by_pos(f, i, &tmp);
        printf("%" PRId32 " ", tmp);
    }

    fclose(f);
    return EXIT_SUCCESS;
}

int sort_file(char *filepath)
{
    FILE *f;
    f = fopen(filepath, "r+b");

    if (f == NULL)
        return ERROR_WRONG_FILEPATH;

    long size;
    int rc = file_size(f, &size);

    if (rc != 0)
    {
        fclose(f);
        return ERROR_FILE_WORK;
    }

    size /= sizeof(int32_t);

    for (long i = 0; i < size; i++)
        for (long j = 0; j < size - 1 - i; j++)
        {
            int32_t t1, t2;
            get_number_by_pos(f, j, &t1);
            get_number_by_pos(f, j + 1, &t2);
            if (t1 > t2)
            {
                put_number_by_pos(f, j, t2);
                put_number_by_pos(f, j + 1, t1);
            }
        }
    fclose(f);
    return EXIT_SUCCESS;
}
