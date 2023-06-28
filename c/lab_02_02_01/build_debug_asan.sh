#!/bin/bash

gcc -std=c99 -fsanitize=address -fno-omit-frame-pointer -g -c main.c
gcc main.o -o app.exe -lm