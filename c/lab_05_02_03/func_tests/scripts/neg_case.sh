#!/bin/bash

# проверка количества аргументов
if [ $# -lt 1 ]; then
	exit 1
fi

in_test=$1

if [ $# -eq 2 ]; then
	out_test=$2
fi

out_prog="out.txt"
command="../../app.exe"

# Коды ошибок
test_p="0"
test_f="1"

if [ $# -eq 3 ]; then
	command="$command $(cat "$3")"
fi

$command "$in_test" > "$out_prog"
error="$?"


# проверка завершения программы
if [ "$error" -eq 0 ]; then								# нулевой код ошибки
	exit "$test_f"
else													# не нулевой код ошибки
	# exit "$test_p"
	# сравниваем выходные данные программы и данные в тесте
	if [ $# -eq 2 ]; then
		if ! ./comparator.sh "$out_prog" "$out_test"; then		# неверный тест
			exit "$test_f"
		else													# верный тест
			exit "$test_p"
		fi
	else
		exit "$test_p"
	fi
fi