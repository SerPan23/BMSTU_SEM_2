#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

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

int get_number_by_pos(FILE *f, long pos, int32_t *num)
{
    fseek(f, pos * sizeof(int32_t), SEEK_SET);
    fread(num, sizeof(int32_t), 1, f);
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

    size /= sizeof(int32_t);

    int32_t t;

    for (long i = 0; i < size; i++)
    {
        get_number_by_pos(in, i, &t);
        fprintf(out, "%" PRId32 "\n", t);
    }

    fclose(in);
    fclose(out);
    return 0;
}