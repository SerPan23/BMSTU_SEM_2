#!/bin/bash

# проверка количества аргументов
if [ $# -lt 1 ]; then
	exit 1
fi

in_test=$1

if [ $# -eq 3 ]; then
	out_test=$3
fi

bin_out_prog="out.bin"
# out_prog="out.txt"
command="../../app.exe"
t2b="./t2b.exe"
b2t="./b2t.exe"

# Коды ошибок
test_p="0"
test_f="1"

if [ $# -eq 2 ]; then
	command="$command $(cat "$2") "
fi

$t2b "$in_test"

len=${#in_test} 
new_len=$((len - 4))
	
bin_in_test="${in_test:0:new_len}.bin"

$command "$bin_in_test" > "$bin_out_prog"
error="$?"

$b2t "$bin_in_test"

# проверка завершения программы
if [ "$error" -eq 0 ]; then								# нулевой код ошибки
	exit "$test_f"
else													# не нулевой код ошибки
	# exit "$test_p"
	# сравниваем выходные данные программы и данные в тесте
	if [ $# -eq 3 ]; then
		if ! ./comparator.sh "${in_test:0:new_len}_b.txt" "$out_test"; then		# неверный тест
			exit "$test_f"
		else													# верный тест
			exit "$test_p"
		fi
	else
		exit "$test_p"
	fi
fi