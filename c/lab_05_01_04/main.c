#include "file.h"

int main(void)
{
    long count;
    int rc = process(stdin, &count);

    if (rc != 0)
        return rc;

    printf("%ld\n", count);

    return 0;
}
