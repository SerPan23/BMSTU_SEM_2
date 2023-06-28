#!/bin/bash

clang -std=c99 -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer -g -c main.c matrix.c
clang main.o matrix.o -o app.exe -lm