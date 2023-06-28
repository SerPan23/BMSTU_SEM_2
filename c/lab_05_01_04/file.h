#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>

#define ERROR_EMPTY_FILE -1
#define ERROR_NOT_ENOUGH_ELEMENTS -2

int process(FILE *f, long *count);

#endif
