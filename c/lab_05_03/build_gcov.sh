#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -c -O0 -g3 -coverage main.c file.c
gcc main.o file.o -o app.exe -coverage -lm