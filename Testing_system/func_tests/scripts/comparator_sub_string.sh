#!/bin/bash

if [ ! -f $1 ]; then
    if echo "$3" | grep -Eq "^-v$"; then
        echo Ошибка! Файл 1 не найден!
    fi
    exit 2
fi
if [ ! -f $2 ]; then
    if echo "$3" | grep -Eq "^-v$"; then
        echo Ошибка! Файл 2 не найден!
    fi
    exit 2
fi


if [ ! -r "$1" ]; then
    if echo "$3" | grep -Eq "^-v$"; then
        echo Ошибка! У вас нет прав доступа к файлу 1!
    fi
    exit 2
fi
if [ ! -r "$2" ]; then
    if echo "$3" | grep -Eq "^-v$"; then
        echo Ошибка! У вас нет прав доступа к файлу 2!
    fi
    exit 2
fi


OLD_IFS=$IFS
IFS=''

flag=''
myfile1=$(mktemp)
DONE=false
until $DONE ;do
    read -r line || DONE=true
    if [ -z $flag ]; then
        if echo "$line" | grep -Eq "Result:"; then
            flag="true"
            echo "$line" | grep -Eo "Result:.*" > "$myfile1"
        fi
    else
        echo "$line" >> "$myfile1"
    fi
done < $1


if [ -z $flag ]; then
    if echo "$3" | grep -Eq "^-v$"; then
        echo Ошибка! В первом файле не найдено подстроки \"Result:\"
    fi
    IFS=$OLD_IFS
    exit 2
fi

flag=''
myfile2=$(mktemp)
DONE=false
until $DONE ;do
    read -r line || DONE=true
    if [ -z $flag ]; then
        if echo "$line" | grep -Eq "Result:"; then
            flag="1"
            echo "$line" | grep -Eo "Result:.*" > "$myfile2"
        fi
    else
        echo "$line" >> "$myfile2"
    fi
done < $2

if [ -z $flag ]; then
    if echo "$3" | grep -Eq "^-v$"; then
        echo Ошибка! Во втором файле не найдено подстроки \"Result:\"
    fi
    IFS=$OLD_IFS
    exit 2
fi

IFS=$OLD_IFS

if cmp -s "$myfile1" "$myfile2"; then
    if echo "$3" | grep -Eq "^-v$"; then
        echo Файлы совпадают
    fi
    IFS=$OLD_IFS
    exit 0
else
    if echo "$3" | grep -Eq "^-v$"; then
        echo Файлы не совпадают
    fi
    IFS=$OLD_IFS
    exit 1
fi