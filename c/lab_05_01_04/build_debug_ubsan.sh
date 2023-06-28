#!/bin/bash

clang -std=c99 -fsanitize=undefined -fPIE -pie -fno-omit-frame-pointer -g -c main.c file.c
clang main.o file.o -o app.exe -lm