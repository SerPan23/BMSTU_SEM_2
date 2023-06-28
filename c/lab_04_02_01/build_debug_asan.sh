#!/bin/bash

gcc -std=c99 -fsanitize=address -fno-omit-frame-pointer -g -c main.c my_string.c
gcc main.o my_string.o -o app.exe -lm