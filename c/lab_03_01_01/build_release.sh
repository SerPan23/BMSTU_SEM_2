#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -c -O3 main.c matrix.c array.c
gcc main.o matrix.o array.o -o app.exe -lm 