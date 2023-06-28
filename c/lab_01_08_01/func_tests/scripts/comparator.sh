#!/bin/bash

if [ ! -f "$1" ]; then
    if echo "$3" | grep -Eq "^-v$"; then
        echo Ошибка! Файл 1 не найден!
    fi
    exit 2
fi
if [ ! -f "$2" ]; then
    if echo "$3" | grep -Eq "^-v$"; then
        echo Ошибка! Файл 2 не найден!
    fi
    exit 3
fi


if [ ! -r "$1" ]; then
    if echo "$3" | grep -Eq "^-v$"; then
        echo Ошибка! У вас нет прав доступа к файлу 1!
    fi
    exit 4
fi
if [ ! -r "$2" ]; then
    if echo "$3" | grep -Eq "^-v$"; then
        echo Ошибка! У вас нет прав доступа к файлу 2!
    fi
    exit 5
fi

file1=$1
file2=$2

mask="Result: .*"

file1_sub_string=$(grep -Eo "$mask" "$file1")

file2_sub_string=$(grep -Eo "$mask" "$file2")

if [[ "$file1_sub_string" != "$file2_sub_string" ]]; then
    exit 1
fi

exit 0
