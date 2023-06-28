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

flag=''
myfile1=$(mktemp)
DONE=false
until $DONE ;do
    read -r line || DONE=true
    for word in $line; do 
        if [[ "$word" =~ ^[-+]?[0-9]+$ ]]; then
            flag='1'
            echo "$word" >> "$myfile1"
        fi
    done
done < "$1"


if [ -z $flag ]; then
    if echo "$3" | grep -Eq "^-v$"; then
        echo Ошибка! В файле 1 нет целых чисел
    fi
    exit 6
fi

flag=''
myfile2=$(mktemp)
DONE=false
until $DONE ;do
    read -r line || DONE=true
    for word in $line; do 
        if [[ "$word" =~ ^[-+]?[0-9]+$ ]]; then
            flag='1'
            echo "$word" >> "$myfile2"
        fi
    done
done < "$2"

if [ -z $flag ]; then
    if echo "$3" | grep -Eq "^-v$"; then
        echo Ошибка! В файле 2 нет целых чисел
    fi
    exit 7
fi


if cmp -s "$myfile1" "$myfile2"; then
    if echo "$3" | grep -Eq "^-v$"; then
        echo Файлы совпадают
    fi
    exit 0
else
    if echo "$3" | grep -Eq "^-v$"; then
        echo Файлы не совпадают
    fi
    exit 1
fi
