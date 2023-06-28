#!/bin/bash

# проверка количества аргументов
if [ $# -lt 1 ]; then
	exit 1
fi

in_test=$1
out_prog="out.txt"
command="../../app.exe"

# Коды ошибок
test_p="0"
test_f="1"


$command < "$in_test" > "$out_prog"
error="$?"


# проверка завершения программы
if [ "$error" -eq 0 ]; then								# нулевой код ошибки
	exit "$test_f"
else													# не нулевой код ошибки
	exit "$test_p"
fi