#!/bin/bash

gcc -std=c99 -fsanitize=address -fno-omit-frame-pointer -g -c main.c file.c
gcc main.o file.o -o app.exe -lm