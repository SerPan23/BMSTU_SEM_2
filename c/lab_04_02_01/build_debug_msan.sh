#!/bin/bash

clang -std=c99 -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer -g -c main.c my_string.c
clang main.o my_string.o -o app.exe -lm