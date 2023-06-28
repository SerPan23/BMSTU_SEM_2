#!/bin/bash

# проверка количества аргументов
if [ $# -lt 2 ]; then
	exit 1
fi

in_test=$1
out_test=$2
bin_out_prog="out.bin"
# out_prog="out.txt"
command="../../app.exe"
t2b="./t2b.exe"
b2t="./b2t.exe"

# Коды ошибок
test_p="0"
test_f="1"

if [ $# -eq 3 ]; then
	command="$command $(cat "$3") "
fi

$t2b "$in_test"

len=${#in_test} 
new_len=$((len - 4))
	
bin_in_test="${in_test:0:new_len}.bin"

$command "$bin_in_test" > "$bin_out_prog"
error="$?"

$b2t "$bin_in_test"


# проверка завершения программы
if ! [ "$error" -eq 0 ]; then							# не нулевой код ошибки
	exit "$test_f"
fi

# сравниваем выходные данные программы и данные в тесте
if ! ./comparator.sh "${in_test:0:new_len}_b.txt" "$out_test"; then		# неверный тест
	exit "$test_f"
else													# верный тест
	exit "$test_p"
fi