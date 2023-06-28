#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

int find_file_len(FILE *f, long *n)
{
    rewind(f);
    *n = 0;
    int32_t tmp;
    while (!feof(f))
    {
        if (fscanf(f, "%" SCNd32, &tmp) == 1)
            ++(*n);
        else
            return EXIT_FAILURE;
    }
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

    int32_t t;

    rewind(in);
    for (long i = 0; i < n; i++)
    {
        if (fscanf(in, "%" SCNd32, &t) == 1)
        {
            fseek(out, 0, SEEK_END);
            fwrite(&t, sizeof(int32_t), 1, out);
        }
    }


    fclose(in);
    fclose(out);
    return 0;
}