#include "file.h"

int process(FILE *f, long *count)
{
    int t1, t2, t3;
    if (fscanf(f, "%d", &t1) != 1)
        return ERROR_EMPTY_FILE;
    if (fscanf(f, "%d", &t2) != 1)
        return ERROR_NOT_ENOUGH_ELEMENTS;
    if (fscanf(f, "%d", &t3) != 1)
        return ERROR_NOT_ENOUGH_ELEMENTS;
        
    *count = 0;
    do
    {
        if (t1 < t2 && t2 > t3)
            ++(*count);
        t1 = t2;
        t2 = t3;
    } while (fscanf(f, "%d", &t3) == 1);

    return 0;
}
