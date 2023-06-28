#!/bin/bash

gcc -std=c99 -fsanitize=address -fno-omit-frame-pointer -g -c main.c matrix.c array.c
gcc main.o matrix.o array.o -o app.exe -lm